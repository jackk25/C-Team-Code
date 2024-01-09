#include "vex.h"
#include "screen.h"

void ScreenButton::draw(){
    int width = p2.x-p1.x;
    int height = p2.y-p1.y;

    //Auto Size Support
    if(!buttonText.empty()){
        if(width == 0){
            width = Brain.Screen.getStringWidth(buttonText.c_str());
        }
        if(height == 0){
            height = Brain.Screen.getStringHeight(buttonText.c_str());
        }
    }

    Brain.Screen.drawRectangle(p1.x, p1.y, width, height);

    // Center aligned vertically, left aligned horizontally
    Brain.Screen.setCursor(p1.y + (height / 2), p1.x);
    Brain.Screen.print(buttonText.c_str());
}

ScreenButton::ScreenButton(Point topLeftPosition, int width, int height, void (*inputFunc)(), std::string text){
    p1 = topLeftPosition;
    p2.x = p1.x + width;
    p2.y = p1.y - height;

    execute = inputFunc;
    buttonText = text;

    draw();
}

void ScreenButton::isWithin(Point touchPoint){
    if(touchPoint.y <= p1.y && touchPoint.y >= p2.y && touchPoint.x >= p1.x && touchPoint.x <= p2.x){
        execute();
    }
}

std::string ScreenButton::getText(){
    return buttonText;
}

void ScreenButton::setText(std::string input){
    buttonText = input;
    draw();
}

void ScreenContainer::runThroughButtons(){
    Point touchPoint = {Brain.Screen.xPosition(), Brain.Screen.yPosition()};
    for(ScreenButton btn : buttons){
        btn.isWithin(touchPoint);
    }
}

ScreenButton ScreenContainer::createButton(Point p1, void (*execute)(), std::string text, int width, int height){
    ScreenButton btn(p1, width, height, execute, text);
    buttons.push_back(btn);

    return btn;
}