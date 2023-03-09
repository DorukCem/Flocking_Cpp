#include "Boids.hpp"
#include <iostream>

int Boid::next_id = 0;

Boid::Boid()
{
   id = next_id++; //This allows every boid to have a unique ID
   int x = 100 + rand() % (WIDTH - 200);
   int y = 100 + rand() % (HEIGHT - 200);

   position = sf::Vector2f(x,y);

   //x and y become -1 or 1 at random
   x = (x%2 == 0) ? -1: 1;
   y = (y%2 == 0) ? -1: 1;
   velocity = sf::Vector2f(x,y);
}

void Boid::update(float dt)
{
   stay_in_bounds();
   limit(acceleration,MAX_FORCE);
   
   limit(velocity, MAX_SPEED);
   limit_min(velocity, MIN_SPEED);

   position += velocity;
   velocity += acceleration;

   acceleration.x = 0;
   acceleration.y = 0;
   
}

void Boid::calculate_grid_position()
{
   int col =  int(position.x / CELL_SIZE);
   int row = int(position.y / CELL_SIZE);
   if (col < 0 or col >= NUM_HORIZONTAL_CELLS or row < 0 or row >= NUM_VERTICAL_CELLS)
   {
      grid_position = -1; // Not in grid
   }else{
      grid_position = col + row * NUM_HORIZONTAL_CELLS;
   } 
}

sf::Vector2f Boid::steer_to(sf::Vector2f target_position)  
{
   sf::Vector2f desired_velocity = target_position - position;
   normalize(desired_velocity);
   desired_velocity *= MAX_SPEED;
   return desired_velocity - velocity;
}

void Boid::stay_in_bounds()
{
   if (position.x < 0){position.x += WIDTH;} 
   if (position.x > WIDTH){position.x -= WIDTH;}
   if (position.y < 0){position.y += HEIGHT;}
   if (position.y > HEIGHT){position.y -= HEIGHT;}
}

void Boid::flocking_behaviour(std::vector<Boid*> &nearby_boid)
{
   std::vector<Boid*> in_range;
   float len;
   sf::Vector2f relative_vector;
   for (auto &boid : nearby_boid)
   {
      relative_vector = this->position - boid->position;
      len = magnitude_of_vector(relative_vector);
      if (len <= VISUAL_RANGE)
      {
         in_range.push_back(boid);
      }
   }
  
   acceleration += cohesion(in_range) * 0.05f;
   acceleration += seperation(in_range) * 3.0f;
   acceleration += alignment(in_range) * 1.0f;
}

sf::Vector2f Boid::cohesion(std::vector<Boid*> &nearby_boid) 
//Avg position of nearby boids
{
   sf::Vector2f sum(0, 0);
   float count = 0.0f;
   for (auto &boid : nearby_boid)
   {
      sum+= boid->position;
      count++;
   }
   if (count == 0){return sum;}
   sum /= count;
   
   return steer_to(sum);
}


sf::Vector2f Boid::seperation(std::vector<Boid*> &nearby_boid)
{
   sf::Vector2f sum(0, 0);
   sf::Vector2f relative_pos;
   for (auto &boid : nearby_boid)
   {
      relative_pos =  boid->position - position;
      if (magnitude_of_vector(relative_pos) > SEPERATION_DISTANCE){continue;}
      sum -= relative_pos;
   }
   //normalize(sum);
   return sum;
}

sf::Vector2f Boid::alignment(std::vector<Boid*> &nearby_boid)
{
   sf::Vector2f sum(0, 0);
   float count = 0;
   for (auto &boid : nearby_boid)
   {
      sum += boid->velocity;
      count++;
   }
   if (count == 0){return sum;}
   sum /= count;
   normalize(sum);
   return sum;
}