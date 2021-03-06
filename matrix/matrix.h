//
// Created by glebd on 18.10.2021.
//

#ifndef LEARNING_STD_THREAD__MATRIX_H_
#define LEARNING_STD_THREAD__MATRIX_H_

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

class Vector : public std::vector<int> {
 public:
  Vector(size_t elem_num) : std::vector<int>(elem_num) {}
};

class Matrix : public std::vector<Vector> {
 public:
  Matrix(size_t row_length, size_t col_length, bool randomize = false, int rand_min = 0, int rand_max = RAND_MAX) :
      std::vector<Vector>(row_length, Vector(col_length)), row_length_(row_length), col_length_(col_length) {
    if (randomize) this->Randomize(rand_min, rand_max);
  }
  decltype(auto) elem(size_t number);
  decltype(auto) elem(size_t number) const;
  void Randomize(int rand_min, int rand_max);
  decltype(auto) GetRowNumber();
  decltype(auto) GetRowNumber() const;
  decltype(auto) GetColNumber();
  decltype(auto) GetColNumber() const;
 protected:
  size_t row_length_;
  size_t col_length_;
};

std::ostream &operator<<(std::ostream &os, const Vector &vector);
std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

Matrix MatrixSequenceProduct(const Matrix &matrix_1, const Matrix &matrix_2);
Matrix MatrixParallelProduct(const Matrix &matrix_1, const Matrix &matrix_2, const size_t &max_thread_num);
void MatrixParallelProductThread(const Matrix &matrix_1, const Matrix &matrix_2, Matrix &result,
                                 size_t start_elem, size_t end_elem);

#endif //LEARNING_STD_THREAD__MATRIX_H_
