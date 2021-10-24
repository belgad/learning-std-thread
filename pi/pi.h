//
// Created by glebd on 18.10.2021.
//

#ifndef LEARNING_STD_THREAD__PI_H_
#define LEARNING_STD_THREAD__PI_H_

#include <thread>
#include <vector>
#include <cmath>

extern const size_t kMaxThreadNumber;

long double Func(long double x);
long double PiSequenceCalculation(const long double &dx = 1e-8);
long double PiParallelCalculation(const long double &dx = 1e-8);
void PiParallelCalculationThread(long double x_start, const long double &jump, long double &thread_result);

#endif //LEARNING_STD_THREAD__PI_H_
