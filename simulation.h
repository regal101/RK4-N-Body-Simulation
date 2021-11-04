#pragma once

#include "particle.h"


class Simulation
{
public:

	Simulation();
	void initialise();

	void update();
	void draw(sf::RenderWindow& window);

	void addParticle(Particle p);

	void calculate_kinetic_energy();
	void calculate_potential_energy();

	double timestep = 1;
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;

	sf::Font font;
	sf::Text energy_text;
	sf::Text ke_text;
	sf::Text pe_text;

	sf::CircleShape shape = sf::CircleShape(10);
	


private:
	std::vector<Particle> particles;
	double kinetic_energy;
	double potential_energy;
	double total_energy;


};