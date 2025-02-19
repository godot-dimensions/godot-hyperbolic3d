#include "transform_h3d_bind.h"

void godot_h3d_bind::TransformH3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_gyration"), &TransformH3D::get_gyration);
	ClassDB::bind_method(D_METHOD("set_gyration", "gyration"), &TransformH3D::set_gyration);
	ADD_PROPERTY(PropertyInfo(Variant::QUATERNION, "gyration"), "set_gyration", "get_gyration");

	ClassDB::bind_method(D_METHOD("get_position"), &TransformH3D::get_position);
	ClassDB::bind_method(D_METHOD("set_position", "position"), &TransformH3D::set_position);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
}
