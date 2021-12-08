// utils.cc

#include <cassert>

#include <plugin_utils.h>

PRGBA ConvertColorToPlugin(const Color& color) {
    return PRGBA(color.x * 255, color.y * 255, color.z * 255, color.t * 255);
}

Color ConvertColorFromPlugin(const PRGBA& color) {
    return Color(color.r, color.g, color.b, color.a);
}

ML::BlendMode ConvertBlendMode(PBlendMode pBlendMode) {
    switch (pBlendMode) {
    case PBlendMode::PPBM_ALPHA_BLEND: return ML::BlendMode::BlendAlpha;
    case PBlendMode::PPBM_COPY: return ML::BlendMode::BlendNone;
    default:
        assert("Plugin wrong blend mode");
        return ML::BlendMode::BlendAlpha;
    }
}

Vector2f ConvertVectorFromPlugin(const PVec2f& pVec) {
    return Vector2f(pVec.x, pVec.y);
}

PVec2f ConvertVectorToPlugin(const Vector2f& vec) {
    return PVec2f(vec.x, vec.y);
}
