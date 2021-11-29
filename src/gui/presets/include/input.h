#ifndef INPUT_HEADER
#define INPUT_HEADER

#include <widget.h>
#include <textbar.h>

enum class InputTemplates  {
    None,
    IntNumber,
    FloatNumber,
};



struct InputWidget: public WidgetManager {
    InputWidget(const Vector2i& size, const Vector2i& pos,
                const std::string& name, const Color& buttonColor);

    const std::string& getInput() const;
    void setInput(const std::string& str);
    

private:
    TextBar* textBar;
};

#endif // INPUT_HEADER
