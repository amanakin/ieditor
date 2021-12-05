#ifndef LAYOUT_MANAGER_HEADER
#define LAYOUT_MANAGER_HEADER

#include <layout.h>

struct LayoutManager: public WidgetManager {
    LayoutManager(const Vector2i&size, const Vector2i& pos);

    void addLayout(const Vector2i& size);
    Layout* getCurrLayout();

private:
    Layout* currLayout;
};

#endif // LAYOUT_MANAGER_HEADER
