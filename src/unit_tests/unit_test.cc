//
// Created by maslynem on 23.04.23.
//

#include <gtest/gtest.h>

#include "../controller/controller.h"

using namespace s21;

class TestModel4x4 {
 public:
  TestModel4x4() {
    maze_model_.ResizeModel(4, 4);
    maze_model_.SetRightBoardValue(0, 3, 1);
    maze_model_.SetRightBoardValue(1, 0, 1);
    maze_model_.SetRightBoardValue(1, 2, 1);
    maze_model_.SetRightBoardValue(1, 3, 1);
    maze_model_.SetRightBoardValue(2, 1, 1);
    maze_model_.SetRightBoardValue(2, 3, 1);
    maze_model_.SetRightBoardValue(3, 3, 1);
    maze_model_.SetBotBoardValue(0, 0, 1);
    maze_model_.SetBotBoardValue(0, 2, 1);
    maze_model_.SetBotBoardValue(1, 2, 1);
    maze_model_.SetBotBoardValue(2, 0, 1);
    maze_model_.SetBotBoardValue(2, 1, 1);
    maze_model_.SetBotBoardValue(2, 3, 1);
    maze_model_.SetBotBoardValue(3, 0, 1);
    maze_model_.SetBotBoardValue(3, 1, 1);
    maze_model_.SetBotBoardValue(3, 2, 1);
    maze_model_.SetBotBoardValue(3, 3, 1);
  }
  [[nodiscard]] const MazeModel& GetMazeModel() const { return maze_model_; }

 private:
  MazeModel maze_model_;
} test_model;

TEST(test_load_maze_from_file, test_load_maze_from_file) {
  Controller controller;
  std::string path = "examples/mazes/4x4.txt";
  controller.LoadMazeModelFromFile(path);
  MazeModel model = controller.GetMazeModel();
  MazeModel test_maze_model = test_model.GetMazeModel();
  for (int i = 0; i < model.GetHeight(); ++i) {
    for (int j = 0; j < model.GetWidth(); ++j) {
      ASSERT_EQ(test_maze_model.GetRightBoardValue(i, j),
                model.GetRightBoardValue(i, j));
      ASSERT_EQ(test_maze_model.GetBotBoardValue(i, j),
                model.GetBotBoardValue(i, j));
    }
  }
}

TEST(test_generate_maze_borders, test_generate_maze) {
  Controller controller;
  int height = 10;
  int width = 10;
  controller.GenerateMaze(height, width);
  MazeModel mazeModel = controller.GetMazeModel();

  bool is_in_maze_model_any_bot_bd = false;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (mazeModel.GetBotBoardValue(i, j)) {
        is_in_maze_model_any_bot_bd = true;
      }
    }
  }

  bool is_in_maze_model_any_right_bd = false;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (mazeModel.GetBotBoardValue(i, j)) {
        is_in_maze_model_any_right_bd = true;
      }
    }
  }

  ASSERT_TRUE(is_in_maze_model_any_bot_bd);
  ASSERT_TRUE(is_in_maze_model_any_right_bd);
  std::string path = "unit_tests/";
  int error = mazeModel.SaveModelInFile(path);
  ASSERT_EQ(error, 0);
}

TEST(test_find_short_way, test_find_short_way_1) {
  Matrix test_right_way(4, 4);
  test_right_way(0, 0) = 1;
  test_right_way(0, 1) = 1;
  Controller controller;
  std::string path = "examples/mazes/4x4.txt";
  controller.LoadMazeModelFromFile(path);
  controller.SolveMaze(0, 0, 1, 0);
  MazeModel mazeModel = controller.GetMazeModel();

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_EQ(test_right_way(i, j), mazeModel.GetShortWayValue(i, j));
    }
  }
}

TEST(test_find_short_way, test_find_short_way_2) {
  Matrix test_right_way(4, 4);
  test_right_way(0, 0) = 1;
  test_right_way(0, 1) = 1;
  test_right_way(1, 1) = 1;
  test_right_way(1, 2) = 1;
  Controller controller;
  std::string path = "examples/mazes/4x4.txt";
  controller.LoadMazeModelFromFile(path);
  controller.SolveMaze(0, 0, 2, 1);
  MazeModel mazeModel = controller.GetMazeModel();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_EQ(test_right_way(i, j), mazeModel.GetShortWayValue(i, j));
    }
  }
  ASSERT_TRUE(mazeModel.IsMazeSolved());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
