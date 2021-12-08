// tool.cc

#include <tool.h>

Tool::~Tool()
{}

void Tool::onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos)
{}

void Tool::onPress(Layout& layout, const Vector2f& pos)
{}

void Tool::onRelease(Layout& layout, const Vector2f& pos)
{}

std::string_view Tool::getName() const {
    return "Error tool name";
}

bool Tool::isIconExist() const {
    return false;
}

DefaultPictures::Picture Tool::getIcon() const {
    return DefaultPictures::Empty;
}
