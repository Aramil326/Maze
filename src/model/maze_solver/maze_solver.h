//
// Created by gwynesse on 23.04.23.
//

#ifndef MAZE_SRC_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_
#define MAZE_SRC_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_

#include <list>

#include "../maze_model/maze_model.h"
#include "error_solve_type.h"

namespace s21 {

class MazeSolver {
 public:
  static int FindPath(MazeModel &mazeModel, int x1, int y1, int x2, int y2);

 private:
  MazeSolver() = default;

  static inline MazeModel *maze_model_;

  static inline Matrix memory_matrix_;

  [[nodiscard]] static bool PointInField(int x, int y);

  static bool NotMeetWall(int i, int x, int y);

  static bool PointNotUsed(int x, int y);

  static void FillPath(int x1, int y1, int x2, int y2);
};

}  // namespace s21

#endif  // MAZE_SRC_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_
