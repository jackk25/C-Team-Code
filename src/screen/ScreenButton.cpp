#include "vex.h"
#include "screen/ScreenButton.h"

void ScreenButton::draw(){
    int width = p2.x-p1.x;
    int height = p2.y-p1.y;

    Brain.Screen.setPenColor(outlineColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.drawRectangle(p1.x, p1.y, width, height);

    // Center aligned horizontally and vertically (Thanks Kayla!)
    Brain.Screen.printAt(
        p1.x + (width/2 - (Brain.Screen.getStringWidth(buttonText.c_str())/2)), 
        p1.y + (height / 2), buttonText.c_str()
    );

    // Resetting the colors
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(white);
}

ScreenButton::ScreenButton(int id, Point topLeftPosition, void (*inputFunc)(int id), std::string text, int width, int height){
    p1 = topLeftPosition;

    //Auto Size Support
    if(!buttonText.empty()){
        if(width == 0){
            width = Brain.Screen.getStringWidth(buttonText.c_str());;
        }
        if(height == 0){
            height = Brain.Screen.getStringHeight(buttonText.c_str());
        }
    }

    p2.x = p1.x + width;
    p2.y = p1.y - height;

    execute = inputFunc;
    buttonText = text;
    buttonid = id;
}

void ScreenButton::isWithin(Point touchPoint){
    if(touchPoint.y <= p1.y && touchPoint.y >= p2.y && touchPoint.x >= p1.x && touchPoint.x <= p2.x){
        execute(this->buttonid);
    }
}

std::string ScreenButton::getText(){
    return buttonText;
}

void ScreenButton::setPosition(Point position){
    p1 = position;
}

void ScreenButton::setText(std::string input){
    buttonText = input;
}

void ScreenButton::setOutlineColor(vex::color color){
    outlineColor = color;
}

void ScreenButton::setFillColor(vex::color color){
    fillColor = color;
}

void ScreenButton::setCallback(void (*callback)(int id)){
    execute = callback;
}
