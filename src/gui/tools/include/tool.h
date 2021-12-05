#ifndef TOOL_HEADER
#define TOOL_HEADER

#include <graphlib.h>
#include <layout.h>

struct Tool {
    virtual ~Tool();

    // Everywhere relative position to layout
    virtual void onPress(Layout& layout, const Vector2i& pos);
    virtual void onRelease(Layout& layout, const Vector2i& pos);
    virtual void onMove(Layout& layout, const Vector2i& oldPos, const Vector2i& newPos);
};

#endif // TOOL_HEADER
