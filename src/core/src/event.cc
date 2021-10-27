// event.cc

#include <cassert>

#include <event.h>
#include <graphlib.h>
#include <widget.h>

//*************************************************************

Event::MouseClick::MouseClick(const Type type, const Vector2i& mousePos, const Mouse::Button button) :
    mousePos(mousePos), button(button), type(type)
{}

Event::MouseHover::MouseHover(const Vector2i& prevPos, const Vector2i& currPos) :
    prevPos(prevPos), currPos(currPos)
{}

Event::MouseDrag::MouseDrag(const Vector2i& prevPos, const Vector2i& currPos, const Mouse::Button button) :
    prevPos(prevPos), currPos(currPos), button(button)
{}

Event::KeyClick::KeyClick(const Type type, const Keyboard::Key key) :
    key(key), type(type)
{}

//*************************************************************

EventManager::EventManager(MLWindow* window, RootWidget* rootWidget) :
    window(window),
    rootWidget(rootWidget) {
    
    assert(window != nullptr);
    assert(rootWidget != nullptr);

    mousePos = window->getMousePosition();

    for (size_t idx = 0; idx < isKeyPressed.size(); ++idx) {
        isKeyPressed[idx] = window->isKeyPressed(static_cast<Keyboard::Key>(idx));
    }

    for (size_t idx = 0; idx < isButtonPressed.size(); ++idx) {
        isButtonPressed[idx] = window->isButtonPressed(static_cast<Mouse::Button>(idx));
    }
}

bool EventManager::pollEvent() {

    Vector2i newMousePos = window->getMousePosition();

    bool isMousePosChanged = newMousePos != mousePos;

    for (size_t idx = 0; idx < isButtonPressed.size(); ++idx) {
        auto button = static_cast<Mouse::Button>(idx);

        if (window->isButtonPressed(button)) {
            
            if (!isButtonPressed[idx]) {
                isButtonPressed[idx] = true;

                rootWidget->onMouseClick(
                    Event::MouseClick(Event::Type::MouseButtonPressed, newMousePos, button),
                    rootWidget->pos
                );

                mousePos = newMousePos;

                return true;
            } else {
                
                if (isMousePosChanged) {
                    
                    rootWidget->onMouseDrag(
                        Event::MouseDrag(mousePos, newMousePos, button),
                        rootWidget->pos
                    );

                    mousePos = newMousePos;

                    return true;
                }
            }
        // Button wasn't pressed
        } else {
            if (isButtonPressed[button]) {
                isButtonPressed[button] = false;

                rootWidget->onMouseClick(
                    Event::MouseClick(Event::Type::MouseButtonReleased, newMousePos, button),
                    rootWidget->pos
                );

                mousePos = newMousePos;

                return true;
            }
        }
    }

    for (size_t idx = 0; idx < isKeyPressed.size(); ++idx) {
        auto key = static_cast<Keyboard::Key>(idx);

        if (window->isKeyPressed(key)) {

            if (!isKeyPressed[idx]) {
                isKeyPressed[idx] = true;
                
                rootWidget->onKeyboard(
                    Event::KeyClick(Event::Type::KeyboardKeyPressed, key)
                );

                return true;
            }

        } else {
            if (isKeyPressed[key]) { 
                isKeyPressed[key] = false;

                rootWidget->onKeyboard(
                    Event::KeyClick(Event::Type::KeyboardKeyReleased, key)
                );

                return true;
            }
        }
    }

    if (isMousePosChanged) {

        rootWidget->onMouseHover(
            Event::MouseHover(mousePos, newMousePos),
            rootWidget->pos
        );

        mousePos = newMousePos;

        return true;
    }
        
    return false;

}

//*************************************************************
