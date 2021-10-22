// event.cc

#include <cassert>

#include <event.h>
#include <graphlib.h>

Event::MouseClickEvent::MouseClickEvent(const Vector2i& pos, Mouse::Button button) :
    pos(pos), button(button)
{}

Event::MouseHoverEvent::MouseHoverEvent(const Vector2i& from, const Vector2i& to) :
    from(from), to(to)
{}

Event::MouseDragEvent::MouseDragEvent(const Vector2i& from, const Vector2i& to, Mouse::Button button) :
    from(from), to(to), button(button)
{}

//*************************************************************

Event::Event()
{}

Event::Event(const Type type) :
    type(type)
{}

Event::Event(const Type type, const MouseClickEvent& mouseClick) :
    type(type), mouseClick(mouseClick)
{}

Event::Event(const Type type, const MouseHoverEvent& mouseHover) :
    type(type), mouseHover(mouseHover)
{}


Event::Event(const Type type, const MouseDragEvent& mouseDrag) : 
    type(type), mouseDrag(mouseDrag)
{}

Event::Event(const Type type, const Keyboard::Key& key) :
    type(type), key(key)
{}

//*************************************************************

EventManager::EventManager(MLWindow* window) :
    window(window) {
    
    assert(window != nullptr);

    printf("event manager ok\n");

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
                event.mouseClick = Event::MouseClickEvent(newMousePos, button);

                return true;
            } else {
                
                if (isMousePosChanged) {
                    event.type = Event::Type::MouseButtonDragged;
                    event.mouseDrag = Event::MouseDragEvent(mousePos, newMousePos, button);

                    mousePos = newMousePos;

                    return true;
                }
            }
        // Button wasn't pressed
        } else {
            if (isButtonPressed[button]) {
                isButtonPressed[button] = false;

                event.type = Event::Type::MouseButtonReleased;
                event.mouseClick = Event::MouseClickEvent(newMousePos, button);

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
        event.mouseHover = Event::MouseHoverEvent(mousePos, newMousePos);

        mousePos = newMousePos;

        return true;
    }
        
    return false;

}


//*************************************************************
