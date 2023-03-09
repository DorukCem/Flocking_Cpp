#include <iostream>
#include "Grid.hpp"
#include "Manager.hpp"

void draw(sf::RenderWindow &window, Flock &flock)
{
    sf::CircleShape circle(TRIANGLE_WIDTH);
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    sf::Vector2f point1, point2, tangent;

  

    for (auto &boid : flock.boids)
    {
        sf::Vector2f direction = boid.velocity;
        if (magnitude_of_vector(direction) != 0)
        {
            normalize(direction);
            tangent.x = -direction.y;
            tangent.y = direction.x;
            point1 = boid.position - tangent * TRIANGLE_WIDTH - direction * TRIANGLE_HEIGHT;
            point2 = boid.position + tangent * TRIANGLE_WIDTH - direction * TRIANGLE_HEIGHT;
            triangle.setPoint(0, boid.position);
            triangle.setPoint(1, point1);
            triangle.setPoint(2, point2);
            window.draw(triangle);
        }
        else{
            circle.setPosition(boid.position);
            window.draw(circle);
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));

    float dt;
    Flock flock(NUM_BOIDS);
    Grid grid;
    Manager manager;

    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    window.setFramerateLimit(FPS);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        manager.update(flock, grid);
        
        window.clear();
        draw(window, flock);
        window.display();
    }
    

    return 0;
}

//make
//.\main