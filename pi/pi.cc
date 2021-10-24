//
// Created by glebd on 18.10.2021.
//

#include "pi.h"

long double Func(long double x) {
  return 4.0 / (1.0 + x * x);
}

long double PiSequenceCalculation(const long double &dx) {
  long double pi = 0.0;
  for (long double x = 0.0; x < 1.0; x += dx) {
    pi += Func(x);
  }
  pi *= dx;
  return pi;
}

long double PiParallelCalculation(const long double &dx) {
  long double pi = 0.0;
  long double x_start = 0.0;
  size_t thread_number = std::min(kMaxThreadNumber, static_cast<size_t>(ceill(1.0 / dx)));
  long double jump = dx * thread_number;
  std::vector<std::thread *> threads(thread_number);
  std::vector<long double> thread_results(thread_number, 0);
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

void PiParallelCalculationThread(long double x_start, const long double &jump, long double &thread_result) {
  for (; x_start < 1.0; x_start += jump) {
    thread_result += Func(x_start);
  }
}
