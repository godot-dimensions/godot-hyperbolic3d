#include "world_h3d.h"

void WorldH3D::set_tile_valence(const double p_tile_valence) {
	set_tile_valence_and_sides(p_tile_valence, _tile_sides);
}

void WorldH3D::set_tile_sides(const double p_tile_sides) {
	set_tile_valence_and_sides(_tile_valence, p_tile_sides);
}

// This tiny epsilon is added at the end to hide small gaps between tiles.
constexpr double KLEIN_EPSILON = CMP_EPSILON;

void WorldH3D::set_tile_valence_and_sides(const double p_tile_valence, const double p_tile_sides) {
	_tile_valence = p_tile_valence;
	_tile_sides = p_tile_sides;
	const double half_valence_angle = Math_PI / _tile_valence;
	const double half_side_angle = Math_PI / _tile_sides;
	const double angle_sum = half_valence_angle + half_side_angle;
	if (Math::is_equal_approx(Math_PI / 2.0, angle_sum)) {
		_curvature_class = CURVATURE_EUCLIDEAN;
		_klein_scale = 1.0;
		_tile_width = 2.0;
	} else {
		_curvature_class = (angle_sum < Math_PI / 2.0) ? CURVATURE_HYPERBOLIC : CURVATURE_SPHERICAL;
		const double ratio = Math::cos(half_valence_angle) / Math::sin(half_side_angle);
		_tile_width = Math::sqrt(Math::abs(ratio * ratio - 1.0)) / ratio;
		_klein_scale = _tile_width + (KLEIN_EPSILON / p_tile_valence);
	}
}

void WorldH3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_is_main_world"), &WorldH3D::get_is_main_world);
	ClassDB::bind_method(D_METHOD("set_is_main_world", "is_main_world"), &WorldH3D::set_is_main_world);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_main_world"), "set_is_main_world", "get_is_main_world");

	ClassDB::bind_method(D_METHOD("get_tile_valence"), &WorldH3D::get_tile_valence);
	ClassDB::bind_method(D_METHOD("set_tile_valence", "tile_valence"), &WorldH3D::set_tile_valence);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tile_valence", PROPERTY_HINT_RANGE, "3,10,1,or_greater"), "set_tile_valence", "get_tile_valence");

	ClassDB::bind_method(D_METHOD("get_tile_sides"), &WorldH3D::get_tile_sides);
	ClassDB::bind_method(D_METHOD("set_tile_sides", "tile_sides"), &WorldH3D::set_tile_sides);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tile_sides", PROPERTY_HINT_RANGE, "3,10,1,or_greater"), "set_tile_sides", "get_tile_sides");

	ClassDB::bind_method(D_METHOD("set_tile_valence_and_sides", "tile_valence", "tile_sides"), &WorldH3D::set_tile_valence_and_sides, DEFVAL(4.0));
	ClassDB::bind_method(D_METHOD("get_curvature_class"), &WorldH3D::get_curvature_class);
	ClassDB::bind_method(D_METHOD("get_klein_scale"), &WorldH3D::get_klein_scale);
	ClassDB::bind_method(D_METHOD("get_tile_width"), &WorldH3D::get_tile_width);
	ClassDB::bind_method(D_METHOD("get_tiles_per_vertex"), &WorldH3D::get_tiles_per_vertex);
	ClassDB::bind_method(D_METHOD("get_sides_per_tile"), &WorldH3D::get_sides_per_tile);

	BIND_ENUM_CONSTANT(CURVATURE_HYPERBOLIC);
	BIND_ENUM_CONSTANT(CURVATURE_EUCLIDEAN);
	BIND_ENUM_CONSTANT(CURVATURE_SPHERICAL);
}
