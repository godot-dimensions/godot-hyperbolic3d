#pragma once

#include "../../godot_hyperbolic3d_defines.h"

#if GDEXTENSION
#include <godot_cpp/classes/image_texture.hpp>
#elif GODOT_MODULE
#include "scene/resources/image_texture.h"
#endif

Ref<ImageTexture> _generate_editor_h3d_icon(const String &p_icon_name);
