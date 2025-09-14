#include <iostream>
#include <chrono>
using namespace std;

const int MAX = 1000;
const int BLOCK_DIVISION = 64;
int matrix_A[MAX][MAX], matrix_B[MAX][MAX], matrix_C[MAX][MAX];

void init_arrays() {
    srand(0);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matrix_A[i][j] = rand() % 10;
            matrix_B[i][j] = rand() % 10;
            matrix_C[i][j] = 0;
        }
    }
}

void multiplication_six_loops() {
    for (int ii = 0; ii < MAX; ii += BLOCK_DIVISION) {
        for (int jj = 0; jj < MAX; jj += BLOCK_DIVISION) {
            for (int kk = 0; kk < MAX; kk += BLOCK_DIVISION) {
                for (int i = ii; i < min(ii + BLOCK_DIVISION, MAX); i++) {
                    for (int j = jj; j < min(jj + BLOCK_DIVISION, MAX); j++) {
                        int adittion = 0;
                        for (int k = kk; k < min(kk + BLOCK_DIVISION, MAX); k++) {
                            adittion += matrix_A[i][k] * matrix_B[k][j];
                        }
                        matrix_C[i][j] += adittion;
                    }
                }
            }
        }
    }
}

int main() {
    init_arrays();

    auto start = chrono::high_resolution_clock::now();
    multiplication_six_loops();
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    cout << "Time Blocked: " << time << " ms." << endl;

    return 0;
}