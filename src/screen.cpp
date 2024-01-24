#include "vex.h"
#include "screen.h"

void ScreenButton::draw(){
    int width = p2.x-p1.x;
    int height = p2.y-p1.y;

    Brain.Screen.drawRectangle(p1.x, p1.y, width, height);

    // Center aligned horizontally and vertically (Thanks Kayla!)
    Brain.Screen.printAt(
        p1.x + (width/2 - (Brain.Screen.getStringWidth(buttonText.c_str())/2)), 
        p1.y + (height / 2), buttonText.c_str()
    );
}

ScreenButton::ScreenButton(Point topLeftPosition, int width, int height, void (*inputFunc)(int id), std::string text, int id){
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

    draw();
}

void ScreenButton::isWithin(Point touchPoint){
    if(touchPoint.y <= p1.y && touchPoint.y >= p2.y && touchPoint.x >= p1.x && touchPoint.x <= p2.x){
        execute(this->buttonid);
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

ScreenButton ScreenContainer::createButton(Point p1, void (*execute)(int id), std::string text, int width, int height){
    ScreenButton btn(p1, width, height, execute, text, this->idCount);
    idCount++;
    buttons.push_back(btn);

    return btn;
}