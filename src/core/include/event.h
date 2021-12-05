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
        Space,
        Slash,     
        Comma,     
        Dot,       
        Semicolon,
        Tilde,
        LBracket,
        RBracket,
        Quote,
        Num0, 
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Left,
        Right,
        Up,
        Down,
        Enter,
        Backspace,
        LControl,
        LShift,
        LAlt,
        LSystem,
        SIZE,
    };

    bool IsCharacter(enum Key key);
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
        // 
        TextEntered,
    };

    struct MouseClick {
        MouseClick(const Type type, const Vector2f& mousePos, const Mouse::Button button);

        Type type;
        Vector2f mousePos;
        Mouse::Button button;
    };

    struct MouseHover {
        enum class HoverSpecific {
            In,
            Out
        };

        MouseHover(const Vector2f& prevPos, const Vector2f& currPos, HoverSpecific type);

        Vector2f prevPos;
        Vector2f currPos;

        HoverSpecific type;
    };

    struct MouseDrag {
        MouseDrag(const Vector2f& prevPos, const Vector2f& currPos, const Mouse::Button button);

        Vector2f prevPos;
        Vector2f currPos;    
        Mouse::Button button;
    };

    struct KeyClick {
        KeyClick(const Type type, const Keyboard::Key key);
        
        Type type;
        Keyboard::Key key;
        bool control;
        bool alt;
        bool shift;
        bool system;
    };

    struct Text {
        Text(uint32_t unicode);
        
        uint32_t unicode;
    };

};

//*************************************************************

namespace ML {
struct Window;
}
struct RootWidget;

struct EventManager {
    EventManager(ML::Window* window, RootWidget* rootWidget);

    // poll events and push them to widget
    bool pollEvent();

private:
    std::array<bool, Mouse::Button::SIZE> isButtonPressed;
    std::array<bool, Keyboard::Key::SIZE> isKeyPressed;

    Vector2f mousePos;

    ML::Window* window;
    RootWidget* rootWidget;
};

//*************************************************************

#endif // EVENT_HEADER
