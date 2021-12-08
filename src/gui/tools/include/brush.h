#ifndef BRUSH_HEADER
#define BRUSH_HEADER

#include <tool.h>

struct Brush: public Tool {
    void onPress(Layout& layout, const Vector2f& pos)                           override;
    void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) override;

    std::string_view getName() const override;
};

#endif // BRUSH

