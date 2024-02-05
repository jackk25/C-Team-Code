#include "ScreenButton.h"
#include "../vex.h"

class ButtonBuilder {
    private:
        ScreenButton button;
    public:
        ButtonBuilder();
        ButtonBuilder id(int id);
        ButtonBuilder position(Point p1);
        ButtonBuilder dimensions(int width, int height);
        ButtonBuilder text(std::string text);
        ButtonBuilder outlineColor(vex::color color);
        ButtonBuilder fillColor(vex::color color);
        ButtonBuilder callback(void (*callback)(int));
        ScreenButton build();
        void reset();
};