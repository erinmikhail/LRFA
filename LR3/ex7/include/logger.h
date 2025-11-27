#ifndef LOGGER_H
#define LOGGER_H

void init_logger(const char* filename);
void log_operation(int line_num, const char* command, const char* variables, const char* operation);
void close_logger();

#endif