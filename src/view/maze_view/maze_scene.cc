#include "maze_scene.h"

#include "./ui_maze_scene.h"

namespace s21 {
s21::MazeScene::MazeScene(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MazeScene) {
  ui->setupUi(this);
  ui->pushButton->setEnabled(false);
}

s21::MazeScene::~MazeScene() { delete ui; }

void MazeScene::on_loadPushButton_clicked() {
  std::string path = QFileDialog::getOpenFileName().toStdString();
  if (!path.empty()) {
    int error = controller_.LoadMazeModelFromFile(path);
    if (!error) {
      SetNewModel();
      ui->pushButton->setEnabled(true);
    } else {
      ProcessLoadFromFileError(error);
    }
  }
}

void MazeScene::SetNewModel() {
  MazeModel model = controller_.GetMazeModel();
  ui->field->SetModel(model);
  ui->field->update();
}

void MazeScene::ShowErrorMessage(const std::string& title,
                                 const std::string& msg) {
  QMessageBox::critical(this, QString::fromStdString(title),
                        QString::fromStdString(msg));
}

void MazeScene::on_generatePushButton_clicked() {
  int height = ui->rowsSpinBox->value();
  int width = ui->columnsSpinBox->value();
  controller_.GenerateMaze(height, width);
  SetNewModel();

  const std::string path =
      QCoreApplication::applicationDirPath().toStdString() + "/Generations";
  QDir().mkdir(QString::fromStdString(path));
  controller_.SaveModelInFile(const_cast<std::string&>(path));

  ui->pushButton->setEnabled(true);
}

void MazeScene::on_pushButton_clicked() {
  int x1 = ui->xStartPointSpinBox->value() - 1;
  int y1 = ui->yStartPointSpinBox->value() - 1;
  int x2 = ui->xEndPointSpinBox->value() - 1;
  int y2 = ui->yEndPointSpinBox->value() - 1;
  int error = controller_.SolveMaze(x1, y1, x2, y2);
  if (error == 0) {
    SetNewModel();
  } else {
    ProcessSolveMazeError(error);
  }
}

void MazeScene::ShowMazeScene() { show(); }

void MazeScene::ProcessLoadFromFileError(int error) {
  switch (error) {
    case ErrorLoadType::kFileNotOpen:
      ShowErrorMessage("Open file error", "File can't be open.");
      break;
    case ErrorLoadType::kWrongHeight:
      ShowErrorMessage("Height error", "Maze must contains 1-50 rows.");
      break;
    case ErrorLoadType::kWrongWidth:
      ShowErrorMessage("Width error", "Maze must contains 1-50 columns.");
      break;
    case ErrorLoadType::kWrongContent:
      ShowErrorMessage("Content error", "Incorrect content format.");
      break;
    default:
      ShowErrorMessage("Unknown error", "Unknown error");
  }
}

void MazeScene::ProcessSolveMazeError(int error) {
  switch (error) {
    case ErrorSolveType::kStartPointOutOfRange:
      ShowErrorMessage("Start point error", "Start point is out of range.");
      break;
    case ErrorSolveType::kEndPointOutOfRange:
      ShowErrorMessage("End point error", "End point is out of range.");
      break;
    case ErrorSolveType::kNoPath:
      ShowErrorMessage("Path error", "Can't find path. Is the maze perfect?");
      break;
    case ErrorSolveType::kStartPointEqualsEndPoint:
      ShowErrorMessage("Start and end point error",
                       "Start point is equal end point.");
      break;
    default:
      ShowErrorMessage("Unknown error", "Unknown error");
  }
}

}  // namespace s21
