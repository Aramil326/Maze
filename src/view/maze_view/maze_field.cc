#include "maze_field.h"

s21::MazeField::MazeField(QWidget *parent) : QWidget(parent) {}

void s21::MazeField::SetModel(s21::MazeModel &model) { model_ = model; }

void s21::MazeField::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  painter_.begin(this);
  painter_.setPen(QPen(Qt::black, 2));

  if (model_.GetWidth() != -1) {
    DrawPerimeter();
    DrawModel();
    DrawRightWay();
  }

  painter_.end();
}

void s21::MazeField::DrawPerimeter() {
  painter_.drawLine(QLine(0, 1, 500, 1));  // top_line
  painter_.drawLine(QLine(1, 0, 1, 500));  // left_line
}

void s21::MazeField::DrawModel() {
  int height = model_.GetHeight();
  int width = model_.GetWidth();
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int j_step = 500 * j / width;
      int j_step_p1 = 500 * (j + 1) / width;
      int i_step = 500 * i / height;
      int i_step_p1 = 500 * (i + 1) / height;
      if (model_.IsThereRightWall(i, j)) {
        if (j + 1 != width && i + 1 != height) {
          painter_.drawLine(
              QLine(j_step_p1 - 1, i_step, j_step_p1 - 1, i_step_p1 - 1));
        } else if (j + 1 != width) {
          painter_.drawLine(QLine(j_step_p1 - 1, i_step, j_step_p1 - 1, 499));
        } else {
          painter_.drawLine(QLine(499, i_step, 499, 499));
        }
      }
      if (model_.IsThereBotWall(i, j) == 1) {
        if (i + 1 != height && j + 1 != width) {
          painter_.drawLine(
              QLine(j_step, i_step_p1 - 1, j_step_p1 - 1, i_step_p1 - 1));
        } else if (i + 1 != height) {
          painter_.drawLine(QLine(j_step, i_step_p1 - 1, 499, i_step_p1 - 1));
        } else {
          painter_.drawLine(QLine(j_step, 499, 499, 499));
        }
      }
    }
  }
}

void s21::MazeField::DrawRightWay() {
  if (model_.IsMazeSolved()) {
    painter_.setPen(QPen(Qt::red, 2));
    int height = model_.GetHeight();
    int width = model_.GetWidth();
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        if (model_.GetShortWayValue(i, j) == 1) {
          int j_step = 500 * (2 * j + 1) / (2 * width);
          int j_step_p1 = 500 * (2 * j + 3) / (2 * width);
          int i_step = 500 * (2 * i + 1) / (2 * height);
          int i_step_p1 = 500 * (2 * i + 3) / (2 * height);
          if (j + 1 < width && model_.GetShortWayValue(i, j + 1) == 1 &&
              !model_.IsThereRightWall(i, j)) {
            painter_.drawLine(QLine(j_step, i_step, j_step_p1, i_step));
          }
          if (i + 1 < height && model_.GetShortWayValue(i + 1, j) == 1 &&
              !model_.IsThereBotWall(i, j)) {
            painter_.drawLine(QLine(j_step, i_step, j_step, i_step_p1));
          }
        }
      }
    }
  }
}
