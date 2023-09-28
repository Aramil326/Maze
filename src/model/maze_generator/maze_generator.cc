//
// Created by azathotp on 23.04.23.
//

#include "maze_generator.h"

s21::MazeGenerator::MazeGenerator(s21::MazeModel *mazeModel)
    : maze_model_(mazeModel) {}

void s21::MazeGenerator::GenerateMaze(int height, int width) {
  maze_model_->ResizeModel(height, width);
  current_row_.clear();
  current_row_.resize(width);
  next_unique_set_num_ = 1;

  for (current_row_num_ = 0; current_row_num_ < height; current_row_num_++) {
    FillUniqueSets();
    AddRightBorders();
    AddBottomBorders();
    if (current_row_num_ != height - 1) {
      PrepareNewLine();
    }
  }
  SetLastRow();
}

void s21::MazeGenerator::FillUniqueSets() {
  for (int i = 0; i < maze_model_->GetWidth(); i++) {
    if (current_row_[i] == 0) {
      current_row_[i] = next_unique_set_num_++;
    }
  }
}

void s21::MazeGenerator::AddRightBorders() {
  for (int j = 0; j < maze_model_->GetWidth() - 1; j++) {
    if (AddBorder() || current_row_[j] == current_row_[j + 1]) {
      maze_model_->SetRightBoardValue(current_row_num_, j, true);
    } else {
      MergeSet(current_row_[j], current_row_[j + 1]);
    }
  }
  maze_model_->SetRightBoardValue(current_row_num_, maze_model_->GetWidth() - 1,
                                  true);
}

bool s21::MazeGenerator::AddBorder() {
  std::uniform_int_distribution<int> dist(0, 1);
  return dist(rd_);
}

void s21::MazeGenerator::MergeSet(int set, int set_to_merge) {
  for (int i = 0; i < maze_model_->GetWidth(); i++) {
    if (current_row_[i] == set_to_merge) {
      current_row_[i] = set;
    }
  }
}

void s21::MazeGenerator::AddBottomBorders() {
  for (int j = 0; j < maze_model_->GetWidth(); j++) {
    int quantity_elements = GetQuantityElementsOfSet(current_row_[j]);
    int quantity_elements_without_bot_bd =
        GetQuantityElementsOfSetWithoutBotBd(current_row_[j]);
    if (AddBorder() && quantity_elements != 1 &&
        quantity_elements_without_bot_bd != 1) {
      maze_model_->SetBotBoardValue(current_row_num_, j, true);
    }
  }
}

int s21::MazeGenerator::GetQuantityElementsOfSet(int set) {
  int element_count = 0;
  for (int i = 0; i < maze_model_->GetWidth(); i++) {
    if (current_row_[i] == set) {
      element_count++;
    }
  }
  return element_count;
}

int s21::MazeGenerator::GetQuantityElementsOfSetWithoutBotBd(int set) {
  int element_count = 0;
  for (int j = 0; j < maze_model_->GetWidth(); j++) {
    if (current_row_[j] == set &&
        !maze_model_->IsThereBotWall(current_row_num_, j)) {
      element_count++;
    }
  }
  return element_count;
}

void s21::MazeGenerator::PrepareNewLine() {
  for (int i = 0; i < maze_model_->GetWidth(); i++) {
    if (maze_model_->IsThereBotWall(current_row_num_, i)) {
      current_row_[i] = 0;
    }
  }
}

void s21::MazeGenerator::SetLastRow() {
  current_row_num_ = maze_model_->GetHeight() - 1;
  for (int i = 0; i < maze_model_->GetWidth() - 1; i++) {
    if (current_row_[i] != current_row_[i + 1]) {
      maze_model_->SetRightBoardValue(current_row_num_, i, false);
      MergeSet(current_row_[i], current_row_[i + 1]);
    }
    maze_model_->SetBotBoardValue(current_row_num_, i, true);
  }
  maze_model_->SetRightBoardValue(current_row_num_, maze_model_->GetWidth() - 1,
                                  true);
  maze_model_->SetBotBoardValue(current_row_num_, maze_model_->GetWidth() - 1,
                                true);
}