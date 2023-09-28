#include "maze_model.h"

s21::MazeModel::MazeModel(int h, int w) {
  this->height_ = h;
  this->width_ = w;
  ResizeModel(h, w);
}

s21::MazeModel::MazeModel() {
  this->height_ = -1;
  this->width_ = -1;
  this->is_maze_solved_ = false;
}

void s21::MazeModel::SetRightBoardValue(int y, int x, int value) {
  right_board_(y, x) = value;
}

void s21::MazeModel::SetBotBoardValue(int y, int x, int value) {
  bot_board_(y, x) = value;
}

void s21::MazeModel::ResizeModel(int h, int w) {
  height_ = h;
  width_ = w;
  right_board_.setRows(h);
  right_board_.setCols(w);
  right_board_.clear();
  bot_board_.setRows(h);
  bot_board_.setCols(w);
  bot_board_.clear();
  short_way_.setRows(h);
  short_way_.setCols(w);
  short_way_.clear();
  this->is_maze_solved_ = false;
}

int s21::MazeModel::GetHeight() const { return height_; }

int s21::MazeModel::GetWidth() const { return width_; }

bool s21::MazeModel::GetRightBoardValue(int y, int x) {
  return right_board_(y, x);
}

bool s21::MazeModel::GetBotBoardValue(int y, int x) { return bot_board_(y, x); }

bool s21::MazeModel::IsThereTopWall(int y, int x) {
  if (y == 0) {
    return true;
  }
  return bot_board_(y - 1, x);
}

bool s21::MazeModel::IsThereBotWall(int y, int x) { return bot_board_(y, x); }

bool s21::MazeModel::IsThereLeftWall(int y, int x) {
  if (x == 0) {
    return true;
  }
  return right_board_(y, x - 1);
}

bool s21::MazeModel::IsThereRightWall(int y, int x) {
  return right_board_(y, x);
}

void s21::MazeModel::SetShortWayValue(int y, int x, int value) {
  short_way_(y, x) = value;
}

bool s21::MazeModel::GetShortWayValue(int y, int x) { return short_way_(y, x); }

bool s21::MazeModel::IsMazeSolved() const { return is_maze_solved_; }

void s21::MazeModel::SetIsMazeSolved(bool isMazeSolved) {
  is_maze_solved_ = isMazeSolved;
}

void s21::MazeModel::ClearShortWay() { short_way_.clear(); }

int s21::MazeModel::SaveModelInFile(std::string &path) {
  std::ofstream out;

  time_t raw_time;
  struct tm *time_info;
  time(&raw_time);
  time_info = localtime(&raw_time);

  int height = GetHeight();
  int width = GetWidth();

  try {
    out.open(path + "/" + std::to_string(height) + "x" + std::to_string(width) +
             "_" + std::to_string(time_info->tm_hour) + "_" +
             std::to_string(time_info->tm_min) + "_" +
             std::to_string(time_info->tm_sec) + ".txt");

    out << std::to_string(height) << " " << std::to_string(width) << "\n";

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (j + 1 == width) {
          out << GetRightBoardValue(i, j);
        } else {
          out << GetRightBoardValue(i, j) << " ";
        }
      }
      out << "\n";
    }

    out << "\n";

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (j + 1 == width) {
          out << GetBotBoardValue(i, j);
        } else {
          out << GetBotBoardValue(i, j) << " ";
        }
      }
      out << "\n";
    }
  } catch (const std::ifstream::failure &e) {
    return 1;
  }

  out.close();
  return 0;
}
