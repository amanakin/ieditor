#pragma once

#include <color.h>
#include <EditorPluginAPI/plugin_std.hpp>
#include <graphlib.h>

PRGBA ConvertColorToPlugin(const Color& color);
Color ConvertColorFromPlugin(const PRGBA& color);

ML::BlendMode ConvertBlendMode(PBlendMode pBlendMode);

Vector2f ConvertVectorFromPlugin(const PVec2f& pVec);
PVec2f ConvertVectorToPlugin(const Vector2f& vec);
