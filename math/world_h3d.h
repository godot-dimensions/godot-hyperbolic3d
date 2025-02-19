#pragma once

#include "../godot_hyper3d_defines.h"

#if GDEXTENSION
#include <godot_cpp/classes/resource.hpp>
#elif GODOT_MODULE
#include "core/io/resource.h"
#endif

// The context in which hyperbolic 3D math takes place.
// Hyperbolic math depends on the curvature of the space, which is stored in WorldH3D.
// Derived from CodeParade's HyperEngine HyperMath designed for the game Hyperbolica.
// https://github.com/HackerPoet/HyperEngine/blob/main/Assets/HyperEngine/HyperMath.cs#L117
class WorldH3D : public Resource {
	GDCLASS(WorldH3D, Resource);

public:
	enum CurvatureClass {
		CURVATURE_HYPERBOLIC = -1,
		CURVATURE_EUCLIDEAN = 0,
		CURVATURE_SPHERICAL = 1,
	};

private:
	CurvatureClass _curvature_class = CURVATURE_EUCLIDEAN;
	double _tile_valence = 4.0;
	double _tile_sides = 4.0;
	double _tile_width = 2.0;
	double _klein_scale = 1.0;
	bool _is_main_world = false;

protected:
	static void _bind_methods();

public:
	bool get_is_main_world() const { return _is_main_world; }
	void set_is_main_world(const bool p_is_main_world) { _is_main_world = p_is_main_world; }

	double get_tile_valence() const { return _tile_valence; }
	void set_tile_valence(const double p_tile_valence);

	double get_tile_sides() const { return _tile_sides; }
	void set_tile_sides(const double p_tile_sides);

	void set_tile_valence_and_sides(const double p_tile_valence, const double p_tile_sides = 4.0);
	// These are not settable directly, but are updated when the tile valence and sides are set.
	CurvatureClass get_curvature_class() const { return _curvature_class; }
	double get_klein_scale() const { return _klein_scale; }
	double get_tile_width() const { return _tile_width; }
	int get_tiles_per_vertex() const { return (int)_tile_valence; }
	int get_sides_per_tile() const { return (int)_tile_sides; }
};

VARIANT_ENUM_CAST(WorldH3D::CurvatureClass);
