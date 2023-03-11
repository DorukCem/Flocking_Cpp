#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <random>
#include "vector_calculations.hpp"
#include <cstdlib>
#include <ctime>

class Boid
{

public:
   Boid();

   int id;
   int grid_position;
   int num_nearby;

   sf::Vector2f position;
   sf::Vector2f velocity;
   sf::Vector2f acceleration;
   sf::Vector2f direction;
   
   sf::Color color1;
   sf::Color color2;
   
   
   void update();
   void calculate_grid_position();
   void stay_in_bounds();
   void flocking_behaviour(std::vector<Boid*> &nearby_boid);
   
   sf::Vector2f steer_to(sf::Vector2f target_position);
   sf::Vector2f cohesion(std::vector<Boid*> &nearby_boid);
   sf::Vector2f seperation(std::vector<Boid*> &nearby_boid);
   sf::Vector2f alignment(std::vector<Boid*> &nearby_boid);
   
};


// Look into enum class types for predators
// I will steer to the average future position of flockmates for cohesion. 
// 