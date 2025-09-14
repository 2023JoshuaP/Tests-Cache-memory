#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
using namespace std;

const int MAX = 1024;

double A[MAX][MAX], x[MAX], y[MAX];

void init_matrix() {
    srand(0);
    for (int i = 0; i < MAX; i++) {
        x[i] = rand() % 10;
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
        }
    }
}

void first_pair_loops() {
    fill(begin(y), end(y), 0.0);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void second_pair_loops() {
    fill(begin(y), end(y), 0.0);
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    init_matrix();
    auto start_time_first = chrono::high_resolution_clock::now();
    first_pair_loops();
    auto end_time_first = chrono::high_resolution_clock::now();
    double time_first_loop = chrono::duration<double>(end_time_first - start_time_first).count();
    cout << "Time loop i-j is: " << time_first_loop << endl;  

    auto start_time_second = chrono::high_resolution_clock::now();
    second_pair_loops();
    auto end_time_second = chrono::high_resolution_clock::now();
    double time_second_loop = chrono::duration<double>(end_time_second - start_time_second).count();
    cout << "Time loop j-i is:" << time_second_loop << endl;
    
    return 0;
}