#pragma once

#include <color.h>
#include <plugin_std.hpp>
#include <graphlib.h>

PUPPY::RGBA ConvertColorToPlugin(const Color& color);
Color ConvertColorFromPlugin(const PUPPY::RGBA& color);

ML::BlendMode ConvertRenderModeFromPlugin(const PUPPY::RenderMode& blendMode);

Vector2f ConvertVectorFromPlugin(const PUPPY::Vec2f& pVec);
PUPPY::Vec2f ConvertVectorToPlugin(const Vector2f& vec);
