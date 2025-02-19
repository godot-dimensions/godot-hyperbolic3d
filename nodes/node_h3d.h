#pragma once

#include "../math/transform_h3d_bind.h"
#include "../math/world_h3d.h"

#if GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#elif GODOT_MODULE
#include "scene/main/node.h"
#endif

class NodeH3D : public Node {
	GDCLASS(NodeH3D, Node);

	TransformH3D _transform;
	Ref<WorldH3D> _world;

	void _find_or_make_world();
	void _give_main_world_to_viewport();

protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _get_property_list(List<PropertyInfo> *p_list) const;

public:
	// Trivial getters and setters.
	Vector3 get_position() const { return _transform.get_position(); }
	void set_position(const Vector3 &p_position) { _transform.set_position(p_position); }

	Quaternion get_gyration() const { return _transform.get_gyration(); }
	void set_gyration(const Quaternion &p_gyration) { _transform.set_gyration(p_gyration); }

	TransformH3D get_transform() const { return _transform; }
	void set_transform(const TransformH3D &p_transform) { _transform = p_transform; }

	Ref<godot_h3d_bind::TransformH3D> get_transform_bind() const;
	void set_transform_bind(const Ref<godot_h3d_bind::TransformH3D> &p_transform);

	Ref<WorldH3D> get_world() const { return _world; }
	void set_world(const Ref<WorldH3D> &p_world) { _world = p_world; }
};
