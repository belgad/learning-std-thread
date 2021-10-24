#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>

#include "pi.h"
#include "matrix.h"

#define PI_CALCULATION
#define MATRIX_CALCULATION

const size_t kMaxThreadNumber = 16;
const size_t kSizeTRandMin = 1000, kSizeTRandMax = 3000;
const int kIntRandMin = 1, kIntRandMax = 100000;

int main() {
  std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1);
#ifdef PI_CALCULATION
  std::cout << "PI CALCULATION" << std::endl;
  auto pi_sequence_start_time = std::chrono::high_resolution_clock::now();
  // START PI SEQUENCE CALCULATION
  auto pi_sequence_result = PiSequenceCalculation();
  // END   PI SEQUENCE CALCULATION
  auto pi_sequence_end_time = std::chrono::high_resolution_clock::now();
  auto pi_sequence_elapsed_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(pi_sequence_end_time - pi_sequence_start_time).count();
  std::cout << "SEQUENCE:" << std::endl
            << "TIME:\t" << pi_sequence_elapsed_time << " ns" << std::endl
            << "RESULT:\t" << pi_sequence_result << std::endl;
  auto pi_parallel_start_time = std::chrono::high_resolution_clock::now();
  // START PI PARALLEL CALCULATION
  auto pi_parallel_result = PiParallelCalculation();
  // END   PI PARALLEL CALCULATION
  auto pi_parallel_end_time = std::chrono::high_resolution_clock::now();
  auto pi_parallel_elapsed_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(pi_parallel_end_time - pi_parallel_start_time).count();
  std::cout << "PARALLEL RESULTS:" << std::endl
            << "TIME:\t" << pi_parallel_elapsed_time << " ns" << std::endl
            << "RESULT:\t" << pi_parallel_result << std::endl;
  std::cout << "EFF:\t"
            << static_cast<long double>(pi_sequence_elapsed_time) / static_cast<long double>(pi_parallel_elapsed_time)
            << std::endl;
#endif
#ifdef MATRIX_CALCULATION
  std::mt19937 random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<size_t> uniform_size_t_distribution(kSizeTRandMin, kSizeTRandMax);
  std::uniform_int_distribution uniform_int_distribution(kIntRandMin, kIntRandMax);
  size_t size_1 = uniform_size_t_distribution(random_engine),
         size_2 = uniform_size_t_distribution(random_engine),
         size_3 = uniform_size_t_distribution(random_engine);
  bool print_matrix = size_1 < 15 && size_2 < 15 && size_3 < 15 && size_1 * size_3 < 100;
  Matrix matrix_1(size_1, size_2, true), matrix_2(size_2, size_3, true);
  std::cout << "MATRIX CALCULATION" << std::endl;
  std::cout << "SIZE 1:\t" << size_1 << "\tSIZE 2:\t" << size_2 << "\tSIZE 3:\t" << size_3 << std::endl;
  if (print_matrix) std::cout << "MATRIX 1:" << std::endl << matrix_1 << "MATRIX_2:" << std::endl << matrix_2;
  auto matrix_sequence_start_time = std::chrono::high_resolution_clock::now();
  // START MATRIX SEQUENCE CALCULATION
  auto matrix_product_sequence_result = MatrixSequenceProduct(matrix_1, matrix_2);
  // END   MATRIX SEQUENCE CALCULATION
  auto matrix_sequence_end_time = std::chrono::high_resolution_clock::now();
  auto matrix_sequence_elapsed_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(matrix_sequence_end_time - matrix_sequence_start_time).count();
  std::cout << "SEQUENCE:" << std::endl
            << "TIME:\t" << matrix_sequence_elapsed_time << " ns" << std::endl;
  if (print_matrix) std::cout << "RESULT:" << std::endl << matrix_product_sequence_result;
  auto matrix_parallel_start_time = std::chrono::high_resolution_clock::now();
  // START MATRIX PARALLEL CALCULATION
  auto matrix_product_parallel_result = MatrixParallelProduct(matrix_1, matrix_2);
  // END   MATRIX PARALLEL CALCULATION
  auto matrix_parallel_end_time = std::chrono::high_resolution_clock::now();
  auto matrix_parallel_elapsed_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(matrix_parallel_end_time - matrix_parallel_start_time).count();
  std::cout << "PARALLEL:" << std::endl
            << "TIME:\t" << matrix_parallel_elapsed_time << " ns" << std::endl;
  if (print_matrix) std::cout << "RESULT:" << std::endl << matrix_product_parallel_result;
  std::cout << "EFF:\t"
            << static_cast<long double>(matrix_sequence_elapsed_time) / static_cast<long double>(matrix_parallel_elapsed_time)
            << std::endl;
#endif
  return 0;
}
