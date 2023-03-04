#include "Boids.hpp"


int Boid::next_id = 0;

Boid::Boid()
{
   id = next_id++; //This allows every boid to have a unique ID
   float x = rand() % WIDTH;
   float y = rand() % HEIGHT;

   position = sf::Vector2f(20,20);
   velocity = sf::Vector2f(3,0);
}

void Boid::update(float dt)
{
   limit(acceleration,max_force);
   position += velocity;
   velocity += acceleration;
   acceleration.x = 0;
   acceleration.y = 0;
   
}

void Boid::calculate_grid_position()
{
   int col =  int(position.x / CELL_SIZE);
   int row = int(position.y / CELL_SIZE);
   grid_position = col + row * NUM_HORIZONTAL_CELLS;
}

void Boid::steer_to(sf::Vector2f target_position)  // change to return force probably
{
   sf::Vector2f desired_velocity = target_position - position;
   normalize(desired_velocity);
   desired_velocity *= max_speed;
   sf::Vector2f steer_force = desired_velocity - velocity;
   acceleration =  steer_force;
}