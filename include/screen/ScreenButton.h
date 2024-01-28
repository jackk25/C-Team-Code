#include <vector>
#include <string>

class ScreenContainer;
class ScreenButton;

struct Point{
  int x, y;
};

typedef struct Point Point;

class ScreenButton{
  Point p1;
  Point p2;
  std::string buttonText;
  int buttonid;
  vex::color outlineColor;
  vex::color fillColor;

  void (*execute)(int id);


  public:
    ScreenButton(int id, Point topLeftPosition, void (*inputFunc)(int id), std::string text = "", int width = 60, int height = 60);
    
    void draw();
    void isWithin(Point touchPoint);

    //----- GETTERS / SETTERS ----//
    std::string getText();
    void setPosition(Point position);
    void setText(std::string input);
    void setOutlineColor(vex::color color);
    void setFillColor(vex::color color);
    void setCallback(void (*callback)(int id));
};