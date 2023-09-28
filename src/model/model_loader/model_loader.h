//
// Created by maslynem on 22.04.23.
//

#ifndef MAZE_MODEL_MODEL_LOADER_MODELLOADER_H_
#define MAZE_MODEL_MODEL_LOADER_MODELLOADER_H_

#include <fstream>
#include <string>

#include "../maze_model/maze_model.h"
#include "error_load_type.h"

namespace s21 {
class ModelLoader {
 public:
  static ModelLoader &Instance();
  ModelLoader(const ModelLoader &root) = delete;
  ModelLoader &operator=(const ModelLoader &) = delete;

  int LoadMazeModel(MazeModel *maze_model, std::string &path);

 private:
  ModelLoader() = default;
};
}  // namespace s21
#endif  // MAZE_MODEL_MODEL_LOADER_MODELLOADER_H_
