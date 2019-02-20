/*
hmac.cpp 
Copyright (c) 2019 Alek Mlynek, Swift Root Inc.

Class for generating HMAC strings in Godot
*/


#include "hmac.h"
#include <thirdparty/mbedtls/include/mbedtls/sha256.h>

// Init
HMAC::HMAC() {
}

void HMAC::sha_256(int data, int key)
{
	return;
}
// Methods

void HMAC::_bind_methods() {
	ClassDB::bind_method(D_METHOD("sha_256"), &HMAC::sha_256);
}



