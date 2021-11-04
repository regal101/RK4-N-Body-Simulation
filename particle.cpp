#pragma once

#include "particle.h"

/* Particle */
Particle::Particle()
{
	index = -1;
	position = Vec{ 0,0 };
	velocity = Vec{	0,0	};
	mass = 1;
	
}

Particle::Particle(int ind, Vec pos, Vec vel, double m)
{
	index = ind;
	position = pos;
	velocity = vel;
	mass = m;

}



Vec Particle::partial_step(Vec f, Vec df, double &timestep, float scale)
{
	return Vec{
		f.x + df.x * timestep * scale,
		f.y + df.y * timestep * scale
	};
}

Vec Particle::calculate_rk4_acceleration(std::vector<Particle> particles, double &timestep)
{
	Vec acceleration = Vec{ 0, 0 };

	Vec k1 = Vec{ 0, 0 };
	Vec k2 = Vec{ 0, 0 };
	Vec k3 = Vec{ 0, 0 };
	Vec k4 = Vec{ 0, 0 };
	Vec temp_pos = Vec{ 0, 0 };
	Vec temp_vel = Vec{ 0, 0 };


	for (auto p : particles)
	{
		if (this->index != p.index)
		{
			float r = sqrt(pow(this->position.x - p.position.x, 2) + pow(this->position.y - p.position.y, 2));
			auto temp = G * p.mass / pow(r, 3);

			k1 = (p.position - this->position) * temp;

			temp_vel = partial_step(this->velocity, k1, timestep, 0.5);
			temp_pos = partial_step(this->position, temp_vel, timestep, 0.5);
			k2 = (p.position - temp_pos) * temp;


			temp_vel = partial_step(this->velocity, k2, timestep, 0.5);
			temp_pos = partial_step(this->position, temp_vel, timestep, 0.5);
			k3 = (p.position - temp_pos) * temp;


			temp_vel = partial_step(this->velocity, k3, timestep, 1);
			temp_pos = partial_step(this->position, temp_vel, timestep, 1);
			k4 = (p.position - temp_pos) * temp;


			acceleration = (k1 + (k2 * 2) + (k3 * 2) + k4)/6;
		}

	}
	return acceleration;
}

void Particle::update_velocity(double &timestep, std::vector<Particle> particles)
{
	Vec acceleration = calculate_rk4_acceleration(particles, timestep);
	this->velocity += acceleration * timestep;
	
}

void Particle::update_position(double &timestep)
{
	this->position += this->velocity * timestep;
}