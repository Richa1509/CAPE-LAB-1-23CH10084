#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

int main() {
    const double Tc = 407.5, Pc = 111.3, R = 0.08206;
    const double T = 250.0 + 273.15, P = 10.0, tol = 1e-6;

    double a = (0.42748 * pow(R, 2) * pow(Tc, 2.5)) / Pc;
    double b = (0.08664 * R * Tc) / Pc;

    double v = (R * T) / P, v_old, diff = 1.0;
    int iters = 0;

    auto start = chrono::high_resolution_clock::now();
    while (diff > tol) {
        iters++;
        v_old = v;
        double f = P - (R * T) / (v - b) + a / (sqrt(T) * v * (v + b));
        double df = (R * T) / pow(v - b, 2) - (a * (2.0 * v + b)) / (sqrt(T) * pow(v * v + v * b, 2));
        if (abs(df) < 1e-12) { 
        cerr << "Error: Derivative near zero. Solver cannot continue." << endl;
        return 1; // Exit the program with an error code
    }
        v = v_old - (f / df);
        diff = abs(v - v_old);
    }
    auto end = chrono::high_resolution_clock::now();

    cout << fixed << setprecision(8) << "Volume: " << v << " L/mol" << endl;
    cout << "Iterations: " << iters << "\nTime: " << chrono::duration<double>(end-start).count() << " s" << endl;
    return 0;

}
