#ifndef TOOL_HEADER
#define TOOL_HEADER

#include <graphlib.h>
#include <layout.h>

struct Tool {
    virtual ~Tool();

    // Everywhere relative position to layout
    virtual void onPress(Layout& layout, const Vector2f& pos);
    virtual void onRelease(Layout& layout, const Vector2f& pos);
    virtual void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos);
};

#endif // TOOL_HEADER
