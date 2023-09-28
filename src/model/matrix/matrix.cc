//
// Created by maslynem on 22.04.23.
//

#include "matrix.h"

namespace s21 {

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new int *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new int[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = false;
      }
    }
  } else
    throw std::out_of_range("Incorrect size of matrix");
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  CopyMatrixArr(*this, other);
}

Matrix::~Matrix() { FreeMatrix(*this); }

int Matrix::GetRows() const { return rows_; }

void Matrix::setRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Incorrect size of matrix");
  } else if (rows != rows_) {
    Matrix temp(rows, cols_);
    for (int i = 0; i < rows_; i++) {
      std::memcpy(temp.matrix_[i], matrix_[i], cols_ * sizeof(int));
      if (rows < rows_ && i + 1 == rows) break;
    }
    *this = temp;
  }
}

int Matrix::GetCols() const { return cols_; }

void Matrix::setCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Incorrect size of matrix");
  } else if (cols != cols_) {
    Matrix temp(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      if (cols < cols_)
        std::memcpy(temp.matrix_[i], matrix_[i], cols * sizeof(int));
      else
        std::memcpy(temp.matrix_[i], matrix_[i], cols_ * sizeof(int));
    }
    *this = temp;
  }
}

int &Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input_, index is out of range");
  }
  return matrix_[row][col];
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    FreeMatrix(*this);
    rows_ = other.rows_;
    cols_ = other.cols_;
    CopyMatrixArr(*this, other);
  }
  return *this;
}

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }

bool Matrix::EqMatrix(const Matrix &other) {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >= EPS) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}

void Matrix::FreeMatrix(Matrix &A) {
  for (int i = 0; i < A.rows_; i++) {
    delete[] A.matrix_[i];
  }
  delete[] A.matrix_;
}

void Matrix::MoveMatrix(Matrix &dist, Matrix &source) {
  dist.matrix_ = source.matrix_;
  dist.rows_ = source.rows_;
  dist.cols_ = source.cols_;
  source.matrix_ = nullptr;
  source.rows_ = 0;
  source.cols_ = 0;
}

void Matrix::CopyMatrixArr(Matrix &dist, const Matrix &source) {
  dist.matrix_ = new int *[dist.rows_];
  for (int i = 0; i < dist.rows_; i++) {
    dist.matrix_[i] = new int[dist.cols_];
    std::memcpy(dist.matrix_[i], source.matrix_[i], source.cols_ * sizeof(int));
  }
}

void Matrix::clear() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = false;
    }
  }
}

void Matrix::Fill(int value) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = value;
}

}  // namespace s21
