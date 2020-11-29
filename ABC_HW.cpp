#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x) {
    return x + 2;
}

double coarse_helper(double a, double b, double (f)(double)) {
    return 0.5 * (b - a) * (f(a) + f(b));
}

double fine_helper(double a, double b, double (f)(double)) {
    double c = (a + b) / 2.0;
    return 0.25 * (b - a) * (f(a) + 2 * f(c) + f(b));
}

double* a, * b, * c;
int coun = 0, count1 = 0;
double tolerance = 0.1;
double fine, fine1;

double func(double* a, double* b) {
    double coarse = coarse_helper(a[0], c[0], f);
    fine = fine_helper(a[0], c[0], f);
    c[0] /= 2.0;
    if ((fabs(coarse - fine) <= 3.0 * tolerance) && (coun >= 1)) {
        return fine;
    }
    else if (coun >= 10000) {
        return NULL;
    }
    else {
        ++coun;
        return func(a, b);
    }
}

double func1(double* a, double* b) {
    double coarse = coarse_helper(c[1], b[0], f);
    fine1 = fine_helper(c[1], b[0], f);
    c[1] /= 2.0;

    if ((fabs(coarse - fine1) <= 3.0 * tolerance) && (count1 >= 1)) {
        return NULL;
    }
    else if (count1 >= 10000) {
        return NULL;
    }
    else {
        ++count1;
        return func1(a, b);
    }
}


int main() {
    a = new double[1];
    b = new double[1];
    c = new double[2];
    cout << "Write a(left border):";
    cin >> a[0];
    cout << "Write b(right border):";
    cin >> b[0];
    c[0] = (a[0] + b[0]) / 2.0;
    c[1] = (a[0] + b[0]) / 2.0;
    int num[3];
    for (int i = 0; i < 3; i++) num[i] = i;
#pragma omp parallel sections
    {
#pragma omp section
        {
            func1(a, b);

        }
#pragma omp section
        {
            func(a, b);
        }
    }
    cout << fine + fine1;
    return 0;
}