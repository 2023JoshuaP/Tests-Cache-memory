#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

const int SIZES[] = {100, 200, 500, 1000, 1500};

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

int main() {
    int size_num = sizeof(SIZES) / sizeof(SIZES[0]);
    for (int i = 0; i < size_num; i++) {
        int size = SIZES[i];
        cout << "Array size: " << size << " x " << size << endl;

        int** matrix_a = init_matrix(size);
        int** matrix_b = init_matrix(size);
        int** matrix_r = init_matrix(size);

        auto start = chrono::high_resolution_clock::now();
        multiplication_classic(matrix_a, matrix_b, matrix_r, size);
        auto end = chrono::high_resolution_clock::now();

        auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Execution time: " << time.count() << " ms." << endl;

        for (int del = 0; del < size; del++) {
            delete[] matrix_a[del];
            delete[] matrix_b[del];
            delete[] matrix_r[del];
        }

        delete[] matrix_a;
        delete[] matrix_b;
        delete[] matrix_r;
    }

    return 0;
}