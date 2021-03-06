// selector.cc

#include <selector.h>
#include <button.h>
#include <algorithm>

const Color Selector::MainColor(132, 132, 168);
const Color Selector::HoverColor(182, 182, 218);
const Color Selector::PressColor(82, 82, 118);

Selector::Selector(const Vector2f& size, const Vector2f& pos,
                   const std::string& name, const Vector2f& buttonSize,
                   float charSize) : 
    WidgetManager(size, pos, nullptr),
    buttonSize(buttonSize),
    isPressed(false),
    charSize(charSize) {

    mainButton = new AnimatedButtonRect(
        [this]() {
            if (this->isPressed) {
                this->hideButtons();
            } else {
                this->showButtons();
            }

            isPressed = !isPressed;
        },
        new FramesText(name, MainColor, HoverColor, PressColor,
                       Colors::WHITE, size, charSize, 1),
        size, Vector2f(0, 0)
    );

    subWidgets.push_back(mainButton);
}

bool Selector::testMouse(const Vector2f& relPosEvent) {
    if (isPressed) {
        for (auto& subWidget: subWidgets) {
            if (subWidget->testMouse(relPosEvent - subWidget->pos)) {
                return true;
            }
        }

        return false;
    } else {
        return mainButton->testMouse(relPosEvent);
    }
}

void Selector::update() {
    if (!isFocus) {
        isPressed = false;
        hideButtons();
    }

    WidgetManager::update();
}

void Selector::addButton(Widget* button) {
    if (button == nullptr) {
        return;
    }

    button->pos = Vector2f(0, mainButton->size.y + (subWidgets.size() - 1) * buttonSize.y);
    subWidgets.push_back(button);

    hideButtons();
}

void Selector::showButtons() {
    size = Vector2f(std::max(mainButton->size.x, buttonSize.x), mainButton->size.y + (subWidgets.size() - 1) * buttonSize.y);

    activateSubWidgets();
}

void Selector::hideButtons() {
    size = mainButton->size;

    deActivateSubWidgets();
}

void Selector::deActivateSubWidgets() {
    for (auto& subWidget: subWidgets) {
        subWidget->isActive = false;
    }

    mainButton->isActive = true;
}

void Selector::activateSubWidgets() {
    for (auto& subWidget: subWidgets) {
        subWidget->isActive = true;
    }
}
