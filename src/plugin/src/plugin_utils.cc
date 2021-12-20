// utils.cc

#include <cassert>

#include <plugin_utils.h>

PUPPY::RGBA ConvertColorToPlugin(const Color& color) {
    return PUPPY::RGBA(color.x * 255, color.y * 255, color.z * 255, color.t * 255);
}

Color ConvertColorFromPlugin(const PUPPY::RGBA& color) {
    return Color(color.r, color.g, color.b, color.a);
}

ML::BlendMode ConvertRenderModeFromPlugin(const PUPPY::RenderMode& renderMode) {
    switch (renderMode.blend) {
    case PUPPY::BlendMode::ALPHA_BLEND:
        return ML::BlendMode::BlendAlpha;
    case PUPPY::BlendMode::COPY:
        return ML::BlendMode::BlendNone;
    default:
        assert("Wrong blend mode in convering");
        return ML::BlendMode::BlendNone;
    }
}

Vector2f ConvertVectorFromPlugin(const PUPPY::Vec2f& pVec) {
    return {pVec.x, pVec.y};
}

PUPPY::Vec2f ConvertVectorToPlugin(const Vector2f& vec) {
    return {vec.x, vec.y};
}


Vector2f PosFromBody(const PUPPY::WBody& body) {
    return ConvertVectorFromPlugin(body.position);
}

Vector2f SizeFromBody(const PUPPY::WBody& body) {
    return ConvertVectorFromPlugin(body.size);
}

PUPPY::WBody WBodyFromVectors(const Vector2f& size, const Vector2f& pos) {
    return PUPPY::WBody(ConvertVectorToPlugin(pos),
                        ConvertVectorToPlugin(size));
}
