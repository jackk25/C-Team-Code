#include "vex.h"
#include "screen/ScreenButtonBuilder.h"

ButtonBuilder ButtonBuilder::id(int id){
    button.setId(id);
    return *this;
}

ButtonBuilder ButtonBuilder::dimensions(int width, int height){
    button.setDimensions(60, 60);
    return *this;
}

ButtonBuilder ButtonBuilder::text(std::string text){
    button.setText(text);
    return *this;
}

ButtonBuilder ButtonBuilder::outlineColor(vex::color color){
    button.setOutlineColor(color);
    return *this;
}

ButtonBuilder ButtonBuilder::fillColor(vex::color color){
    button.setFillColor(color);
    return *this;
}

ButtonBuilder ButtonBuilder::callback(void (*callback)(int)){
    button.setCallback(callback);
    return *this;
}

ScreenButton ButtonBuilder::build(){
    ScreenButton& result = this->button;
    this->reset();
    return result;
}

void ButtonBuilder::reset(){
    button = ScreenButton();
}