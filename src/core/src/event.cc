// event.cc

#include <cassert>

#include <event.h>
#include <graphlib.h>
#include <widget.h>

//*************************************************************

bool Keyboard::IsLetter(enum Key key) {
    return key >= Key::A && key <= Key::Z;
}

bool Keyboard::IsSpecChar(enum Key key) {
    return (key == Keyboard::Key::Space     ||
            key == Keyboard::Key::Tilde     ||
            key == Keyboard::Key::Semicolon ||
            key == Keyboard::Key::Slash     || 
            key == Keyboard::Key::Comma     ||
            key == Keyboard::Key::Dot);
}

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

    int i = 0;
    keyboardMap[i++] = Keyboard::Key::A;
    keyboardMap[i++] = Keyboard::Key::B;
    keyboardMap[i++] = Keyboard::Key::C;
    keyboardMap[i++] = Keyboard::Key::D;
    keyboardMap[i++] = Keyboard::Key::E;
    keyboardMap[i++] = Keyboard::Key::F;
    keyboardMap[i++] = Keyboard::Key::G;
    keyboardMap[i++] = Keyboard::Key::H;
    keyboardMap[i++] = Keyboard::Key::I;
    keyboardMap[i++] = Keyboard::Key::J;
    keyboardMap[i++] = Keyboard::Key::K;
    keyboardMap[i++] = Keyboard::Key::L;
    keyboardMap[i++] = Keyboard::Key::M;
    keyboardMap[i++] = Keyboard::Key::N;
    keyboardMap[i++] = Keyboard::Key::O;
    keyboardMap[i++] = Keyboard::Key::P;
    keyboardMap[i++] = Keyboard::Key::Q;
    keyboardMap[i++] = Keyboard::Key::R;
    keyboardMap[i++] = Keyboard::Key::S;
    keyboardMap[i++] = Keyboard::Key::T;
    keyboardMap[i++] = Keyboard::Key::U;
    keyboardMap[i++] = Keyboard::Key::V;
    keyboardMap[i++] = Keyboard::Key::W;
    keyboardMap[i++] = Keyboard::Key::X;
    keyboardMap[i++] = Keyboard::Key::Y;
    keyboardMap[i++] = Keyboard::Key::Z;
    keyboardMap[i++] = Keyboard::Key::Space;
    keyboardMap[i++] = Keyboard::Key::Slash;
    keyboardMap[i++] = Keyboard::Key::Comma;
    keyboardMap[i++] = Keyboard::Key::Dot;
    keyboardMap[i++] = Keyboard::Key::Semicolon;
    keyboardMap[i++] = Keyboard::Key::Tilde;
    keyboardMap[i++] = Keyboard::Key::Num0;
    keyboardMap[i++] = Keyboard::Key::Num1;
    keyboardMap[i++] = Keyboard::Key::Num2;
    keyboardMap[i++] = Keyboard::Key::Num3;
    keyboardMap[i++] = Keyboard::Key::Num4;
    keyboardMap[i++] = Keyboard::Key::Num5;
    keyboardMap[i++] = Keyboard::Key::Num6;
    keyboardMap[i++] = Keyboard::Key::Num7;
    keyboardMap[i++] = Keyboard::Key::Num8;
    keyboardMap[i++] = Keyboard::Key::Num9;
    keyboardMap[i++] = Keyboard::Key::Left;
    keyboardMap[i++] = Keyboard::Key::Right;
    keyboardMap[i++] = Keyboard::Key::Up;
    keyboardMap[i++] = Keyboard::Key::Down;
    keyboardMap[i++] = Keyboard::Key::Enter;
    keyboardMap[i++] = Keyboard::Key::Backspace;
    keyboardMap[i++] = Keyboard::Key::LControl;
    keyboardMap[i++] = Keyboard::Key::LShift;
    keyboardMap[i++] = Keyboard::Key::LAlt;
    keyboardMap[i++] = Keyboard::Key::LSystem;
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

    for (size_t idx = 0; idx < keyboardMap.size(); ++idx) {
        auto key = static_cast<Keyboard::Key>(keyboardMap[idx]);

        if (window->isKeyPressed(key)) {

            if (!isKeyPressed[idx]) {
                isKeyPressed[idx] = true;
                
                rootWidget->onKeyboard(
                    Event::KeyClick(Event::Type::KeyboardKeyPressed, key)
                );

                return true;
            }

        } else {
            if (isKeyPressed[idx]) { 
                isKeyPressed[idx] = false;

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
