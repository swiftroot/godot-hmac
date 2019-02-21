#include "register_types.h"
#include "hmac.h"
#include <core/class_db.h>
#include <core/engine.h>

void register_hmac_types() {
	ClassDB::register_class<HMAC>();
}

void unregister_hmac_types() {
}
