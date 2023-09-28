//
// Created by maslynem on 22.04.23.
//

#ifndef MAZE_MODEL_FACADE_H_
#define MAZE_MODEL_FACADE_H_

#include "../maze_generator/maze_generator.h"
#include "../maze_model/maze_model.h"
#include "../maze_solver/maze_solver.h"
#include "../model_loader/model_loader.h"

namespace s21 {
class Facade {
 public:
  Facade();
  ~Facade();

  int LoadMazeModelFromFile(std::string& path);

  void GenerateMaze(int height, int width);
  int SolveMaze(int x1, int y1, int x2, int y2);
  [[nodiscard]] const MazeModel& GetMazeModel() const;
  void SaveModelInFile(std::string& path);

 private:
  MazeModel maze_model_;
  ModelLoader* model_loader_;
  MazeGenerator* maze_generator_;
};
}  // namespace s21
#endif  // MAZE_MODEL_FACADE_H_
