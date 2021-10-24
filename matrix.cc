//
// Created by glebd on 18.10.2021.
//

#include "matrix.h"

decltype(auto) Matrix::elem(size_t number) {
  return (this->data()[number / row_length_][number % col_length_]);
}

decltype(auto) Matrix::elem(size_t number) const {
  return (this->data()[number / row_length_][number % col_length_]);
}

void Matrix::Randomize() {
  std::mt19937 random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution uniform_int_distribution(kIntRandMin, kIntRandMax);

  for (size_t i = 0; i < this->row_length_; ++i) {
    for (size_t j = 0; j < this->col_length_; ++j) {
      this->data()[i][j] = uniform_int_distribution(random_engine);
    }
  }
}

decltype(auto) Matrix::GetRowNumber() {
  return (this->row_length_);
}

decltype(auto) Matrix::GetRowNumber() const {
  return (this->row_length_);
}

decltype(auto) Matrix::GetColNumber() {
  return (this->col_length_);
}

decltype(auto) Matrix::GetColNumber() const {
  return (this->col_length_);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
  for (const auto &i : vector) {
    os << i << '\t';
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  for (const auto &i : matrix) {
    os << i << std::endl;
  }
  return os;
}

Matrix MatrixSequenceProduct(const Matrix &matrix_1, const Matrix &matrix_2) {
  size_t row_length = matrix_1.GetRowNumber(), col_num = matrix_2.GetColNumber(), calc_len = matrix_1.GetColNumber();
  Matrix result(row_length, col_num);
  for (size_t i = 0; i < row_length; ++i) {
    for (size_t j = 0; j < col_num; ++j) {
      for (size_t k = 0; k < calc_len; ++k) {
        result[i][j] += matrix_1[i][k] * matrix_2[k][j];
      }
    }
  }
  return result;
}

Matrix MatrixParallelProduct(const Matrix &matrix_1, const Matrix &matrix_2) {
  size_t row_length = matrix_1.GetRowNumber(), col_length = matrix_2.GetColNumber(), calc_length = matrix_1.GetColNumber(), full_size = row_length * col_length;
  size_t thread_num = std::min(full_size, kMaxThreadNumber);
  Matrix result(row_length, col_length);
  std::vector<std::thread *> threads(thread_num);
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i] = new std::thread(&MatrixParallelProductThread,
                                 std::cref(matrix_1),
                                 std::cref(matrix_2),
                                 std::ref(result),
                                 i,
                                 std::cref(col_length),
                                 std::cref(calc_length),
                                 std::cref(full_size));
  }
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i]->join();
  }
  return result;
}

void MatrixParallelProductThread(const Matrix &matrix_1, const Matrix &matrix_2, Matrix &result,
                                 size_t start_elem, const size_t &col_length, const size_t &calc_length, const size_t &full_size) {
  size_t i, row_now = start_elem / col_length, col_now = start_elem % col_length;
  while (start_elem < full_size) {
    for (i = 0; i < calc_length; ++i) {
      result[row_now][col_now] += matrix_1[row_now][i] * matrix_2[i][col_now];
    }
    start_elem += kMaxThreadNumber;
//    row_now += (kMaxThreadNumber + col_now) / col_length;
//    col_now = (kMaxThreadNumber + col_now) % col_length;
  row_now = start_elem / col_length;
  col_now = start_elem % col_length;
  }
}
