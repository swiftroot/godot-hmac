/*
device_check.h 
Copyright (c) 2019 Alek Mlynek, Swift Root Inc.

Class for generating HMAC strings in Godot
*/

#ifndef HMAC_H
#define HMAC_H

#include "core/reference.h"

class HMAC : public Reference {
	GDCLASS(HMAC, Reference);

	protected:
		static void _bind_methods();
	public:
		void get_token();
		void sha_256(int data, int key);

		HMAC();
};
#endif
