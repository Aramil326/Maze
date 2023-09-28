//
// Created by maslynem on 22.04.23.
//

#ifndef MAZE_MODEL_MATRIX_MATRIX_H_
#define MAZE_MODEL_MATRIX_MATRIX_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#define EPS 1e-7

namespace s21 {

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  ~Matrix();

  [[nodiscard]] int GetRows() const;
  void setRows(int rows);
  [[nodiscard]] int GetCols() const;
  void setCols(int cols);

  bool EqMatrix(const Matrix& other);
  void clear();
  void Fill(int value);

  int& operator()(int row, int col) const;
  Matrix& operator=(const Matrix& other);
  bool operator==(const Matrix& other);

 private:
  int rows_, cols_;
  int** matrix_;
  static void FreeMatrix(Matrix& A);
  static void MoveMatrix(Matrix& dist, Matrix& source);
  static void CopyMatrixArr(Matrix& dist, const Matrix& source);
};

}  // namespace s21

#endif  // MAZE_MODEL_MATRIX_MATRIX_H_
