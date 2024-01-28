#include "screen/ScreenContainer.h"
#include "vex.h"

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