//
// Created by maslynem on 22.04.23.
//
#ifndef MAZE_ERROR_LOAD_TYPE_H
#define MAZE_ERROR_LOAD_TYPE_H
namespace s21 {
enum ErrorLoadType {
  kOk = 0,
  kFileNotOpen,
  kWrongHeight,
  kWrongWidth,
  kWrongContent,
};
}
#endif  // MAZE_ERROR_LOAD_TYPE_H
