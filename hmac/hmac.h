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
		unsigned char *hmac_hash;
		String secret, payload;
		const char *secretArray, *payloadArray;
		unsigned int type;
		bool is_digested;

		const char *getArrayFromString(String source);
	protected:
		static void _bind_methods();
	public:
		
		void init(String p_secret, String p_payload, unsigned int p_type);
		void setSecret(String secret);
		void setPayload(String payload);
		void setType(unsigned int type);
		void digest();

		String* getHMAC();
		
		HMAC() {
			type = 6; //SHA256 default 
			is_digested = false;
		}
};
#endif
