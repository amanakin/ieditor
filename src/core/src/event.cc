// event.cc

#include <cassert>

#include <event.h>
#include <graphlib.h>

Event::MouseEvent::Click::Click(Mouse::Button button) :
    button(button)
{}

Event::MouseEvent::Hover::Hover(const Vector2i& newPos) :
    newPos(newPos)
{}

Event::MouseEvent::Drag::Drag(const Vector2i& newPos, Mouse::Button button) :
    newPos(newPos), button(button)
{}

//*************************************************************

Event::MouseEvent::MouseEvent(const Vector2i& pos, const Click& click) :
    pos(pos), click(click)
{}

Event::MouseEvent::MouseEvent(const Vector2i& pos, const Hover& hover) :
    pos(pos), hover(hover)
{}

Event::MouseEvent::MouseEvent(const Vector2i& pos, const Drag& drag) :
    pos(pos), drag(drag)
{}

//*************************************************************

Event::Event()
{}

Event::Event(const Type type) :
    type(type)
{}

Event::Event(const Type type, const Event::MouseEvent& mouseEvent) :
    type(type), mouse(mouseEvent)
{}

Event::Event(const Type type, const Keyboard::Key& key) :
    type(type), key(key)
{}

//*************************************************************

EventManager::EventManager(MLWindow* window) :
    window(window) {
    
    assert(window != nullptr);

    mousePos = window->getMousePosition();


    for (size_t idx = 0; idx < isKeyPressed.size(); ++idx) {
        isKeyPressed[idx] = window->isKeyPressed(static_cast<Keyboard::Key>(idx));
    }

    for (size_t idx = 0; idx < isButtonPressed.size(); ++idx) {
        isButtonPressed[idx] = window->isButtonPressed(static_cast<Mouse::Button>(idx));
    }
}

bool EventManager::pollEvent(Event& event) {

    if (!window->isOpen()) {
        event.type == Event::Type::WindowClosed;

        return true;
    }

    Vector2i newMousePos = window->getMousePosition();

    bool isMousePosChanged = newMousePos != mousePos;

    for (size_t idx = 0; idx < isButtonPressed.size(); ++idx) {
        auto button = static_cast<Mouse::Button>(idx);

        if (window->isButtonPressed(button)) {
            
            if (!isButtonPressed[idx]) {
                isButtonPressed[idx] = true;
                
                event.type = Event::Type::MouseButtonPressed;
                event.mouse = Event::MouseEvent(newMousePos, Event::MouseEvent::Click(button));

                return true;
            } else {
                
                if (isMousePosChanged) {
                    event.type = Event::Type::MouseButtonDragged;
                    event.mouse = Event::MouseEvent(mousePos, Event::MouseEvent::Drag(newMousePos, button));

                    mousePos = newMousePos;

                    return true;
                }
            }
        // Button wasn't pressed
        } else {
            if (isButtonPressed[button]) {
                isButtonPressed[button] = false;

                event.type = Event::Type::MouseButtonReleased;
                event.mouse = Event::MouseEvent(newMousePos, Event::MouseEvent::Click(button));

                return true;
            }
        }
    }

    for (size_t idx = 0; idx < isKeyPressed.size(); ++idx) {
        auto key = static_cast<Keyboard::Key>(idx);

        if (window->isKeyPressed(key)) {

            if (!isKeyPressed[idx]) {
                isKeyPressed[idx] = true;

                event.type = Event::Type::KeyboardKeyPressed;
                event.key = key;

                return true;
            }

        } else {
            if (isKeyPressed[key]) { 
                isKeyPressed[key] = false;

                event.type = Event::Type::KeyboardKeyReleased;
                event.key = key;

                return true;
            }
        }
    }

    if (isMousePosChanged) {
        event.type = Event::Type::MouseHovered;
        event.mouse = Event::MouseEvent(mousePos, Event::MouseEvent::Hover(newMousePos));

        mousePos = newMousePos;

        return true;
    }
        
    return false;

}


//*************************************************************
