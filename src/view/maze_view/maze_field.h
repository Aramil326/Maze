#ifndef FIELD_H
#define FIELD_H

#include <QPainter>
#include <QStyleOption>
#include <QWidget>

#include "model/maze_model/maze_model.h"

namespace s21 {

class MazeField : public QWidget {
  Q_OBJECT
 public:
  explicit MazeField(QWidget *parent = nullptr);
  ~MazeField() override = default;
  void SetModel(MazeModel &model);

 private:
  QPainter painter_;
  MazeModel model_;
  void paintEvent(QPaintEvent *) override;
  void DrawPerimeter();
  void DrawModel();
  void DrawRightWay();
};
}  // namespace s21
#endif  // FIELD_H
