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

extern const size_t kMaxThreadNumber;
extern const size_t kSizeTRandMin, kSizeTRandMax;
extern const int kIntRandMin, kIntRandMax;

class Vector : public std::vector<int> {
 public:
  Vector(size_t elem_num) : std::vector<int>(elem_num, 0) {}
};

class Matrix : public std::vector<Vector> {
 public:
  Matrix(size_t row_length, size_t col_length, bool randomize = false, bool zero = false) :
      std::vector<Vector>(row_length, Vector(col_length)), row_length_(row_length), col_length_(col_length) {
    if (randomize) this->Randomize();
  }
  int elem(size_t number);
  void Randomize();
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
Matrix MatrixParallelProduct(const Matrix &matrix_1, const Matrix &matrix_2);
void MatrixParallelProductThread(const Matrix &matrix_1, const Matrix &matrix_2, Matrix &result,
                                 size_t start_elem, const size_t &col_length, const size_t &calc_length, const size_t &full_size);

#endif //LEARNING_STD_THREAD__MATRIX_H_
