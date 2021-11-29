#ifndef BRUSH_HEADER
#define BRUSH_HEADER

#include <tool.h>

struct Brush: public Tool {
    void onPress(Layout& layout, const Vector2i& pos) override;
    void onMove(Layout& layout, const Vector2i& oldPos, const Vector2i& newPos) override;
};

#endif // BRUSH

