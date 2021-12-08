#ifndef LAYOUT_MANAGER_HEADER
#define LAYOUT_MANAGER_HEADER

#include <layout.h>
#include <picture_manager.h>

struct LayoutManager: public WidgetManager {
    LayoutManager(const Vector2f&size, const Vector2f& pos, PictureManager& pictManager);

    void addLayout(const Vector2f& size);
    Layout* getCurrLayout();

private:
    Layout* currLayout;
};

#endif // LAYOUT_MANAGER_HEADER
