// Galia Shabanova CS-01
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void predator_prey(int numVictims, int numKillers, double alpha1, double beta1, double alpha2,
                    double beta2, double timeLimit, int numPoints) {

    double interval = timeLimit / numPoints;
    auto *victims = new double[numPoints + 1];
    auto *killers = new double[numPoints + 1];
    auto *timeslots = new double[numPoints + 1];
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
int main() {

    int numVictims;
    int numKillers;
    double alpha1;
    double beta1;
    double alpha2;
    double beta2;
    double timeLimit;
    int numPoints;

    cin >> numVictims;
    cin >> numKillers;
    cin >> alpha1;
    cin >> beta1;
    cin >> alpha2;
    cin >> beta2;
    cin >> timeLimit;
    cin >> numPoints;

    predator_prey(numVictims, numKillers, alpha1, beta1, alpha2, beta2, timeLimit, numPoints);
    return 0;
}
