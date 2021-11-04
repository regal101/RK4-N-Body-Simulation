#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include "vector2d.h"

#define G 6.67408e-11

typedef std::chrono::high_resolution_clock Clock;
typedef vector2d Vec;

class Particle
{
public:
    Particle();
    Particle(int index, Vec position, Vec velocity, double mass);

    int index;
    Vec position;
    Vec velocity;
    double mass;


    Vec partial_step(Vec f, Vec df, double &timestep, float scale);
    Vec calculate_rk4_acceleration(std::vector<Particle> particles, double &timestep);
    void update_velocity(double &timestep, std::vector<Particle> particles);
    void update_position(double &timestep);
    
    
};
