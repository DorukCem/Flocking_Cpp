#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <random>
#include "vector_calculations.hpp"

class Boid
{

public:
   Boid();
   //~Boid();

   static int next_id;
   int id;
   int grid_position;

   sf::Vector2f position;
   sf::Vector2f velocity;
   sf::Vector2f acceleration;
   float max_speed = 6.00f;
   float max_force = 0.30f;
   
   sf::Color color;
   
   void update(float dt);
   void calculate_grid_position();
   void steer_to(sf::Vector2f target_position);
   void stay_in_bounds();
   void cohesion();

};


// Look into enum class types for predators
// I will steer to the average future position of flockmates for cohesion. 
// 