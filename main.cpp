#pragma once

#include "simulation.h"

int main()
{


    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulation");

    Simulation sim;

    sim.initialise();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sim.update();

        sim.draw(window);


    }


    return 0;
}