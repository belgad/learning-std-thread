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

void Matrix::Randomize(int rand_min, int rand_max) {
  std::mt19937 random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution uniform_int_distribution(rand_min, rand_max);

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

Matrix MatrixParallelProduct(const Matrix &matrix_1, const Matrix &matrix_2, const size_t &max_thread_num) {
  size_t row_length = matrix_1.GetRowNumber(), col_length = matrix_2.GetColNumber(), calc_length = matrix_1.GetColNumber(), full_size = row_length * col_length;
  size_t thread_num = std::min(full_size, max_thread_num);
  Matrix result(row_length, col_length);
  std::vector<std::thread *> threads(thread_num);
  std::vector<size_t> borders(thread_num + 1);
  size_t jump = full_size / thread_num;
  borders[0] = 0;
  for (size_t i = 1; i < thread_num; ++i) {
    borders[i] = borders[i - 1] + jump;
  }
  borders[thread_num] = full_size;
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i] = new std::thread(&MatrixParallelProductThread,
                                 std::cref(matrix_1),
                                 std::cref(matrix_2),
                                 std::ref(result),
                                 borders[i],
                                 borders[i + 1]);
  }
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i]->join();
  }
  return result;
}

void MatrixParallelProductThread(const Matrix &matrix_1, const Matrix &matrix_2, Matrix &result,
                                 size_t start_elem, size_t end_elem) {
  size_t i, calc_length = matrix_1.GetColNumber(), col_length = matrix_2.GetColNumber(),
  row = start_elem / col_length, col = start_elem % col_length;
  for (; start_elem < end_elem; ++start_elem) {
    result[row][col] = 0;
    for (i = 0; i < calc_length; ++i) {
      result[row][col] += matrix_1[row][i] * matrix_2[i][col];
    }
    if (++col == col_length) {
      ++row; col = 0;
    }
  }
}
