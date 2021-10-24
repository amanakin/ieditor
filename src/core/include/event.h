#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <array>

#include <vector2.h>

namespace Mouse {
    enum Button {
        Left,
        Right,
        SIZE
    };
};

//*************************************************************

namespace Keyboard {
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
    struct MouseEvent {
        struct Click {
            Click(Mouse::Button button);

            Mouse::Button button;
        };

        struct Hover {
            Hover(const Vector2i& newPos);

            Vector2i newPos;
        };

        struct Drag {
            Drag(const Vector2i& newPos, Mouse::Button button);

            Vector2i newPos;
            Mouse::Button button;
        };

        MouseEvent(const Vector2i& pos, const Click& click);
        MouseEvent(const Vector2i& pos, const Hover& hover);
        MouseEvent(const Vector2i& pos, const Drag& drag);

        union {
            Click click;
            Hover hover;
            Drag drag;
        };
        Vector2i pos;
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
    Event(const Type, const MouseEvent&);
    Event(const Type, const Keyboard::Key&);

    Type type;
    
    union {
        MouseEvent mouse;
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
