//
// Created by maslynem on 22.04.23.
//

#include "model_loader.h"
using namespace s21;

ModelLoader &ModelLoader::Instance() {
  static ModelLoader model_loader;
  return model_loader;
}

int ModelLoader::LoadMazeModel(MazeModel *maze_model, std::string &path) {
  std::ifstream in(path);
  if (!in.is_open()) {
    return ErrorLoadType::kFileNotOpen;
  }
  int height = -1;
  int width = -1;
  in >> height;
  if (height < 1 || height > 50) {
    return ErrorLoadType::kWrongHeight;
  }
  in >> width;
  if (width < 1 || width > 50) {
    return ErrorLoadType::kWrongWidth;
  }
  maze_model->ResizeModel(height, width);
  int temp = -1;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      in >> temp;
      if (temp == 0) {
        maze_model->SetRightBoardValue(i, j, false);
      } else if (temp == 1) {
        maze_model->SetRightBoardValue(i, j, true);
      } else {
        return ErrorLoadType::kWrongContent;
      }
    }
  }
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      in >> temp;
      if (temp == 0) {
        maze_model->SetBotBoardValue(i, j, 0);
      } else if (temp == 1) {
        maze_model->SetBotBoardValue(i, j, 1);
      } else {
        return ErrorLoadType::kWrongContent;
      }
    }
  }
  return ErrorLoadType::kOk;
}
