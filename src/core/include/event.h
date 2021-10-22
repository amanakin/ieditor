#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <array>

#include <vector2.h>

struct Mouse {
    enum Button {
        Left,
        Right,
        SIZE
    };
};

//*************************************************************

struct Keyboard {
    enum Key {
        W,
        A,
        S,
        D,
        Up,
        Down,
        Left,
        Right,
        SIZE,
    };
};

//*************************************************************

struct Event {
    struct MouseClickEvent {
        MouseClickEvent(const Vector2i& pos, Mouse::Button button);

        Vector2i pos;
        Mouse::Button button;
    };

    struct MouseHoverEvent {
        MouseHoverEvent(const Vector2i& from, const Vector2i& to);

        Vector2i from;
        Vector2i to;
    };

    struct MouseDragEvent {
        MouseDragEvent(const Vector2i& from, const Vector2i& to, Mouse::Button button);

        Vector2i from;
        Vector2i to;
        Mouse::Button button;
    };

    enum class Type {
        // mouseClick
        MouseButtonPressed,
        MouseButtonReleased,
        // mouseHover
        MouseHovered,
        // mouseDrag
        MouseButtonDragged,
        // key
        KeyboardKeyPressed,
        KeyboardKeyReleased,
        // None
        WindowClosed,
    };

    Event();
    Event(const Type);
    Event(const Type, const MouseClickEvent&);
    Event(const Type, const MouseHoverEvent&);
    Event(const Type, const MouseDragEvent&);
    Event(const Type, const Keyboard::Key&);

    Type type;
    
    union {
        MouseClickEvent mouseClick;
        MouseHoverEvent mouseHover;
        MouseDragEvent mouseDrag;
        Keyboard::Key key;
    };
};

//*************************************************************

struct MLWindow;

struct EventManager {
    EventManager(MLWindow* window);

    bool pollEvent(Event& event);

private:
    std::array<bool, Mouse::Button::SIZE> isButtonPressed;
    std::array<bool, Keyboard::Key::SIZE> isKeyPressed;

    Vector2i mousePos;

    MLWindow* window;
};

//*************************************************************

#endif // EVENT_HEADER
