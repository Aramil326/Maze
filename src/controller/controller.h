//
// Created by maslynem on 22.04.23.
//

#ifndef MAZE_CONTROLLER_CONTROLLER_H_
#define MAZE_CONTROLLER_CONTROLLER_H_

#include "../model/facade/facade.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  int LoadMazeModelFromFile(std::string& path);
  void GenerateMaze(int height, int width);
  int SolveMaze(int x1, int y1, int x2, int y2);
  [[nodiscard]] const MazeModel& GetMazeModel() const;

  void SaveModelInFile(std::string& path);

 private:
  Facade facade_;
};
}  // namespace s21
#endif  // MAZE_CONTROLLER_CONTROLLER_H_
