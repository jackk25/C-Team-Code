#include <vector>
#include <string>
#include "Point.h"
#include "../vex.h"

#ifndef SCREENBUTTON
#define SCREENBUTTON

class ScreenButton{
  Point p1;
  Point p2;
  std::string buttonText;
  int buttonId;
  vex::color outlineColor;
  vex::color fillColor;

  void (*execute)(int id);

  public:
    ScreenButton();
    
    void draw();
    void isWithin(Point touchPoint);

    //----- GETTERS / SETTERS ----//
    std::string getText();
    void setId(int id);
    void setPosition(Point position);
    void setDimensions(int width, int height);
    void setText(std::string input);
    void setOutlineColor(vex::color color);
    void setFillColor(vex::color color);
    void setCallback(void (*callback)(int id));
};

#endif