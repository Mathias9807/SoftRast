#ifndef LOGGER_H
#define LOGGER_H


#include <stdio.h>


void L_InitLogger(int level);

void L_Log(const char* format, ...);
void L_LogLevel(int level, const char* format, ...);
void L_Err(const char* format, ...);
void L_ErrLevel(int level, const char* format, ...);


#endif // LOGGER_H
