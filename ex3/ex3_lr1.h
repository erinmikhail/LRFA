#ifndef EX3_LR1_H
#define EX3_LR1_H

#include <stdbool.h>


void solve_quadratic(double a, double b, double c, double epsilon);
void generate_perm(double coef[3], double epsilon);
void handle_q_flag(int argc, char *argv[]);
void handle_m_flag(int argc, char *argv[]);
void handle_t_flag(int argc, char *argv[]);

#endif