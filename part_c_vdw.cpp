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

    double v = (R * T) / P, v_old, diff = 1.0;
    int iters = 0;

    auto start = chrono::high_resolution_clock::now();
    while (diff > tol) {
        iters++;
        v_old = v;
        double f = (P + a / pow(v, 2)) * (v - b) - (R * T);
        double df = P - (a / pow(v, 2)) + (2.0 * a * b / pow(v, 3));
        v = v_old - (f / df);
        diff = abs(v - v_old);
    }
    auto end = chrono::high_resolution_clock::now();

    cout << fixed << setprecision(8) << "Volume: " << v << " L/mol" << endl;
    cout << "Iterations: " << iters << "\nTime: " << chrono::duration<double>(end-start).count() << " s" << endl;
    return 0;
}