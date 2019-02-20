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
#include <iostream>

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
	CharString source8 = source.utf8();
	const char *sourceChars = source8.ptr();
	
	return sourceChars;
}

// Methods
void HMAC::digest()
{
	unsigned char local_mac[64] = {'\0'};
	char converted_mac[64*2+1];

	mbedtls_md_context_t ctx;
	mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256; //this->type;

	const size_t key_length = strlen(this->secretArray);
	const size_t payload_length = strlen(this->payloadArray);
	
	mbedtls_md_init(&ctx);
  	mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
  	mbedtls_md_hmac_starts(&ctx, (const unsigned char *) this->secretArray, key_length);
  	mbedtls_md_hmac_update(&ctx, (const unsigned char *) this->payloadArray, payload_length);
  	mbedtls_md_hmac_finish(&ctx, local_mac);
  	mbedtls_md_free(&ctx);	

	for(int i = 0; i < sizeof(local_mac); i++) {
		if(local_mac[i] != '\0') {
			sprintf(&converted_mac[i*2], "%02X", (int)local_mac[i]);
		}
		else {
			break;
		}
	}

	this->hmac_hash = converted_mac;
	this->is_digested = true;
}

String HMAC::getHMAC(){
	if(this->is_digested) { 
		return this->hmac_hash;
	}

	return "";
}

void HMAC::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init"), &HMAC::init);
	ClassDB::bind_method(D_METHOD("digest"), &HMAC::digest);
	ClassDB::bind_method(D_METHOD("get_hmac"), &HMAC::getHMAC);
}

