#include <stdio.h>
#include <math.h>
#include <time.h>

#define TARGET_TIME 15.0
#define TOLERANCE 0.005

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
		        struct timespec start_overall, end_overall;
			    
			    clock_gettime(CLOCK_MONOTONIC, &start_overall);

			        while (1) {
					        struct timespec start, end;
						        clock_gettime(CLOCK_MONOTONIC, &start);

							        double result = trapezoidal_integral(a, b, N);

								        clock_gettime(CLOCK_MONOTONIC, &end);
									        elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

										        printf("N: %d, Время выполнения: %.6f секунд\n", N, elapsed_time);

											        if (elapsed_time >=15.0) {
													            clock_gettime(CLOCK_MONOTONIC, &end_overall);
														                double total_elapsed = (end_overall.tv_sec - start_overall.tv_sec) + 
																	                                   (end_overall.tv_nsec - start_overall.tv_nsec) / 1e9;
																            double abs_error = elapsed_time - TARGET_TIME;
																	                double rel_error = fabs(abs_error / elapsed_time) * 100.0;

																			            printf("Приближенное значение интеграла: %.10f\n", result);
																				                printf("Финальное время выполнения: %.6f секунд\n", elapsed_time);
																						            printf("Абсолютная погрешность: %.6f секунд\n", abs_error);
																							                printf("Относительная погрешность: %.6f%%\n", rel_error);
																									            break;
																										            }

												        double scale_factor = TARGET_TIME / elapsed_time;
													        if (scale_factor > 1.2) scale_factor = 1.2;
														        if (scale_factor < 0.8) scale_factor = 0.8;

															        N = (int)(N * scale_factor);
																    }

				    return 0;
}

