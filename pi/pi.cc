//
// Created by glebd on 18.10.2021.
//

#include "pi.h"

double Func(double x) {
  return 4.0 / (1.0 + x * x);
}

double PiSequenceCalculation(const double &dx) {
  double pi = 0.0;
  for (double x = 0.0; x < 1.0; x += dx) {
    pi += Func(x);
  }
  pi *= dx;
  return pi;
}

double PiParallelCalculation(const double &dx) {
  double pi = 0.0;
  double x_start = 0.0;
  size_t thread_number = std::min(kMaxThreadNumber, static_cast<size_t>(ceill(1.0 / dx)));
  double jump = dx * thread_number;
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
