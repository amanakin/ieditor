#ifndef TOOL_HEADER
#define TOOL_HEADER

#include <graphlib.h>
#include <layout.h>
#include <picture_manager.h>

struct Tool {
    virtual ~Tool();

    // Everywhere relative position to layout
    virtual void onPress(Layout& layout, const Vector2f& pos);
    virtual void onRelease(Layout& layout, const Vector2f& pos);
    virtual void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos);

    virtual std::string_view getName() const;

    virtual bool isIconExist() const;
    virtual DefaultPictures::Picture getIcon() const;
};

#endif // TOOL_HEADER
