#include <QApplication>

#include "view/maze_view/maze_scene.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MazeScene w;
  w.show();
  return a.exec();
}
