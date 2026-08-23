#include "register_types.h"

#if GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#elif GODOT_MODULE
#include "core/config/engine.h"
#include "core/core_bind.h"
#endif

#include "math/transform_h3d_bind.h"
#include "math/world_h3d.h"
#include "nodes/node_h3d.h"

inline void add_godot_singleton(const StringName &p_singleton_name, Object *p_object) {
	CoreBind::Engine::get_singleton()->register_singleton(p_singleton_name, p_object);
}

inline void remove_godot_singleton(const StringName &p_singleton_name) {
	CoreBind::Engine::get_singleton()->unregister_singleton(p_singleton_name);
}

#if GDEXTENSION
// The extension declares `set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE)`,
// which is required to support reloading, but prevents using CORE or SERVERS initialization levels.
#define MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST MODULE_INITIALIZATION_LEVEL_SCENE
#elif GODOT_MODULE
// The module can use CORE or SERVERS initialization levels. In modules, we want to
// register as early as possible, so that other modules can depend on this module.
#define MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST MODULE_INITIALIZATION_LEVEL_CORE
#endif

void initialize_hyperbolic3d_module(ModuleInitializationLevel p_level) {
	// Classes MUST be registered in inheritance order, then dependency order.
	// When the inheritance and dependency doesn't matter, then alphabetical order is used.
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST) {
		GDREGISTER_CLASS(godot_h3d_bind::TransformH3D);
		GDREGISTER_CLASS(WorldH3D);
		GDREGISTER_CLASS(NodeH3D);
	}
}

void uninitialize_hyperbolic3d_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST) {
	}
}
