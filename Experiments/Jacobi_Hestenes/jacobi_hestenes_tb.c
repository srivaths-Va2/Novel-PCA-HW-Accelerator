#include <stdio.h>
#include "jacobi_hestenes.h"

#define NUM_ROWS 3
#define NUM_COLS 3

// Test Bench for Jacobi-Hestenes Algorithm
int main() {
    // Declare the input matrix
double A[NUM_ROWS][NUM_COLS] = {
       {1, 2, 3},
       {4, 5, 6},
       {7, 8, 9}
   };
    double V[NUM_ROWS][NUM_COLS] = {0};

    // Initialize the input matrix and identity matrix for eigenvalues/vectors
    init_input_matrix(A);
    init_identity_matrix(V);

    // Print input matrix
    printf("Initial Matrix A:\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    // Perform the Jacobi iteration
    jacobi(A, V);

    // Print the resulting matrix A after convergence
    printf("\nMatrix A after Jacobi rotation:\n");
    for (int i1 = 0; i1 < NUM_ROWS; i1++) {
        for (int j1 = 0; j1 < NUM_COLS; j1++) {
            printf("%lf ", A[i1][j1]);
        }
        printf("\n");
    }

    // Print the eigenvector matrix V
    printf("\nEigenvector Matrix V:\n");
    for (int i2 = 0; i2 < NUM_ROWS; i2++) {
        for (int j2 = 0; j2 < NUM_COLS; j2++) {
            printf("%lf ", V[i2][j2]);
        }
        printf("\n");
    }

    // Write output to a file (output.dat)
    FILE *output_file = fopen("output.dat", "w");
    if (output_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write matrix A to output.dat
    fprintf(output_file, "Matrix A after Jacobi rotation:\n");
    for (int i3 = 0; i3 < NUM_ROWS; i3++) {
        for (int j3 = 0; j3 < NUM_COLS; j3++) {
            fprintf(output_file, "%lf ", A[i3][j3]);
        }
        fprintf(output_file, "\n");
    }

    // Write the eigenvector matrix V to output.dat
    fprintf(output_file, "\nEigenvector Matrix V:\n");
    for (int i4 = 0; i4 < NUM_ROWS; i4++) {
        for (int j4 = 0; j4 < NUM_COLS; j4++) {
            fprintf(output_file, "%lf ", V[i4][j4]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
    return 0;
}