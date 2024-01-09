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

  void (*execute)();

  void draw();

  public:
    ScreenButton(Point topLeftPosition, int width, int height, void (*inputFunc)(), std::string text);
    
    void isWithin(Point touchPoint);

    //----- GETTERS / SETTERS ----//
    std::string getText();
    void setText(std::string input);
};

class ScreenContainer{
  std::vector<ScreenButton> buttons;

  public:
    void runThroughButtons();

    ScreenButton createButton(Point p1, void (*execute)(), std::string text = "", int width = 60, int height = 60);
};