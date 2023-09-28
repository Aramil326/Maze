//
// Created by Maslyn Emperor on 4/26/23.
//

#ifndef MAZE_ERROR_SOLVE_TYPE_H
#define MAZE_ERROR_SOLVE_TYPE_H
namespace s21 {
enum ErrorSolveType {
  kSuccess = 0,
  kStartPointOutOfRange,
  kEndPointOutOfRange,
  kNoPath,
  kStartPointEqualsEndPoint,
};
}
#endif  // MAZE_ERROR_SOLVE_TYPE_H
