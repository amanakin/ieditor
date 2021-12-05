#ifndef LAYOUT_MANAGER_HEADER
#define LAYOUT_MANAGER_HEADER

#include <layout.h>

struct LayoutManager: public WidgetManager {
    LayoutManager(const Vector2f&size, const Vector2f& pos);

    void addLayout(const Vector2f& size);
    Layout* getCurrLayout();

private:
    Layout* currLayout;
};

#endif // LAYOUT_MANAGER_HEADER
