#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

const int SIZES[] = {100, 200, 500, 1000, 1500};
const int BLOCK_SIZE = 64;

int** init_matrix(int m) {
    int** matrix = new int*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void multiplication_classic(int **matrix_a, int** matrix_b, int** matrix_r, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int adittion = 0;
            for (int k = 0; k < size; k++) {
                adittion += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_r[i][j] = adittion;
        }
    }
}

void multiplication_blocked(int **matrix_a, int** matrix_b, int** matrix_r, int size) {
    for (int ii = 0; ii < size; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < size; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < size; kk += BLOCK_SIZE) {
                for (int i = ii; i < min(ii + BLOCK_SIZE, size); i++) {
                    for (int j = jj; j < min(jj + BLOCK_SIZE, size); j++) {
                        int adittion = 0;
                        for (int k = kk; k < min(kk + BLOCK_SIZE, size); k++) {
                            adittion += matrix_a[i][k] * matrix_b[k][j];
                        }
                        matrix_r[i][j] += adittion;
                    }
                }
            }
        }
    }
}

int main() {
    int size_num = sizeof(SIZES) / sizeof(SIZES[0]);

    cout << "Multiplication Classic vs Division Blocked" << endl;

    for (int i = 0; i < size_num; i++) {
        int size = SIZES[i];
        cout << "\nArray size: " << size << " x " << size << endl;

        int** matrix_a = init_matrix(size);
        int** matrix_b = init_matrix(size);
        int** matrix_r1 = new int*[size];
        int** matrix_r2 = new int*[size];

        for (int x = 0; x < size; x++) {
            matrix_r1[x] = new int[size];
            matrix_r2[x] = new int[size];
            for (int y = 0; y < size; y++) {
                matrix_r1[x][y] = 0;
                matrix_r2[x][y] = 0;
            }
        }

        auto start1 = chrono::high_resolution_clock::now();
        multiplication_classic(matrix_a, matrix_b, matrix_r1, size);
        auto end1 = chrono::high_resolution_clock::now();
        auto t1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();
        cout << "Classic time: " << t1 << " ms." << endl;

        auto start2 = chrono::high_resolution_clock::now();
        multiplication_blocked(matrix_a, matrix_b, matrix_r2, size);
        auto end2 = chrono::high_resolution_clock::now();
        auto t2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2).count();
        cout << "Blocked time: " << t2 << " ms." << endl;

        for (int del = 0; del < size; del++) {
            delete[] matrix_a[del];
            delete[] matrix_b[del];
            delete[] matrix_r1[del];
            delete[] matrix_r2[del];
        }
        delete[] matrix_a;
        delete[] matrix_b;
        delete[] matrix_r1;
        delete[] matrix_r2;
    }

    return 0;
}
