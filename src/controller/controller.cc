//
// Created by maslynem on 22.04.23.
//

#include "controller.h"

int s21::Controller::LoadMazeModelFromFile(std::string &path) {
  return facade_.LoadMazeModelFromFile(path);
}

void s21::Controller::GenerateMaze(int height, int width) {
  facade_.GenerateMaze(height, width);
}

const s21::MazeModel &s21::Controller::GetMazeModel() const {
  return facade_.GetMazeModel();
}

int s21::Controller::SolveMaze(int x1, int y1, int x2, int y2) {
  return facade_.SolveMaze(x1, y1, x2, y2);
}

void s21::Controller::SaveModelInFile(std::string &path) {
  facade_.SaveModelInFile(path);
}
