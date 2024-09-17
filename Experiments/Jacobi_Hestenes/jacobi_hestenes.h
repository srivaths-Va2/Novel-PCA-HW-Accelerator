#ifndef JACOBI_HESTENES_H_
#define JACOBI_HESTENES_H_

#define NUM_ROWS 3
#define NUM_COLS 3

void init_input_matrix();
void init_identity_matrix();
void jacobi(double A[NUM_ROWS][NUM_COLS], double V[NUM_ROWS][NUM_COLS]);
void jacobi_rotate(double A[NUM_ROWS][NUM_COLS], double V[NUM_ROWS][NUM_COLS], int i, int j);

#endif