#include <iostream>
#include "Grid.hpp"

void draw(sf::RenderWindow &window, Flock &flock)
{
    for (auto &boid : flock.boids)
    {
        sf::CircleShape circle = sf::CircleShape(20); 
        circle.setPosition(boid.position);
        window.draw(circle);
    }
}

int main()
{
    float dt;
    Flock flock(NUM_BOIDS);
    Grid grid;

    sf::Vector2i mpos; //***
    
    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mpos = sf::Mouse::getPosition(window); // ****
        sf::Vector2f m(mpos);

        flock.update(dt, m);
        
        
        window.clear();
        draw(window, flock);
        window.display();
    }
    

    return 0;
}

//make
//.\main