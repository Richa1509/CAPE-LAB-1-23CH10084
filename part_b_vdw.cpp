#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

double f_vdw(double v, double P, double R, double T, double a, double b) {
    return (P + a / pow(v, 2)) * (v - b) - R * T;
}

int main() {
    const double Tc = 407.5, Pc = 111.3, R = 0.08206;
    const double T = 250.0 + 273.15, P = 10.0, tol = 1e-6;

    double a = (27.0 * pow(R, 2) * pow(Tc, 2)) / (64.0 * Pc);
    double b = (R * Tc) / (8.0 * Pc);

    double v_low = b + 0.01, v_high = 10.0, v_mid;
    int iters = 0;

    auto start = chrono::high_resolution_clock::now();
    while ((v_high - v_low) / 2.0 > tol) {
        iters++;
        v_mid = (v_low + v_high) / 2.0;
        if (f_vdw(v_low, P, R, T, a, b) * f_vdw(v_mid, P, R, T, a, b) < 0) v_high = v_mid;
        else v_low = v_mid;
    }
    auto end = chrono::high_resolution_clock::now();
    
    cout << fixed << setprecision(8) << "Volume: " << v_mid << " L/mol" << endl;
    cout << "Iterations: " << iters << "\nTime: " << chrono::duration<double>(end-start).count() << " s" << endl;
    return 0;
}