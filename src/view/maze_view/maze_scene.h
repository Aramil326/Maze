#ifndef SCENE_H
#define SCENE_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>

#include "controller/controller.h"
#include "maze_field.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeScene;
}
QT_END_NAMESPACE

namespace s21 {

class MazeScene : public QMainWindow {
  Q_OBJECT

 public:
  explicit MazeScene(QWidget *parent = nullptr);
  ~MazeScene() override;

 private slots:
  void on_loadPushButton_clicked();

  void on_generatePushButton_clicked();

  void on_pushButton_clicked();

  void ShowMazeScene();

 private:
  Ui::MazeScene *ui;
  Controller controller_;

  void ShowErrorMessage(const std::string &title, const std::string &msg);

  void ProcessLoadFromFileError(int error);

  void ProcessSolveMazeError(int error);

  void SetNewModel();
};
}  // namespace s21
#endif  // SCENE_H
