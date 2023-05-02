#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void predator_prey(int numVictims, int numKillers, double alpha1, double beta1, double alpha2,
                    double beta2, double timeLimit, int numPoints, double timeslots[], double victims[], double killers[]) {

    double interval = timeLimit / numPoints;

    double t_i = 0;
    double a0;
    double a1;
    double A_0_1 = (0 - alpha2) * beta1 / beta2;
    double A_1_0 = alpha1 * beta2 / beta1;


    for (int i = 0; i < numPoints + 1; i++) {
        if (t_i != timeLimit + interval) {
            a0 = cos(sqrt(alpha1 * alpha2) * t_i);
            a1 = sin(sqrt(alpha1 * alpha2) * t_i) / sqrt(alpha1 * alpha2);
            timeslots[i] = t_i;
            victims[i] = (numVictims - alpha2/beta2)*a0 + (numKillers - alpha1/beta1) * a1 *A_0_1 + alpha2/beta2;
            killers[i] = (numVictims - alpha2/beta2)*a1*A_1_0 + (numKillers - alpha1/beta1)*a0 + alpha1/beta1;
            t_i += interval;
        }
    }
    cout << "t:" << endl;
    for (int i = 0; i < numPoints + 1; i++) {
        cout << fixed << setprecision(2) << timeslots[i] << " ";
    }
    cout << endl;

    cout << "v:" << endl;
    for (int i = 0; i < numPoints + 1; i++) {
        cout << fixed << setprecision(2) << victims[i] << " ";
    }
    cout << endl;

    cout << "k:" << endl;
    for (int i = 0; i < numPoints + 1; i++) {
        cout << fixed << setprecision(2) << killers[i] << " ";
    }
    cout << endl;


}

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#endif

int main() {

#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#endif

    int numVictims = 107;
    int numKillers = 34;
    double alpha1 = 0.36;
    double beta1 = 0.01;
    double alpha2 = 0.32;
    double beta2 = 0.006;
    double timeLimit = 55;
    int numPoints = 220;

    auto *timeslots = new double[numPoints + 1];
    auto *victims = new double[numPoints + 1];
    auto *killers = new double[numPoints + 1];

    predator_prey(numVictims, numKillers, alpha1, beta1, alpha2, beta2, timeLimit, numPoints, timeslots, victims, killers);

    fprintf(pipe, "set multiplot\n");
    fprintf(pipe, "set yrange [0:200]\n");
    fprintf(pipe, "set xrange [0:%lf]\n", timeLimit);
    fprintf(pipe, "plot '-' lc 'green' title 'victims' with lines\n");
    for (int i = 0; i < numPoints + 1; i++) {
        fprintf(pipe, "%lf %lf\n", timeslots[i], victims[i]);
    }

    fprintf(pipe, "e\n");
    fprintf(pipe, "plot '-' lc 'orange' title 'killers' with lines\n");
    for (int i = 0; i < numPoints + 1; i++) {
        fprintf(pipe, "%lf %lf\n", timeslots[i], killers[i]);
    }
    fprintf(pipe, "e\n");
    fprintf(pipe, "unset multiplot\n");
    fprintf(pipe, "plot '-' lc 'blue' title 'v(k)' with lines\n");
    for (int i = 0; i < numPoints + 1; i++) {
        fprintf(pipe, "%lf %lf\n", killers[i], victims[i]);
    }

    fprintf(pipe, "e\n");
    fflush(pipe);
#ifdef WIN32
    _pclose(pipe);
#endif
    return 0;
}
