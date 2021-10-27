//
// Created by glebd on 18.10.2021.
//

#ifndef LEARNING_STD_THREAD__PI_H_
#define LEARNING_STD_THREAD__PI_H_

#include <thread>
#include <vector>
#include <cmath>

extern const size_t kMaxThreadNumber;

double Func(double x);
double PiSequenceCalculation(const double &dx = 1e-8);
double PiParallelCalculation(const double &dx = 1e-8);
void PiParallelCalculationThread(double x_start, const double &jump, double &thread_result);

#endif //LEARNING_STD_THREAD__PI_H_
