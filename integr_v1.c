#include <stdio.h>
#include <math.h>
#include <time.h>

#define TARGET_TIME 15.0
#define TOLERANCE 0.01  // 1% относительная погрешность

double f(double x) {
    return exp(x) * sin(x);
}

double trapezoidal_integral(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.5 * (f(a) + f(b));

    for (int k = 1; k < N; k++) {
        double xk = a + k * h;
        sum += f(xk);
    }
    return h * sum;
}

int main() {
    double a = 0.0, b = M_PI;
    int N = 603288758;
    double elapsed_time = 0.0;
    struct timespec start, end;

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        double result = trapezoidal_integral(a, b, N);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time = (end.tv_sec - start.tv_sec) +
                      (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("N: %d, Время: %.6f сек\n", N, elapsed_time);

        // Проверяем два условия: время ≥ 15 сек И погрешность ≤ 1%
        if (elapsed_time >= TARGET_TIME) {
            double abs_error = elapsed_time - TARGET_TIME;
            double rel_error = fabs(abs_error / elapsed_time) * 100.0;

            if (rel_error <= TOLERANCE * 100.0) {
                printf("\nРезультат:\n");
                printf("Интеграл: %.10f\n", result);
                printf("Время: %.6f сек\n", elapsed_time);
                printf("Абс. погрешность: %.6f сек\n", abs_error);
                printf("Отн. погрешность: %.6f%%\n", rel_error);
                break;
            }
        }

        // Корректируем N
        double scale_factor = TARGET_TIME / elapsed_time;
        scale_factor = fmin(fmax(scale_factor, 0.8), 1.2);  // Ограничение 0.8-1.2
        N = (int)(N * scale_factor);
    }

    return 0;
}
