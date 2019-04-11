/*
hmac.cpp 
Copyright (c) 2019 Alek Mlynek, Swift Root Inc.

Class for generating HMAC strings in Godot
*/

#include "hmac.h"

// Init
void HMAC::init(PoolByteArray p_secret,PoolByteArray p_payload, String p_type)
{
	this->setSecret(p_secret);
	this->setPayload(p_payload);
	this->setType(p_type);
	is_init = true;
}

void HMAC::setSecret(PoolByteArray val) {
	this->secret = val;
}
void HMAC::setPayload(PoolByteArray val) {
	this->payload = val;
}

void HMAC::setType(String val) {
	this->type = val;
	this->mac_size = 32;

	if (val == "sha256") { this->md_type = MBEDTLS_MD_SHA256; }
	else if(val == "none") { this->md_type = MBEDTLS_MD_NONE;}
	else if(val == "md2") { this->md_type = MBEDTLS_MD_MD2; }
	else if(val == "md4") { this->md_type = MBEDTLS_MD_MD4;}
	else if(val == "md5") { this->md_type = MBEDTLS_MD_MD5;}
	else if(val == "sha1") { 
		this->md_type = MBEDTLS_MD_SHA1;
		this->mac_size = 20;
	}
	else if(val == "sha224") { 
		this->md_type = MBEDTLS_MD_SHA224;
		this->mac_size = 28;
	}
	else if(val == "sha384") { 
		this->md_type = MBEDTLS_MD_SHA384;
		this->mac_size = 48;
	}
	else if(val == "sha512") { 
		this->md_type = MBEDTLS_MD_SHA512;
		this->mac_size = 64;
	}
	else if(val == "ripemd160") {
		this->md_type = MBEDTLS_MD_RIPEMD160;
		this->mac_size = 20;
	}
}

// Methods
void HMAC::digest()
{
	if (!is_init) { 
		print_line("Not initialized. Please run init() first");
		return; 
	}

	unsigned char local_mac[this->mac_size];
	char converted_mac[this->mac_size*2]; // = this->converted_mac;

	mbedtls_md_context_t ctx;

	const size_t key_length = this->secret.size(); 
	const size_t payload_length = this->payload.size(); 	
	
	char *secretBuffer = new char[key_length](); 
	char *payloadBuffer = new char[payload_length](); 

	// @TODO: Bit ugly, is there a better way?
	for (int i = 0; i < key_length; i++) {
		secretBuffer[i] = (char)this->secret[i];
	}

	for (int i = 0; i < payload_length; i++) {
		payloadBuffer[i] = (char)this->payload[i];
	}

	mbedtls_md_init(&ctx);
  	mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(this->md_type), 1);
  	mbedtls_md_hmac_starts(&ctx, (const unsigned char *) secretBuffer, key_length);
  	mbedtls_md_hmac_update(&ctx, (const unsigned char *) payloadBuffer, payload_length);
  	mbedtls_md_hmac_finish(&ctx, local_mac);
  	mbedtls_md_free(&ctx);

	for (int i = 0; i < sizeof(local_mac); i++) {
		sprintf(&converted_mac[i*2], "%02x", (int)local_mac[i]);
	}
	
	this->hmac_hash = converted_mac; // converts
	this->is_digested = true;
}

String HMAC::getHMAC(){
	if (this->is_digested) { 
		return this->hmac_hash;
	}

	return "";
}

void HMAC::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init"), &HMAC::init);
	ClassDB::bind_method(D_METHOD("digest"), &HMAC::digest);
	ClassDB::bind_method(D_METHOD("get_hmac"), &HMAC::getHMAC);
}

