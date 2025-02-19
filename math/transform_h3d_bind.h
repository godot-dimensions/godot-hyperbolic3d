#pragma once

#include "transform_h3d.h"

#if GDEXTENSION
#include <godot_cpp/classes/ref_counted.hpp>
#elif GODOT_MODULE
#include "core/object/ref_counted.h"
#endif

namespace godot_h3d_bind {
class TransformH3D : public RefCounted {
	GDCLASS(TransformH3D, RefCounted);

	::TransformH3D _transform;

protected:
	static void _bind_methods();

public:
	// Trivial getters and setters.
	Quaternion get_gyration() const { return _transform.get_gyration(); }
	void set_gyration(const Quaternion &p_gyration) { _transform.set_gyration(p_gyration); }

	Vector3 get_position() const { return _transform.get_position(); }
	void set_position(const Vector3 &p_position) { _transform.set_position(p_position); }

	::TransformH3D get_transform() const { return _transform; }
	void set_transform(const ::TransformH3D &p_transform) { _transform = p_transform; }
};
} // namespace godot_h3d_bind
