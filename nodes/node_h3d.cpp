#include "node_h3d.h"

#if GDEXTENSION
#include <godot_cpp/classes/viewport.hpp>
#elif GODOT_MODULE
#include "scene/main/viewport.h"
#endif

void NodeH3D::_find_or_make_world() {
	Node *parent = get_parent();
	while (parent) {
		NodeH3D *h3d_parent = Object::cast_to<NodeH3D>(parent);
		if (h3d_parent) {
			// If the parent is a NodeH3D, use its world, even if it's null.
			// The parent should automatically get one when added to the tree,
			// but if it's not, then this may be intentional by the user.
			_world = h3d_parent->get_world();
			break;
		}
		Viewport *viewport = Object::cast_to<Viewport>(parent);
		if (viewport) {
			// If we find a Viewport, use its world, or provide one if it doesn't have one.
			if (viewport->has_meta(StringName("world_h3d"))) {
				_world = viewport->get_meta(StringName("world_h3d"));
			} else {
				if (_world.is_null()) {
					_world.instantiate();
				}
				viewport->set_meta(StringName("world_h3d"), _world);
			}
			break;
		}
		parent = parent->get_parent();
	}
}

void NodeH3D::_give_main_world_to_viewport() {
	Viewport *viewport = get_viewport();
	if (viewport) {
		if (viewport->has_meta(StringName("world_h3d"))) {
			// By this point, we know the Viewport has a WorldH3D, but is it marked as main?
			// If ours is marked as main, but the Viewport's is not, then ours takes precedence.
			Ref<WorldH3D> viewport_world = viewport->get_meta(StringName("world_h3d"));
			if (viewport_world->get_is_main_world()) {
				return; // Viewport already has a WorldH3D marked as main.
			}
		}
		// Give the main world to the viewport if it needs one.
		viewport->set_meta(StringName("world_h3d"), _world);
	}
}

void NodeH3D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			if (_world.is_valid() && _world->get_is_main_world()) {
				// This is expected to be the case for the main scene root node.
				_give_main_world_to_viewport();
			} else {
				// If our WorldH3D is not main, try to find another one first.
				// This is expected to happen for prefabs and other non-main scenes.
				// Such sub-scenes still need to do math and stuff when edited.
				_find_or_make_world();
			}
		} break;
	}
}

void NodeH3D::_get_property_list(List<PropertyInfo> *p_list) const {
	for (List<PropertyInfo>::Element *E = p_list->front(); E; E = E->next()) {
		PropertyInfo &prop = E->get();
		if (prop.name == StringName("world")) {
			NodeH3D *parent_h3d = Object::cast_to<NodeH3D>(get_parent());
			if (parent_h3d && parent_h3d->get_world() == _world) {
				// If the parent has the same world, don't save this node's world into the tscn file.
				prop.usage = PROPERTY_USAGE_EDITOR;
			}
		}
	}
	Node::_get_property_list(p_list);
}

Ref<godot_h3d_bind::TransformH3D> NodeH3D::get_transform_bind() const {
	Ref<godot_h3d_bind::TransformH3D> transform_bind;
	transform_bind.instantiate();
	transform_bind->set_transform(_transform);
	return transform_bind;
}

void NodeH3D::set_transform_bind(const Ref<godot_h3d_bind::TransformH3D> &p_transform) {
	_transform = p_transform->get_transform();
}

void NodeH3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_position"), &NodeH3D::get_position);
	ClassDB::bind_method(D_METHOD("set_position", "position"), &NodeH3D::set_position);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");

	ClassDB::bind_method(D_METHOD("get_gyration"), &NodeH3D::get_gyration);
	ClassDB::bind_method(D_METHOD("set_gyration", "gyration"), &NodeH3D::set_gyration);
	ADD_PROPERTY(PropertyInfo(Variant::QUATERNION, "gyration"), "set_gyration", "get_gyration");

	ClassDB::bind_method(D_METHOD("get_transform"), &NodeH3D::get_transform_bind);
	ClassDB::bind_method(D_METHOD("set_transform", "transform"), &NodeH3D::set_transform_bind);

	ClassDB::bind_method(D_METHOD("get_world"), &NodeH3D::get_world);
	ClassDB::bind_method(D_METHOD("set_world", "world"), &NodeH3D::set_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world", PROPERTY_HINT_RESOURCE_TYPE, "WorldH3D"), "set_world", "get_world");
}
