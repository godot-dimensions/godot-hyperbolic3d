#include "register_types.h"

#if GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#elif GODOT_MODULE
#include "core/config/engine.h"
#endif

#include "math/transform_h3d_bind.h"
#include "math/world_h3d.h"
#include "nodes/node_h3d.h"

inline void add_godot_singleton(const StringName &p_singleton_name, Object *p_object) {
#if GDEXTENSION
	Engine::get_singleton()->register_singleton(p_singleton_name, p_object);
#elif GODOT_MODULE
	Engine::get_singleton()->add_singleton(Engine::Singleton(p_singleton_name, p_object));
#endif
}

inline void remove_godot_singleton(const StringName &p_singleton_name) {
#if GDEXTENSION
	Engine::get_singleton()->unregister_singleton(p_singleton_name);
#elif GODOT_MODULE
	Engine::get_singleton()->remove_singleton(p_singleton_name);
#endif
}

void initialize_hyperbolic3d_module(ModuleInitializationLevel p_level) {
	// Note: Classes MUST be registered in inheritance order.
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
		GDREGISTER_CLASS(godot_h3d_bind::TransformH3D);
		GDREGISTER_CLASS(WorldH3D);
	} else if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		// Register node classes here.
		// You can add singletons using add_godot_singleton().
		GDREGISTER_CLASS(NodeH3D);
	}
}

void uninitialize_hyperbolic3d_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		// Perform cleanup here.
		// You can remove singletons using remove_godot_singleton().
	}
}
