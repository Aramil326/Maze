//
// Created by gwynesse on 23.04.23.
//

#include "maze_solver.h"

int s21::MazeSolver::FindPath(s21::MazeModel &mazeModel, int x1, int y1, int x2,
                              int y2) {
  maze_model_ = &mazeModel;
  if (!PointInField(x1, y1)) return kStartPointOutOfRange;
  if (!PointInField(x2, y2)) return kEndPointOutOfRange;
  if ((x1 == x2) && (y1 == y2)) return kStartPointEqualsEndPoint;

  memory_matrix_.setCols(mazeModel.GetWidth());
  memory_matrix_.setRows(mazeModel.GetHeight());
  memory_matrix_.Fill(-2);
  memory_matrix_(y1, x1) = -1;

  s21::Matrix steps(4, 2);
  steps(0, 0) = 1;
  steps(1, 1) = 1;
  steps(2, 0) = -1;
  steps(3, 1) = -1;

  std::pair<int, int> start_point{x1, y1};
  std::list<std::pair<int, int>> cell_queue;
  cell_queue.push_back(start_point);
  std::pair<int, int> temp_point{};

  bool keep_going(true);
  while (not cell_queue.empty() && keep_going) {
    int x = cell_queue.front().first;
    int y = cell_queue.front().second;
    cell_queue.pop_front();
    for (int i = 0; i < 4 && keep_going; i++) {
      int new_x = x + steps(i, 0);
      int new_y = y + steps(i, 1);
      if (PointInField(new_x, new_y)) {
        if (NotMeetWall(i, x, y)) {
          if (PointNotUsed(new_x, new_y)) {
            temp_point.first = new_x;
            temp_point.second = new_y;
            cell_queue.push_back(temp_point);
            memory_matrix_(new_y, new_x) = 1000 * x + y;
            if ((temp_point.first == x2) && (temp_point.second == y2))
              keep_going = false;
          }
        }
      }
    }
  }
  if (keep_going) return kNoPath;
  FillPath(x1, y1, x2, y2);
  maze_model_->SetIsMazeSolved(true);
  return kSuccess;
}

bool s21::MazeSolver::PointInField(int x, int y) {
  return ((x >= 0) && (x < maze_model_->GetWidth()) && (y >= 0) &&
          (y < maze_model_->GetHeight()));
}

bool s21::MazeSolver::NotMeetWall(int i, int x, int y) {
  bool wall(true);
  if (i == 0)
    wall = !(maze_model_->IsThereRightWall(y, x));
  else if (i == 1)
    wall = !(maze_model_->IsThereBotWall(y, x));
  else if (i == 2)
    wall = !(maze_model_->IsThereLeftWall(y, x));
  else
    wall = !(maze_model_->IsThereTopWall(y, x));
  return wall;
}

bool s21::MazeSolver::PointNotUsed(int x, int y) {
  return (memory_matrix_(y, x) == -2);
}

void s21::MazeSolver::FillPath(int x1, int y1, int x2, int y2) {
  maze_model_->ClearShortWay();
  maze_model_->SetShortWayValue(y1, x1, 1);
  while (memory_matrix_(y2, x2) != -1) {
    maze_model_->SetShortWayValue(y2, x2, 1);
    int previous = memory_matrix_(y2, x2);
    x2 = previous / 1000;
    y2 = previous % 1000;
  }
}
