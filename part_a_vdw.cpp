#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

int main() {
    const double Tc = 407.5, Pc = 111.3, R = 0.08206;
    const double T = 250.0 + 273.15, P = 10.0, tol = 1e-6;

    double a = (27.0 * pow(R, 2) * pow(Tc, 2)) / (64.0 * Pc);
    double b = (R * Tc) / (8.0 * Pc);

    double v_curr = (R * T) / P; // Ideal Gas Guess
    double v_next;
    int iters = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 1000; i++) {
        iters = i;
        v_next = (R * T) / (P + a / pow(v_curr, 2)) + b;
        if (abs(v_next - v_curr) < tol) break;
        v_curr = v_next;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(8) << "Volume: " << v_next << " L/mol" << endl;
    cout << "Iterations: " << iters << "\nTime: " << elapsed.count() << " s" << endl;
    return 0;
}