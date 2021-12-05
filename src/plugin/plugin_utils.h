#pragma once

#include <color.h>
#include <EditorPluginAPI/plugin_std.hpp>
#include <graphlib.h>

PRGBA ConvertColorToPlugin(const Color& color);
Color ConvertColorFromPlugin(const PRGBA& color);

MLBlendMode ConvertBlendMode(PBlendMode pBlendMode);

Vector2i ConvertVectorFromPlugin(const PVec2f& pVec);
PVec2f ConvertVectorToPlugin(const Vector2i& vec);
