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

  void (*execute)(int id);

  void draw();

  public:
    ScreenButton(Point topLeftPosition, int width, int height, void (*inputFunc)(int id), std::string text, int id);
    
    void isWithin(Point touchPoint);

    //----- GETTERS / SETTERS ----//
    std::string getText();
    void setText(std::string input);
};