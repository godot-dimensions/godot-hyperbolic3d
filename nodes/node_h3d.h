#pragma once

#include "../godot_hyper3d_defines.h"

#if GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#elif GODOT_MODULE
#include "scene/main/node.h"
#endif

class NodeH3D : public Node {
	GDCLASS(NodeH3D, Node);

protected:
	static void _bind_methods();
};
