#include <stdio.h>
#include "jacobi_hestenes.h"

// Test Bench for Jacobi-Hestenes Algorithm
int main() {
    // Declare the input matrix
    double A[NUM_ROWS][NUM_COLS];
    double V[NUM_ROWS][NUM_COLS];

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
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    // Print the eigenvector matrix V
    printf("\nEigenvector Matrix V:\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%lf ", V[i][j]);
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
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            fprintf(output_file, "%lf ", A[i][j]);
        }
        fprintf(output_file, "\n");
    }

    // Write the eigenvector matrix V to output.dat
    fprintf(output_file, "\nEigenvector Matrix V:\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            fprintf(output_file, "%lf ", V[i][j]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
    return 0;
}
