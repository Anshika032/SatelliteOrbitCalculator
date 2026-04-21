#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {

    // ================= PLANET SELECTION =================
    int planet_choice;
    double G = 6.67430e-11;
    double M, R;

    cout << "========================================\n";
    cout << "      ORBIT SIMULATION SYSTEM\n";
    cout << "========================================\n\n";

    cout << "Select Planet:\n";
    cout << "1. Earth\n";
    cout << "2. Mars\n";
    cout << "3. Moon\n";
    cout << "Enter choice: ";
    cin >> planet_choice;

    switch (planet_choice) {
        case 1:
            M = 5.972e24;
            R = 6371000;
            cout << "Planet: Earth\n";
            break;
        case 2:
            M = 6.39e23;
            R = 3389500;
            cout << "Planet: Mars\n";
            break;
        case 3:
            M = 7.35e22;
            R = 1737000;
            cout << "Planet: Moon\n";
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    double mu = G * M;

    // ================= ORBIT TYPE =================
    int orbit_type;
    cout << "\nSelect Orbit Type:\n";
    cout << "1. Circular Orbit\n";
    cout << "2. Elliptical Orbit\n";
    cout << "Enter choice: ";
    cin >> orbit_type;

    double a_km, e;

    if (orbit_type == 1) {
        cout << "Enter orbital height above surface (km): ";
        double height;
        cin >> height;

        a_km = height + (R / 1000.0); // convert to semi-major axis
        e = 0.0;
    }
    else if (orbit_type == 2) {
        cout << "Enter semi-major axis (km): ";
        cin >> a_km;

        cout << "Enter eccentricity (0 <= e < 1): ";
        cin >> e;

        if (e < 0 || e >= 1) {
            cout << "Invalid eccentricity!\n";
            return 1;
        }
    }
    else {
        cout << "Invalid orbit type!\n";
        return 1;
    }

    double a = a_km * 1000.0;

    // ================= ORBITAL PERIOD =================
    double T = 2 * M_PI * sqrt(pow(a, 3) / mu);

    cout << fixed << setprecision(2);

    cout << "\n========================================\n";
    cout << "           ORBIT RESULTS\n";
    cout << "========================================\n";

    cout << "Semi-major axis: " << a_km << " km\n";
    cout << "Eccentricity:    " << e << "\n";
    cout << "Orbital Period:  " << T << " sec ("
         << T / 3600 << " hrs)\n";

    // ================= ORBIT SIMULATION =================
    ofstream file("orbit.csv");

    if (!file) {
        cout << "Error creating file!\n";
        return 1;
    }

    file << "x,y,v\n";

    cout << "\nGenerating orbit data...\n";

    for (double theta = 0; theta <= 2 * M_PI; theta += 0.01) {

        double r = (a * (1 - e*e)) / (1 + e * cos(theta));

        double x = r * cos(theta);
        double y = r * sin(theta);

        // Velocity using Vis-Viva Equation
        double v = sqrt(mu * (2.0/r - 1.0/a));

        file << x/1000 << "," << y/1000 << "," << v << "\n";
    }

    file.close();

    cout << "Orbit data saved to orbit.csv\n";

    // ================= SPECIAL NOTES =================
    if (planet_choice == 1 && fabs(a_km - 42164) < 200) {
        cout << "\nNote: Close to Geostationary Orbit!\n";
    }

    if (planet_choice == 1 && a_km > 6700 && a_km < 7000) {
        cout << "\nNote: Similar to ISS orbit!\n";
    }

    cout << "\nSimulation completed successfully!\n";

    return 0;
}