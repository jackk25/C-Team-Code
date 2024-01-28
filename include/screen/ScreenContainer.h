#include "ScreenButton.h"

class ScreenContainer{
  std::vector<ScreenButton> buttons;
  int idCount;

  public:
    void draw();
    void runThroughButtons();

    ScreenButton createButton(Point p1, void (*execute)(int id), std::string text = "", int width = 60, int height = 60);
};