// event.cc

#include <cassert>

#include <event.h>
#include <graphlib.h>
#include <widget.h>

//*************************************************************

Event::MouseClick::MouseClick(const Type type, const Vector2f& mousePos, const Mouse::Button button) :
    mousePos(mousePos), button(button), type(type)
{}

Event::MouseHover::MouseHover(const Vector2f& prevPos, const Vector2f& currPos, HoverSpecific type) :
    prevPos(prevPos), currPos(currPos), type(type)
{}

Event::MouseDrag::MouseDrag(const Vector2f& prevPos, const Vector2f& currPos, const Mouse::Button button) :
    prevPos(prevPos), currPos(currPos), button(button)
{}

Event::KeyClick::KeyClick(const Type type, const Keyboard::Key key) :
    key(key), type(type)
{}

Event::Text::Text(uint32_t unicode) :
    unicode(unicode)
{}

bool Keyboard::IsCharacter(Keyboard::Key key) {
    if (key >= Key::A && key <= Key::Z) {
        return true;
    }
    if (key >= Key::Space && key <= Key::Num9) {
        return true;
    }
    
    return false;
}

//*************************************************************

EventManager::EventManager(ML::Window* window, RootWidget* rootWidget) :
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

    bool isEvented = false;

    Vector2f newMousePos = window->getMousePosition();

    bool isMousePosChanged = newMousePos != mousePos;

    for (size_t idx = 0; idx < Mouse::Button::SIZE; ++idx) {
        auto button = static_cast<Mouse::Button>(idx);

        if (window->isButtonPressed(button)) {
            
            if (!isButtonPressed[idx]) {
                isButtonPressed[idx] = true;

                if (button == Mouse::Button::Left) {
                    rootWidget->onUnFocus();
                }

                rootWidget->onMouseClick(
                    Event::MouseClick(Event::Type::MouseButtonPressed, newMousePos, button),
                    rootWidget->pos
                );

                isEvented = true;
            } else {
                
                if (isMousePosChanged) {
                    
                    rootWidget->onMouseDrag(
                        Event::MouseDrag(mousePos, newMousePos, button),
                        rootWidget->pos
                    );

                    isEvented = true;
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

                isEvented = true;
            }
        }
    }

    for (size_t idx = 0; idx < Keyboard::SIZE; ++idx) {
        auto key = static_cast<Keyboard::Key>(idx);

        if (window->isKeyPressed(key)) {

            if (!isKeyPressed[idx]) {
                isKeyPressed[idx] = true;

                uint32_t unicode = window->isTextEntered();
                if (!window->isActive()) {
                    return false;
                }

                if (unicode != 0) {
                    rootWidget->onTextEntered(Event::Text(unicode));    
                }

                auto event = Event::KeyClick(Event::Type::KeyboardKeyPressed, key);
                event.control = window->isKeyPressed(Keyboard::Key::LControl);
                event.shift = window->isKeyPressed(Keyboard::Key::LShift);
                event.system = window->isKeyPressed(Keyboard::Key::LSystem);
                event.alt = window->isKeyPressed(Keyboard::Key::LAlt);

                rootWidget->onKeyboard(event);

                isEvented = true;
            }

        } else {
            if (isKeyPressed[idx]) { 
                isKeyPressed[idx] = false;

                rootWidget->onKeyboard(
                    Event::KeyClick(Event::Type::KeyboardKeyReleased, key)
                );

                isEvented = true;
            }
        }
    }

    if (isMousePosChanged) {

        rootWidget->onMouseHover(
            Event::MouseHover(mousePos, newMousePos, Event::MouseHover::HoverSpecific::Out),
            rootWidget->pos
        );

        rootWidget->onMouseHover(
            Event::MouseHover(mousePos, newMousePos, Event::MouseHover::HoverSpecific::In),
            rootWidget->pos
        );

        mousePos = newMousePos;

        isEvented = true;
    }
        
    return isEvented;

}

//*************************************************************
