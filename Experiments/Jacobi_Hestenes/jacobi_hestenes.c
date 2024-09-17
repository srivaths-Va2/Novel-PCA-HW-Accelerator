/* C program to implement the Jacobi-Hestenes algorithm */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define NUM_ROWS    3       // Number of rows
#define NUM_COLS    3       // Number of columns
#define MAX_ITER    100     // Number of iterations to be carried to convergence
#define EPSILON     1e-9    // Threshold value for convergence


double V[NUM_ROWS][NUM_COLS];

void jacobi_rotate(double A[NUM_ROWS][NUM_COLS], double V[NUM_ROWS][NUM_COLS], int i, int j);


void matrix_multiply(double A[NUM_ROWS][NUM_COLS], double B[NUM_ROWS][NUM_COLS], double result[NUM_ROWS][NUM_COLS])
/**
 * Multiply two matrices A and B and store the result in matrix 'result'.
 * This function will handle both the multiplication of Res = A * P and P^T * Res.
 *
 * @param A The first matrix in the multiplication.
 * @param B The second matrix in the multiplication.
 * @param result The resulting matrix.
 */
{
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < NUM_COLS; k++) {
                result[i][j] += A[i][k] * B[k][j];  // Perform matrix multiplication
            }
        }
    }
}



void init_input_matrix()
/**
 * Initialize the input matrix with predefined values.
 */
{
    // Define input matrix
    double A[NUM_ROWS][NUM_COLS];

    // Initialise the matrix here
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;
    A[2][0] = 7; A[2][1] = 8; A[2][2] = 9;

   
}

void init_identity_matrix()
/**
 * Initializes an identity matrix to store eigenvalues and vectors.
 */
{
    // Define the identity matrix that will store the eigenvalues and vectors
    double V[NUM_ROWS][NUM_COLS];

    // Initialise the identity matrix
    for(int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            V[i][j] = ((i == j) ? 1 : 0);
        }
    }
}

void jacobi(double A[NUM_ROWS][NUM_COLS], double V[NUM_ROWS][NUM_COLS])
/**
 * Perform the Jacobi iteration on a given matrix A to find the eigenvalues.
 *
 * @param A The matrix on which the Jacobi iteration is performed
 */
{
    int i = 0;
    int j = 0;

    for(int iter = 0; iter < MAX_ITER; iter++)
    {
        double max = 0;
        for(int r = 0; r < NUM_ROWS; r++)
        {
            for(int c = 0; c < NUM_COLS; c++)
            {
                if(r != c)
                {
                    if(A[r][c] > max)
                    {
                        max = A[r][c];
                        i = r;
                        j = c;
                    }
                }

            }
        }

        if(max < EPSILON)
        {
            break;
        }

        // Compute the Jacobi rotation
        jacobi_rotate(A, V, i, j);
    }
}

void jacobi_rotate(double A[NUM_ROWS][NUM_COLS], double V[NUM_ROWS][NUM_COLS], int i, int j)
/**
 * Perform a Jacobi rotation on a given matrix A at indices i and j.
 * Update the matrix A with the rotation and construct a Jacobi rotation matrix P.
 * Update the eigenvector matrix V using optimized multipliers.
 */
{
    double theta = 0;

    theta = 0.5 * atan((2 * A[i][j]) / (A[i][i] - A[j][j]));

    double P[NUM_ROWS][NUM_COLS];
    // Use 'row' and 'col' instead of 'i' and 'j'
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            P[row][col] = (row == col) ? 1 : 0;
        }
    }

    double c = cos(theta);
    double s = sin(theta);

    A[i][i] = c;
    A[j][j] = c;
    A[i][j] = s;
    A[j][i] = (-1 * s);

    double Res[NUM_ROWS][NUM_COLS];
    matrix_multiply(A, P, Res);

    for(int row1 = 0; row1 < NUM_ROWS; row1++) {
        for(int col1 = 0; col1 < NUM_COLS; col1++) {
            P[col1][row1] = P[row1][col1];
        }
    }

    matrix_multiply(P, Res, A);

    double tempV[NUM_ROWS][NUM_COLS];
    matrix_multiply(V, P, tempV);
}