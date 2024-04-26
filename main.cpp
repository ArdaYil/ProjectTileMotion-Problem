#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;

const float g = 9.8;
double oldValue = 0;

double degToRad(double rad) {
    return rad * (numbers::pi / 180);
}

double sinDeg(double a) {
    return sin(degToRad(a));
}

double cosDeg(double a) {
    return cos(degToRad(a));
}

double calculateR(int h, int v, int a) {
    return (pow(v, 2) * sinDeg(2 * a))/(2*g) +
    v * cosDeg(a) * sqrt((pow(v, 2) * sinDeg(a) + 2 * h * g)/(pow(g, 2)));
}

void printParameters(int h, int v, int a) {
    cout << "h: " << h << ", v: " << v << ", a: " << a;
}

void resetValues(int& h, int& v, int& a) {
    h = 2;
    v = 12;
    a = 45;
}

void execute(int& h, int& v, int& a) {
    printParameters(h, v, a);

    double newValue = calculateR(h, v, a);

    cout << "   ||   R = " << newValue << "m" << "  ||  " << "dR/dt = " << newValue - oldValue << endl;

    oldValue = newValue;
}

int main() {
    int h = 2;
    int v = 12;
    int a = 45;

    for (int i = 0; i <= 3; i++) {
        execute(i, v, a);
    }

    for (int i = 0; i <= 90; i++) {
        execute(h, v, i);
    }

    ofstream dataFile("data.dat");

    for (int i = 1; i <= 17; i++) {
        dataFile << i << " " << calculateR(h, v, a) << endl;
    }

    FILE *gnuplotPipe = popen("gnuplot -persist", "w");

    fprintf(gnuplotPipe, "set title 'Enkelt grafexempel'\n");
    fprintf(gnuplotPipe, "set xlabel 'X'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y'\n");
    fprintf(gnuplotPipe, "plot 'data.dat' with lines\n");

    pclose(gnuplotPipe);
}
