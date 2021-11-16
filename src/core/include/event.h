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
        A = 'A',
        B = 'B',
        C = 'C',
        D = 'D',
        E = 'E',
        F = 'F',
        G = 'G',
        H = 'H',
        I = 'I',
        J = 'J',
        K = 'K',
        L = 'L',
        M = 'M',
        N = 'N',
        O = 'O',
        P = 'P',
        Q = 'Q',
        R = 'R',
        S = 'S',
        T = 'T',
        U = 'U',
        V = 'V',
        W = 'W',
        X = 'X',
        Y = 'Y',
        Z = 'Z',
        Space =     ' ',
        Slash =     '/',     
        Comma =     ',',     
        Dot =       '.',       
        Semicolon = ';',
        Tilde =     '~',
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
        SIZE = 52,
    };

    bool IsLetter(enum Key key);
    bool IsSpecChar(enum Key key);
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

    std::array<int, Keyboard::Key::SIZE> keyboardMap;
    std::array<bool, Keyboard::Key::SIZE> isKeyPressed;

    Vector2i mousePos;

    MLWindow* window;
    RootWidget* rootWidget;
};

//*************************************************************

#endif // EVENT_HEADER
