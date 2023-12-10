#ifndef MATCHING_H
#define MATCHING_H

#define TIME_LIMIT 1800

#include <cmath>
#include <iostream>
#include <ctime>

void step1(int n, double** dist, int& step);
void step2(int n, const double** dist, int** M, int* RowCover, int* ColCover, int& step);
void step3(int n, const int** M, int* ColCover, int& step);
void step4(int n, const double** matrix, int** M, int* RowCover, int* ColCover, int& path_row_0, int& path_col_0, int& step);
void step5(int n, int** path, int path_row_0, int path_col_0, int** M, int* RowCover, int* ColCover, int& step);
void step6(int n, double** matrix, int* RowCover, int* ColCover, int& step);
bool hungarian(int n, double** original, int** M, time_t start);


#endif