#pragma once

#include "../godot_hyperbolic3d_defines.h"

struct _NO_DISCARD_ TransformH3D {
	// This is the post-rotation as a result of holonomy, as well as regular rotation.
	Quaternion _gyration;
	// This is the hyperbolic offset vector or position on the Poincaré disk.
	Vector3 _position;

public:
	// Trivial getters and setters.
	Quaternion get_gyration() const { return _gyration; }
	void set_gyration(const Quaternion &p_gyration) { _gyration = p_gyration; }

	Vector3 get_position() const { return _position; }
	void set_position(const Vector3 &p_position) { _position = p_position; }
};
