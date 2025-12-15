# Godot Hyperbolic 3D

NodeH3D and other hyperbolic 3-dimensional types for making hyperbolic 3D games in Godot.

NOTE: This module is very much incomplete and has almost nothing implemented yet.

## Installation

First, have all the Godot dependencies installed on your computer as per the
[official instructions](https://docs.godotengine.org/en/stable/engine_details/development/compiling/index.html).

If you want all of the Godot Dimensions modules at once, you can grab a
branch of [our Godot fork](https://github.com/godot-dimensions/godot/tree/dimensions-latest).

```shell
git clone https://github.com/godot-dimensions/godot godot-dimensions
cd godot-dimensions
# First, make sure you can compile regular Godot.
scons
# Then, switch to the dimensions branch and download the submodules.
git switch dimensions-latest
git submodule update --init --recursive
scons
# Re-run the `scons` command to re-compile if you make changes.
```

Alternatively, if you only want hyperbolic 3D, you can start with any clone
of Godot Engine and add this module to it:

```shell
cd modules
git clone https://github.com/godot-dimensions/godot-hyperbolic3d hyperbolic3d
# Make sure the folder is named `hyperbolic3d`, not `godot-hyperbolic3d`!
cd ..
scons
# Re-run the `scons` command to re-compile if you make changes.
```

It should now be successfully compiled, and you can run the executable in the `bin` folder.

Alternatively, Godot Hyperbolic 3D can be compiled as a GDExtension. The module approach
is recommended, but GDExtension allows you to avoid recompiling Godot.
To compile as a GDExtension, clone this repository anywhere, with submodules,
and run `scons target=editor`. You can open the repository's `project.godot`
in Godot to test the GDExtension, and copy the `addons/hyperbolic3d` to your own project.
