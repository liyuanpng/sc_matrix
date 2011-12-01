/*
 * Matrix manipulation operations
 *
 * Copyright (C) 2011 Steve Kerrison <github@stevekerrison.com>
 *
 * This software is freely distributable under a derivative of the
 * University of Illinois/NCSA Open Source License posted in
 * LICENSE.txt and at <http://github.xcore.com/>
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "xc_pointer.h"

// Number of threads to use
// Specify this in your Makefile if you prefer
#ifndef MATRIX_NTHREADS
	#define MATRIX_NTHREADS 4
#endif

#ifdef __XC__
#define MATRIX_NULL() null, null
#else
#define MATRIX_NULL() 0, 0
#endif

#define MATRIX_CREATE(name,rows,columns,...) 			\
	int name[rows * columns] = { __VA_ARGS__ };		\
	short dim##name[4] = {rows,columns,rows,columns}
	
#define MATRIX_REDIM(name,rows,columns)				\
	matrix_redim(dim##name, rows, columns)	
	
#define MATRIX_REF(name) name, dim##name

#define MATRIX_PTR(name) pointer_int(name), pointer_short(dim##name)

#define MATRIX_PRINT(display,name) matrix_print(display,name,dim##name)

#define MATRIX_ROWS(name) (dim##name[0])
#define MATRIX_COLS(name) (dim##name[1])

enum matrix_ops { ADD, SUB, MUL, DIV, SDIV, UDIV, RAND, SET, SHR, ASHR };

int matrix_redim(short dims[4],short rows, short columns);

void matrix_print(char name[], int M[], short dimM[2]);

int matrix_cmp(int A[], short dimA[2], int B[], short dimB[2]);

int matrix_mul(int A[], short dimA[2], int B[], short dimB[2],
			int NULLABLE C[], short NULLABLE dimC[2], char nThreads);

int matrix_arr_op(enum matrix_ops op, int A[], short dimA[2], int B[], short dimB[2],
			int NULLABLE C[], short NULLABLE dimC[2], char nThreads);
			
int matrix_sca_op(enum matrix_ops op, int A[], short dimA[2], int S,
			int NULLABLE C[], short NULLABLE dimC[2], char nThreads);

#endif /* MATRIX_H_ */
