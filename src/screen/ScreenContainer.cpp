#include "screen/ScreenContainer.h"
#include "vex.h"

void ScreenContainer::draw(){
    Brain.Screen.clearScreen();
    for(ScreenButton btn : buttons){
        btn.draw();
    }
}

void ScreenContainer::runThroughButtons(){
    Point touchPoint = {Brain.Screen.xPosition(), Brain.Screen.yPosition()};
    for(ScreenButton btn : buttons){
        btn.isWithin(touchPoint);
    }
}

void ScreenContainer::addButton(ScreenButton btn){
    buttons.push_back(btn);
}

ScreenButton ScreenContainer::createButton(Point p1, void (*execute)(int id), std::string text, int width, int height){
    ScreenButton btn;
    idCount++;

    return btn;
}