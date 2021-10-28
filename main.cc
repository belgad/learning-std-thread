#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <cstring>

#include "pi/pi.h"
#include "matrix/matrix.h"

void print_usage(char *path) {
  std::cout
      << "Usage: " << path << " [-t N] [-pi [-i N]] [-matrix [-smin N] [-smax N] [-rmin N] [-rmax N]]" << std::endl
      << std::endl
      << "Available options: " << std::endl
      << "-t N             Maximum thread number (default: 16)" << std::endl
      << "-pi              Calculate pi" << std::endl
      << "-i N             Number of intervals for pi calculation (default: 10^8)" << std::endl
      << "-matrix          Calculate matrix" << std::endl
      << "-smin N          SIZE_MIN size for matrix generation (default: 100)" << std::endl
      << "-smax N          SIZE_MAX matrix generation (default: 1000)" << std::endl
      << "-rmin N          RAND_MIN for matrix generation (default: 0)" << std::endl
      << "-rmax N          RAND_MAX for matrix generation (default: RAND_MAX)" << std::endl;
}

int main(int argc, char *argv[]) {

  if (argc == 1) {
    print_usage(argv[0]);
    return 1;
  }

  size_t max_thread_num = 16;
  size_t pi_interval_num = 100000000;
  size_t size_min = 100, size_max = 1000;
  int rand_min = 0, rand_max = RAND_MAX;
  bool pi_calculation = false, matrix_calculation = false;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-t") == 0) {
      max_thread_num = std::stoull(argv[++i]);
    } else if (strcmp(argv[i], "-pi") == 0) {
      pi_calculation = true;
    } else if (strcmp(argv[i], "-i") == 0) {
      pi_interval_num = std::stoull(argv[++i]);
    } else if (strcmp(argv[i], "-matrix") == 0) {
      matrix_calculation = true;
    } else if (strcmp(argv[i], "-smin") == 0) {
      size_min = std::stoi(argv[++i]);
    } else if (strcmp(argv[i], "-smax") == 0) {
      size_max = std::stoi(argv[++i]);
    } else if (strcmp(argv[i], "-rmin") == 0) {
      rand_min = std::stoi(argv[++i]);
    } else if (strcmp(argv[i], "-rmax") == 0) {
      rand_max = std::stoi(argv[++i]);
    }
  }

  if (!(pi_calculation || matrix_calculation)) {
    print_usage(argv[0]);
    return 1;
  }

  std::cout << "Execution parameters:" << std::endl
  << "  Max thread number:  " << max_thread_num << std::endl;
  if (pi_calculation) {
    std::cout << "  Pi calculation:     true" << std::endl << "  Interval number:    " << pi_interval_num << std::endl;
  } else {
    std::cout << "  Pi calculation:     false" << std::endl;
  }
  if (matrix_calculation) {
    std::cout << "  Matrix calculation: true" << std::endl << "  SIZE_MIN:           " << size_min << std::endl;
    if (size_min > size_max) {
      std::cout << "  SIZE_MIN is greater than SIZE_MAX" << std::endl
                << "  Setting SIZE_MAX equal to SIZE_MIN" << std::endl;
      size_max = size_min;
    } else {
      std::cout << "  SIZE_MAX:           " << size_max << std::endl;
    }
    std::cout << "  RAND_MIN:           " << rand_min << std::endl;
    if (rand_min > rand_max) {
      std::cout << "  RAND_MIN is greater than RAND_MAX" << std::endl
                << "  Setting RAND_MAX equal to RAND_MIN" << std::endl;
      rand_max = rand_min;
    } else {
      std::cout << "  RAND_MAX:           " << rand_max << std::endl;
    }
  } else {
    std::cout << "  Matrix calculation: false" << std::endl;
  }

  std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1);
  if (pi_calculation) {
    std::cout << "PI CALCULATION" << std::endl;
    auto pi_sequence_start_time = std::chrono::high_resolution_clock::now();
    // START PI SEQUENCE CALCULATION
    auto pi_sequence_result = PiSequenceCalculation(pi_interval_num);
    // END   PI SEQUENCE CALCULATION
    auto pi_sequence_end_time = std::chrono::high_resolution_clock::now();
    auto pi_sequence_elapsed_time =
        std::chrono::duration_cast<std::chrono::nanoseconds>(pi_sequence_end_time - pi_sequence_start_time).count();
    std::cout << "  SEQUENCE:" << std::endl
              << "  TIME:    " << pi_sequence_elapsed_time << " ns" << std::endl
              << "  RESULT:  " << pi_sequence_result << std::endl;
    auto pi_parallel_start_time = std::chrono::high_resolution_clock::now();
    // START PI PARALLEL CALCULATION
    auto pi_parallel_result = PiParallelCalculation(pi_interval_num, max_thread_num);
    // END   PI PARALLEL CALCULATION
    auto pi_parallel_end_time = std::chrono::high_resolution_clock::now();
    auto pi_parallel_elapsed_time =
        std::chrono::duration_cast<std::chrono::nanoseconds>(pi_parallel_end_time - pi_parallel_start_time).count();
    std::cout << "  PARALLEL:" << std::endl
              << "  TIME:    " << pi_parallel_elapsed_time << " ns" << std::endl
              << "  RESULT:  " << pi_parallel_result << std::endl;
    std::cout << "  EFF:     "
              << static_cast<long double>(pi_sequence_elapsed_time) / static_cast<long double>(pi_parallel_elapsed_time)
              << std::endl;
  }
  if (matrix_calculation) {
    std::mt19937 random_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> uniform_size_t_distribution(size_min, size_max);
    size_t size_1 = uniform_size_t_distribution(random_engine),
        size_2 = uniform_size_t_distribution(random_engine),
        size_3 = uniform_size_t_distribution(random_engine);
    bool print_matrix = size_1 < 15 && size_2 < 15 && size_3 < 15 && size_1 * size_3 < 100;
    Matrix matrix_1(size_1, size_2, true), matrix_2(size_2, size_3, true, rand_min, rand_max);
    std::cout << "MATRIX CALCULATION" << std::endl;
    std::cout << "  SIZE 1:\t" << size_1 << "\tSIZE 2:\t" << size_2 << "\tSIZE 3:\t" << size_3 << std::endl;
    if (print_matrix) std::cout << "  MATRIX 1:" << std::endl << matrix_1 << "  MATRIX_2:" << std::endl << matrix_2;
    auto matrix_sequence_start_time = std::chrono::high_resolution_clock::now();
    // START MATRIX SEQUENCE CALCULATION
    auto matrix_product_sequence_result = MatrixSequenceProduct(matrix_1, matrix_2);
    // END   MATRIX SEQUENCE CALCULATION
    auto matrix_sequence_end_time = std::chrono::high_resolution_clock::now();
    auto matrix_sequence_elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
        (matrix_sequence_end_time - matrix_sequence_start_time).count();
    std::cout << "  SEQUENCE:" << std::endl
              << "  TIME:    " << matrix_sequence_elapsed_time << " ns" << std::endl;
    if (print_matrix) std::cout << "  RESULT:" << std::endl << matrix_product_sequence_result;
    auto matrix_parallel_start_time = std::chrono::high_resolution_clock::now();
    // START MATRIX PARALLEL CALCULATION
    auto matrix_product_parallel_result = MatrixParallelProduct(matrix_1, matrix_2, max_thread_num);
    // END   MATRIX PARALLEL CALCULATION
    auto matrix_parallel_end_time = std::chrono::high_resolution_clock::now();
    auto matrix_parallel_elapsed_time =std::chrono::duration_cast<std::chrono::nanoseconds>
        (matrix_parallel_end_time - matrix_parallel_start_time).count();
    std::cout << "  PARALLEL:" << std::endl
              << "  TIME:    " << matrix_parallel_elapsed_time << " ns" << std::endl;
    if (print_matrix) std::cout << "  RESULT:" << std::endl << matrix_product_parallel_result;
    std::cout << "  EFF:     "
              << static_cast<long double>(matrix_sequence_elapsed_time)
                  / static_cast<long double>(matrix_parallel_elapsed_time)
              << std::endl;
  }
  return 0;
}
