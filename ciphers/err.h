#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __STATUS_ERR   1
#define __STATUS_WARN  0
#define FatalError(str)    Error(str)
#define Error(str)        fprintf(stderr, "%s\n", str), exit(__STATUS_ERR)
#define Warning(str)      fprintf(stderr, "%s\n", str), exit(__STATUS_WARN)
#define Print(str)        fprintf(stdout, "%s\n", str)
#define PrintInteger(integer)    fprintf(stdout, "%d\n", integer)
#define NewLine()         printf("\n")


typedef int** MATRIX;
typedef int** VECTOR;
typedef int* PTR_I_;
typedef int SIZE;
typedef int KEY_TYPE;
typedef char* STRING;
typedef int BOOL;