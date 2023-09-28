#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <ctime>
#include <fstream>
#include <vector>

#include "../matrix/matrix.h"

namespace s21 {
class MazeModel {
 public:
  MazeModel();
  MazeModel(int h, int w);

  void SetRightBoardValue(int y, int x, int value);
  void SetBotBoardValue(int y, int x, int value);
  void SetShortWayValue(int y, int x, int value);
  bool GetRightBoardValue(int y, int x);

  bool GetBotBoardValue(int y, int x);
  bool GetShortWayValue(int y, int x);

  [[nodiscard]] int GetHeight() const;
  [[nodiscard]] int GetWidth() const;

  void ResizeModel(int h, int w);

  bool IsThereTopWall(int y, int x);
  bool IsThereBotWall(int y, int x);
  bool IsThereLeftWall(int y, int x);
  bool IsThereRightWall(int y, int x);

  [[nodiscard]] bool IsMazeSolved() const;
  void SetIsMazeSolved(bool isMazeSolved);

  void ClearShortWay();

  int SaveModelInFile(std::string &path);

 private:
  int height_;
  int width_;
  bool is_maze_solved_;
  Matrix right_board_;
  Matrix bot_board_;
  Matrix short_way_;
};
}  // namespace s21
#endif  // MAZEMODEL_H
