/*
device_check.h 
Copyright (c) 2019 Alek Mlynek, Swift Root Inc.

Class for generating HMAC strings in Godot
*/

#ifndef HMAC_H
#define HMAC_H

#include "core/reference.h"
#include "core/ustring.h"
#include <thirdparty/mbedtls/include/mbedtls/md.h>
#include <thirdparty/mbedtls/include/mbedtls/sha256.h>

class HMAC : public Reference {
	GDCLASS(HMAC, Reference);

	private:
		PoolByteArray secret, payload; 
		String hmac_hash, type;
		mbedtls_md_type_t md_type;
		const char *secretArray, *payloadArray;
		bool is_digested;
		bool is_init;
	protected:
		static void _bind_methods();
	public:
		void init(PoolByteArray p_secret, PoolByteArray p_payload, String p_type = "sha256");
		void setSecret(PoolByteArray secret);
		void setPayload(PoolByteArray payload);
		void setType(String type);
		void digest();

		String getHMAC();
		
		HMAC() {
			type = "sha256"; 
			md_type = MBEDTLS_MD_SHA256;
			is_digested = false;
			is_init = false;
		}
};
#endif
