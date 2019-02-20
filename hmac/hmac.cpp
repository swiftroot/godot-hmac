/*
hmac.cpp 
Copyright (c) 2019 Alek Mlynek, Swift Root Inc.

Class for generating HMAC strings in Godot
*/


#include "hmac.h"
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>

// Init
void HMAC::init(String p_secret,String p_payload, unsigned int p_type)
{
	this->setSecret(p_secret);
	this->setPayload(p_payload);
	this->setType(p_type);
}

void HMAC::setSecret(String val) {
	this->secret = val;
	this->secretArray = this->getArrayFromString(this->secret);
}
void HMAC::setPayload(String val) {
	this->payload = val;
	this->payloadArray = this->getArrayFromString(this->payload);
}

void HMAC::setType(unsigned int val) {this->type = val;}

const char* HMAC::getArrayFromString(String source) {
	char dest[source.length()+1];
	const char *destPointer;

	int i;
	for(i = 0; i < source.length(); i++)
	{
		dest[i] = (unsigned char)source[i];
	}
	dest[i+1] = '\0';

	destPointer = dest;
	return destPointer;
}

// Methods
void HMAC::digest()
{
	unsigned char local_mac[64] = {'\0'};
	char payload_buffer[512] = {'\0'};

	mbedtls_md_context_t ctx;
	mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256; //this->type;

	const size_t key_length = strlen(this->secretArray);
	const size_t payload_length = strlen(this->payloadArray);
	
	mbedtls_md_init(&ctx);
	mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
	mbedtls_md_hmac_starts(&ctx, (const unsigned char*)this->secretArray, key_length);
	mbedtls_md_hmac_update(&ctx, (const unsigned char*)payload_buffer, payload_length);
	mbedtls_md_hmac_finish(&ctx, local_mac);
	mbedtls_md_free(&ctx);	

	this->hmac_hash = local_mac;
	this->is_digested = true;
}

String* HMAC::getHMAC(){
	String *returnMac = new String();
	const char *local_hash = reinterpret_cast<const char*>(this->hmac_hash);

	size_t hmac_length = strlen(local_hash);

	int i = 0;
	for(i = 0; i < hmac_length; i++)
	{
		returnMac += this->hmac_hash[i];
	}

	return returnMac;
}

void HMAC::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init"), &HMAC::init);
	ClassDB::bind_method(D_METHOD("digest"), &HMAC::digest);
	ClassDB::bind_method(D_METHOD("get_hmac"), &HMAC::getHMAC);

}



