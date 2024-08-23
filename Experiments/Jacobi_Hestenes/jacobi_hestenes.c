/* C program to implement the Jacobi-Hestenes algorithm */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define NUM_ROWS    3       // Number of rows
#define NUM_COLS    3       // Number of columns
#define MAX_ITER    100     // Number of iterations to be carried to convergence
#define EPSILON     1e-9    // Threshold value for convergence

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

void jacobi(double A[NUM_ROWS][NUM_COLS])
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
        jacobi_rotate(A, i, j); 
    }
}

void jacobi_rotate(double A[NUM_ROWS][NUM_COLS], int i, int j)
/**
 * Perform a Jacobi rotation on a given matrix A at indices i and j.
 * Update the matrix A with the rotation and construct a Jacobi rotation matrix P.
 * Update the eigenvector matrix V using optimized multipliers.
 */
{
    double theta = 0;

    theta = 0.5 * atan((2 * A[i][j]) / (A[i][i] - A[j][j]));

    // Constructing a Jacobi rotation matrix P
    double P[NUM_ROWS][NUM_COLS];
    // populating the matrix with 1's at the diagonal
    for(int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            P[i][j] = (i == j) ? 1 : 0;
        }
    }

    // getting the sine anc cosine terms to be popukated in the array
    double c = cos(theta);
    double s = sin(theta);

    // populating the sine and cosine terms
    A[i][i] = c;
    A[j][j] = c;
    A[i][j] = s;
    A[j][i] = (-1 * s);

    // add optimized multiplier. Multiply Res = A & P

    // take transpose
    for(int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            P[j][i] = P[i][j];
        }
    }

    // Multiply P^T and Res using same optimized multiplier

    // Update the eigenvector matrix V
    // V = VP, using optimized multiplier provided by Xilinx HLS
}