// tool.cc

#include <tool.h>

Tool::~Tool()
{}

void Tool::onMove(Layout& layout, const Vector2i& oldPos, const Vector2i& newPos)
{}

void Tool::onPress(Layout& layout, const Vector2i& pos)
{}

void Tool::onRelease(Layout& layout, const Vector2i& pos)
{}
