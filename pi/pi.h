//
// Created by glebd on 18.10.2021.
//

#ifndef LEARNING_STD_THREAD__PI_H_
#define LEARNING_STD_THREAD__PI_H_

#include <thread>
#include <vector>
#include <cmath>

double Func(double x);
double PiSequenceCalculation(const size_t &interval_num);
double PiParallelCalculation(const size_t &interval_num, const size_t &max_thread_num);
void PiParallelCalculationThread(double x_start, const double &jump, double &thread_result);

#endif //LEARNING_STD_THREAD__PI_H_
