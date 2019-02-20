#include "register_types.h"
#include "device_check.h"
#include <core/class_db.h>
#include <core/engine.h>

void register_devicecheck_types() {
	//  ClassDB is not a good idea in this case. If it doesn't exist, there is no way to check.
	ClassDB::register_class<HMAC>();
	
	// Engine::get_singleton()->add_singleton(Engine::Singleton("DeviceCheck", memnew(DeviceCheck)));

}

void unregister_devicecheck_types() {
}
