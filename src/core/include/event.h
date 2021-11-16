#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <array>

#include <vector2.h>

//*************************************************************

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
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Left,
        Right,
        Space,
        Enter,
        BackSpace,
        SIZE,
    };

    bool IsChar(enum Key key);

    char GetChar(enum Key key);

};

//*************************************************************

namespace Event {
    
    enum class Type {
        // MouseClick
        MouseButtonPressed,
        MouseButtonReleased,
        // MouseHover
        MouseHovered,
        // MouseDrag
        MouseButtonDragged,
        // KeyClick
        KeyboardKeyPressed,
        KeyboardKeyReleased,
    };

    struct MouseClick {
        MouseClick(const Type type, const Vector2i& mousePos, const Mouse::Button button);

        Type type;
        Vector2i mousePos;
        Mouse::Button button;
    };

    struct MouseHover {
        MouseHover(const Vector2i& prevPos, const Vector2i& currPos);

        Vector2i prevPos;
        Vector2i currPos;
    };

    struct MouseDrag {
        MouseDrag(const Vector2i& prevPos, const Vector2i& currPos, const Mouse::Button button);

        Vector2i prevPos;
        Vector2i currPos;    
        Mouse::Button button;
    };

    struct KeyClick {
        KeyClick(const Type type, const Keyboard::Key key);
        
        Type type;
        Keyboard::Key key;
    };

};

//*************************************************************

struct MLWindow;
struct RootWidget;

struct EventManager {
    EventManager(MLWindow* window, RootWidget* rootWidget);

    // poll events and push them to widget
    bool pollEvent();

private:
    std::array<bool, Mouse::Button::SIZE> isButtonPressed;
    std::array<bool, Keyboard::Key::SIZE> isKeyPressed;

    Vector2i mousePos;

    MLWindow* window;
    RootWidget* rootWidget;
};

//*************************************************************

#endif // EVENT_HEADER
