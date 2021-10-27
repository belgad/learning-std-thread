//
// Created by glebd on 18.10.2021.
//

#include "pi.h"

double Func(double x) {
  return 4.0 / (1.0 + x * x);
}

double PiSequenceCalculation(const size_t &interval_num) {
  double pi = 0.0, dx = 1.0 / static_cast<double>(interval_num);
  for (double x = 0.0; x < 1.0; x += dx) {
    pi += Func(x);
  }
  pi *= dx;
  return pi;
}

double PiParallelCalculation(const size_t &interval_num, const size_t &max_thread_num) {
  double pi = 0.0, x_start = 0.0, dx = 1.0 / static_cast<double>(interval_num);
  size_t thread_number = std::min(max_thread_num, static_cast<size_t>(ceill(1.0 / dx)));
  double jump = dx * static_cast<double>(thread_number);
  std::vector<std::thread *> threads(thread_number);
  std::vector<double> thread_results(thread_number, 0);
  for (size_t i = 0; i < thread_number; ++i, x_start += dx) {
    threads[i] = new std::thread(&PiParallelCalculationThread, x_start, std::cref(jump), std::ref(thread_results[i]));
  }
  for (size_t i = 0; i < thread_number; ++i) {
    threads[i]->join();
    pi += thread_results[i];
  }
  pi *= dx;
  return pi;
}

void PiParallelCalculationThread(double x_start, const double &jump, double &thread_result) {
  for (; x_start < 1.0; x_start += jump) {
    thread_result += Func(x_start);
  }
}
