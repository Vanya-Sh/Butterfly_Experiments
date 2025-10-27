#pragma once

#include "matrix.h"
#include "filters.h"
#include <cmath>
#include <random>

using namespace std;

double dth = 0;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double get_torque(double theta, double dtheta, double t)
{   
    static double theta0=theta;    
    auto e = 0.03;   
    auto w = 8;
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<double> U(0.0, 2.0 * M_PI);  
    static double phi = U(rng);
    static double t_prew = -1.0;
    if (t_prew >= 0.0 && t < t_prew){
        phi = U(rng);
        std::cout<<"NEW RUN phi = "<< phi
                 << "rad(" << phi*180.0/M_PI<< " deg)\n";   
    }
    if (t_prew < 0){
        std::cout<<"First RUN phi = "<< phi
                 << "rad(" << phi*180.0/M_PI<< " deg)\n";
    }
    t_prew = t;
    auto tau = e*std::sin(w*t + phi);
    

    return tau;
}