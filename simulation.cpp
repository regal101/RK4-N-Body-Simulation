#pragma once

#include "simulation.h"
#include "particle.h"

double RandomDouble(double a, double b) {
    double random = ((double)rand()) / (double)RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

Simulation::Simulation() {};

void Simulation::initialise()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Font load failed" << std::endl;
    }
    this->energy_text.setFont(this->font);
    this->energy_text.setCharacterSize(15);
    this->energy_text.setFillColor(sf::Color::White);
    this->energy_text.setPosition(sf::Vector2f(10, 10));

    this->ke_text.setFont(this->font);
    this->ke_text.setCharacterSize(15);
    this->ke_text.setFillColor(sf::Color::White);
    this->ke_text.setPosition(sf::Vector2f(10, 30));

    this->pe_text.setFont(this->font);
    this->pe_text.setCharacterSize(15);
    this->pe_text.setFillColor(sf::Color::White);
    this->pe_text.setPosition(sf::Vector2f(10, 50));

    for (int i = 0; i < 100; i++) {
        this->addParticle(Particle(i,
            Vec{ RandomDouble(0.0,1000.0), RandomDouble(0.0,1000.0) },
            Vec{ RandomDouble(-1.0,1.0), RandomDouble(-1.0,1.0) },
            5 * 10e11));
    }



    this->shape.setFillColor(sf::Color::Blue);

};

void Simulation::update()
{
    start_time = Clock::now();

    for (auto& p : particles)
    {
        p.update_velocity(this->timestep, this->particles);
    }
    for (auto& p : particles)
    {
        p.update_position(this->timestep);
    }

    this->calculate_kinetic_energy();
    this->calculate_potential_energy();

    

};

void Simulation::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    
    for (auto p : particles)
    {
        this->shape.setPosition(sf::Vector2f(p.position.x,p.position.y));
        window.draw(shape);
    }

    this->energy_text.setString("Total: " + std::to_string(this->kinetic_energy + this->potential_energy));
    this->ke_text.setString("Kinetic: " + std::to_string(this->kinetic_energy));
    this->pe_text.setString("Potential: " + std::to_string(this->potential_energy));
    window.draw(this->energy_text);
    window.draw(this->ke_text);
    window.draw(this->pe_text);
    window.display();

    end_time = Clock::now();

    std::cout << "Delta t2-t1: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
        << " microseconds" << std::endl;
};

void Simulation::addParticle(Particle p)
{
    particles.push_back(p);
}

void Simulation::calculate_kinetic_energy()
{
    double kinetic_energy = 0.0;
    for (auto p: particles)
    {
        kinetic_energy += 0.5 * p.mass * (p.velocity.x * p.velocity.x +
                                          p.velocity.y * p.velocity.y);
    }
    this->kinetic_energy = kinetic_energy;
}

void Simulation::calculate_potential_energy()
{
    double potential_energy = 0.0;
    for (auto p1 : particles)
    {
        for (auto p2 : particles)
        {
            if (p2.index != p1.index) {
                potential_energy -= G * p2.mass * p1.mass / sqrt((p1.position.x - p2.position.x) * (p1.position.x - p2.position.x) +
                                                                 (p1.position.y - p2.position.y) * (p1.position.y - p2.position.y));
            }
        }
    }
    this->potential_energy = potential_energy /2.0;
}