# This file is for building as a Godot engine module.
def can_build(env, platform):
	return True


def configure(env):
	pass


def get_doc_classes():
	return [
		"NodeH3D",
		"TransformH3D",
		"WorldH3D",
	]


def get_doc_path():
	return "addons/hyper3d/doc_classes"


def get_icons_path():
	return "addons/hyper3d/icons"
