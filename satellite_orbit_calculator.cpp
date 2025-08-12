#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    
    const double GRAVITATIONAL_CONSTANT = 6.67430e-11;  
    const double EARTH_MASS = 5.972e24;                
    const double EARTH_RADIUS = 6371000.0;              
    
    
    double orbital_height_km;
    double orbital_height_m;
    double orbital_radius_m;
    double orbital_period_seconds;
    double orbital_period_minutes;
    double orbital_period_hours;
    
    
    std::cout << "========================================" << std::endl;
    std::cout << "    SATELLITE ORBIT PERIOD CALCULATOR   " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    
    std::cout << "Enter the orbital height above Earth's surface (in kilometers): ";
    std::cin >> orbital_height_km;
    
    
    if (orbital_height_km < 0) {
        std::cout << "Error: Orbital height cannot be negative!" << std::endl;
        return 1;
    }
    
    orbital_height_m = orbital_height_km * 1000.0;
    

    orbital_radius_m = EARTH_RADIUS + orbital_height_m;
    
    // Apply Kepler's Third Law: T = 2π√(R³/GM)
    // Step 1: Calculate R³
    double radius_cubed = pow(orbital_radius_m, 3.0);
    
    // Step 2: Calculate GM (gravitational parameter)
    double gravitational_parameter = GRAVITATIONAL_CONSTANT * EARTH_MASS;
    
    // Step 3: Calculate R³/GM
    double ratio = radius_cubed / gravitational_parameter;
    
    // Step 4: Calculate √(R³/GM)
    double sqrt_ratio = sqrt(ratio);
    
    // Step 5: Calculate T = 2π√(R³/GM)
    orbital_period_seconds = 2.0 * M_PI * sqrt_ratio;
    
    // Convert orbital period to minutes and hours
    orbital_period_minutes = orbital_period_seconds / 60.0;
    orbital_period_hours = orbital_period_seconds / 3600.0;
    
    // Display results with proper formatting
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "            CALCULATION RESULTS         " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "Orbital Height:     " << std::setw(10) << orbital_height_km << " km" << std::endl;
    std::cout << "Orbital Radius:     " << std::setw(10) << orbital_radius_m / 1000.0 << " km" << std::endl;
    std::cout << std::endl;
    std::cout << "ORBITAL PERIOD:" << std::endl;
    std::cout << "  In seconds:       " << std::setw(10) << orbital_period_seconds << " s" << std::endl;
    std::cout << "  In minutes:       " << std::setw(10) << orbital_period_minutes << " min" << std::endl;
    std::cout << "  In hours:         " << std::setw(10) << orbital_period_hours << " hrs" << std::endl;
    
    // Display some interesting comparisons
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "            REFERENCE VALUES            " << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (orbital_height_km >= 35786 - 100 && orbital_height_km <= 35786 + 100) {
        std::cout << "Note: This orbit is close to geostationary orbit!" << std::endl;
        std::cout << "(Geostationary orbit ≈ 35,786 km altitude)" << std::endl;
    }
    
    if (orbital_height_km >= 400 && orbital_height_km <= 420) {
        std::cout << "Note: This is similar to the International Space Station!" << std::endl;
        std::cout << "(ISS orbits at approximately 408 km altitude)" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Calculation completed successfully!" << std::endl;
    
    return 0;
}