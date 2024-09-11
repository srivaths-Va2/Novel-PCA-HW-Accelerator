/* C++ program to implement the Jacobi-Hestenes algorithm */

#include <iostream>
#include <cmath>
#include <vector>

// Import HLS linear algebra library
#include "hls_linear_algebra.h"

#define NUM_ROWS    3       // Number of rows
#define NUM_COLS    3       // Number of columns
#define MAX_ITER    100     // Number of iterations to be carried to convergence
#define EPSILON     1e-9    // Threshold value for convergence

// Function prototypes
void init_input_matrix(std::vector<std::vector<double>>& A);
void init_identity_matrix(std::vector<std::vector<double>>& V);
void jacobi(std::vector<std::vector<double>>& A);
void jacobi_rotate(std::vector<std::vector<double>>& A, int i, int j);

// structure to configure the matrix multiplier
/*
1) ARCH = 2 => floating point data, LOW on Resouces, LOW on throughput, HIGH on Latency
2) INNER_II = 1 => any data type, HIGH on Resources, HIGH on throughput, LOW on Latency
3) UNROLL_FACTOR = 2 => HIGH on Resouce, HIGH on throughput, LOW on latency
*/
struct MY_CONFIG: hls::matrix_multiply_traits<hls::NoTranspose, hls::NoTranspose, A_ROWS, A_COLS, B_ROWS, B_COLS, MATRIX_T, MATRIX_T>{
    static const int ARCH = 2;
    static const int INNER_II = 1;
    static const int UNROLL_FACTOR = 2;
};

/**
 * Main function to find eigenvalues using Jacobi iterations.
 * Initializes input and identity matrices, performs Jacobi iterations on the input matrix.
 * 
 * @return 0 on successful completion
 */
int main() {
    // Define and initialize the input matrix and identity matrix
    std::vector<std::vector<double>> A(NUM_ROWS, std::vector<double>(NUM_COLS));
    std::vector<std::vector<double>> V(NUM_ROWS, std::vector<double>(NUM_COLS));

    init_input_matrix(A);
    init_identity_matrix(V);

    // Perform Jacobi iterations to find eigenvalues
    jacobi(A);

    return 0;
}

/**
 * Initialize the input matrix with predefined values.
 */
void init_input_matrix(std::vector<std::vector<double>>& A) {
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;
    A[2][0] = 7; A[2][1] = 8; A[2][2] = 9;
}

/**
 * Initializes an identity matrix to store eigenvalues and vectors.
 */
void init_identity_matrix(std::vector<std::vector<double>>& V) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            V[i][j] = (i == j) ? 1 : 0;
        }
    }
}

/**
 * Perform the Jacobi iteration on a given matrix A to find the eigenvalues.
 * 
 * @param A The matrix on which the Jacobi iteration is performed
 */
void jacobi(std::vector<std::vector<double>>& A) {
    int i = 0;
    int j = 0;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        double max = 0;
        for (int r = 0; r < NUM_ROWS; r++) {
            for (int c = 0; c < NUM_COLS; c++) {
                if (r != c) {
                    if (A[r][c] > max) {
                        max = A[r][c];
                        i = r;
                        j = c;
                    }
                }
            }
        }

        if (max < EPSILON) {
            break;
        }

        // Compute the Jacobi rotation
        jacobi_rotate(A, i, j); 
    }
}

/**
 * Perform a Jacobi rotation on a given matrix A at indices i and j.
 * Update the matrix A with the rotation and construct a Jacobi rotation matrix P.
 * Update the eigenvector matrix V using optimized multipliers.
 */
void jacobi_rotate(std::vector<std::vector<double>>& A, int i, int j) {
    double theta = 0;
    theta = 0.5 * atan((2 * A[i][j]) / (A[i][i] - A[j][j]));

    // Constructing a Jacobi rotation matrix P
    std::vector<std::vector<double>> P(NUM_ROWS, std::vector<double>(NUM_COLS));
    
    // Populating the matrix with 1's at the diagonal
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            P[i][j] = (i == j) ? 1 : 0;
        }
    }

    // Getting the sine and cosine terms to be populated in the array
    double c = cos(theta);
    double s = sin(theta);

    // Populating the sine and cosine terms
    A[i][i] = c;
    A[j][j] = c;
    A[i][j] = s;
    A[j][i] = -s;

    // Define a result matrix to store multiplication of A and P
    std::vector<std::vector<double>> Res(NUM_ROWS, std::vector<double>(NUM_COLS));

    // Convert std::vector matrices A and P to C-style arrays for HLS multiplication
    double A_array[NUM_ROWS][NUM_COLS], P_array[NUM_ROWS][NUM_COLS], Res_array[NUM_ROWS][NUM_COLS];
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            A_array[r][c] = A[r][c];
            P_array[r][c] = P[r][c];
        }
    }

    // Multiply A and P using HLS matrix multiplication with MY_CONFIG configuration
    hls::matrix_multiply<hls::NoTranspose, hls::NoTranspose, MY_CONFIG>(A_array, P_array, Res_array);

    // Copy result back from Res_array to std::vector Res
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            Res[r][c] = Res_array[r][c];
        }
    }

    // Transpose of matrix P
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            P[j][i] = P[i][j];
        }
    }

    // Update the eigenvector matrix V
    // V = VP, using optimized multiplier provided by Xilinx HLS
    // Convert std::vector matrices V and P to C-style arrays for HLS multiplication
    double V_array[NUM_ROWS][NUM_COLS], P_array[NUM_ROWS][NUM_COLS];
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            V_array[r][c] = V[r][c];
            P_array[r][c] = P[r][c];
        }
    }

    // Multiply V and P using HLS matrix multiplication with MY_CONFIG configuration
    hls::matrix_multiply<hls::NoTranspose, hls::NoTranspose, MY_CONFIG>(V_array, P_array, V_array);

    // Copy result back from V_array to std::vector v
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            V[r][c] = V_array[r][c];
        }
    }


    
}
