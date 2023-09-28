//
// Created by maslynem on 22.04.23.
//

#include "facade.h"
s21::Facade::Facade() {
  model_loader_ = &ModelLoader::Instance();
  maze_generator_ = new MazeGenerator(&maze_model_);
}

s21::Facade::~Facade() { delete maze_generator_; }

int s21::Facade::LoadMazeModelFromFile(std::string &path) {
  return model_loader_->LoadMazeModel(&maze_model_, path);
}

void s21::Facade::GenerateMaze(int height, int width) {
  maze_generator_->GenerateMaze(height, width);
}

const s21::MazeModel &s21::Facade::GetMazeModel() const { return maze_model_; }

int s21::Facade::SolveMaze(int x1, int y1, int x2, int y2) {
  return MazeSolver::FindPath(maze_model_, x1, y1, x2, y2);
}

void s21::Facade::SaveModelInFile(std::string &path) {
  maze_model_.SaveModelInFile(path);
}
