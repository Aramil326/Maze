//
// Created by azathotp on 23.04.23.
//

#ifndef MAZE_SRC_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_
#define MAZE_SRC_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_

#include "../maze_model/maze_model.h"
#include "../model_loader/error_load_type.h"

namespace s21 {
class MazeGenerator {
 public:
  explicit MazeGenerator(MazeModel *mazeModel);
  void GenerateMaze(int height, int width);

 private:
  MazeModel *maze_model_;
  std::vector<int> current_row_;
  std::random_device rd_;
  int current_row_num_;
  int next_unique_set_num_;

  void FillUniqueSets();

  bool AddBorder();

  void AddRightBorders();

  void MergeSet(int set, int set_to_merge);

  void AddBottomBorders();

  int GetQuantityElementsOfSet(int set);

  int GetQuantityElementsOfSetWithoutBotBd(int set);

  void PrepareNewLine();

  void SetLastRow();
};
}  // namespace s21
#endif  // MAZE_SRC_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_
