#include "Boids.hpp"


int Boid::next_id = 0;

Boid::Boid()
{
   id = next_id++; //This allows every boid to have a unique ID
   float x = rand() % WIDTH;
   float y = rand() % HEIGHT;

   position = sf::Vector2f(20,20);
   velocity = sf::Vector2f(0,0);
}

void Boid::update(float dt)
{
   //stay_in_bounds();
   limit(acceleration,max_force);
   
   position += velocity;
   velocity += acceleration;
   limit(velocity, max_speed);

   acceleration.x = 0;
   acceleration.y = 0;
   
}

void Boid::calculate_grid_position()
{
   int col =  int(position.x / CELL_SIZE);
   int row = int(position.y / CELL_SIZE);
   if (col < 0 or col > NUM_HORIZONTAL_CELLS or row < 0 or row > NUM_VERTICAL_CELLS)
   {
      grid_position = -1; // Not in grid
   }else{
      grid_position = col + row * NUM_HORIZONTAL_CELLS;
   }
   
}

void Boid::steer_to(sf::Vector2f target_position)  // change to return force probably
{
   sf::Vector2f desired_velocity = target_position - position;
   normalize(desired_velocity);
   desired_velocity *= max_speed;
   sf::Vector2f steer_force = desired_velocity - velocity;
   acceleration =  steer_force;
}

void Boid::stay_in_bounds()
{
   if (position.x < OUT_OF_BOUNDS_SIZE){acceleration.x += KEEP_IN_BOUNDS_FORCE;} 
   if (position.x > WIDTH - OUT_OF_BOUNDS_SIZE){acceleration.x -= KEEP_IN_BOUNDS_FORCE;}
   if (position.y < OUT_OF_BOUNDS_SIZE){acceleration.y += KEEP_IN_BOUNDS_FORCE;}
   if (position.y > HEIGHT - OUT_OF_BOUNDS_SIZE){acceleration.y -= KEEP_IN_BOUNDS_FORCE;}
}