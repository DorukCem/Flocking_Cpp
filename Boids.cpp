#include "Boids.hpp"
#include <iostream>
#include <array>

Boid::Boid()
{
   //Every boid is assigned and id at random which determines its flockmates and its color.
   //Boids of the same color flock together

   static std::array<std::pair<sf::Color, sf::Color>, 4> color_pairs = {{
      
      {sf::Color(52, 152, 219), sf::Color(41, 128, 185)},
      {sf::Color(46, 204, 113), sf::Color(39, 174, 96)},
      {sf::Color(241, 196, 15), sf::Color(243, 156, 18)},
      {sf::Color(155, 89, 182), sf::Color(142, 68, 173)}
   }};


   id = rand() % 4;
   color1 = color_pairs[id].first;
   color2 = color_pairs[id].second;

   int x = 100 + rand() % (WIDTH - 200);
   int y = 100 + rand() % (HEIGHT - 200);

   position = sf::Vector2f(x,y);

   //x and y become -1 or 1 at random
   x = (x%2 == 0) ? -1: 1;
   y = (y%2 == 0) ? -1: 1;
   velocity = sf::Vector2f(x,y);
}

void Boid::update()
{
   stay_in_bounds();
   limit(acceleration,MAX_FORCE);
   
   limit(velocity, MAX_SPEED);
   limit_min(velocity, MIN_SPEED);

   position += velocity;
   velocity += acceleration;

   //acceleration only exits if there is a force
   //so it is set 0 after every frame 
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
   {
   if (position.x < OUT_OF_BOUNDS_SIZE){velocity.x += KEEP_IN_BOUNDS_FORCE;} 
   if (position.x > WIDTH - OUT_OF_BOUNDS_SIZE){velocity.x -= KEEP_IN_BOUNDS_FORCE;}
   if (position.y < OUT_OF_BOUNDS_SIZE){velocity.y += KEEP_IN_BOUNDS_FORCE;}
   if (position.y > HEIGHT - OUT_OF_BOUNDS_SIZE){velocity.y -= KEEP_IN_BOUNDS_FORCE;}
   }
}

void Boid::flocking_behaviour(std::vector<Boid*> &nearby_boid)
{
   std::vector<Boid*> in_range;
   float distance;
   sf::Vector2f relative_vector;
   for (auto &boid : nearby_boid)
   {
      relative_vector = this->position - boid->position;
      distance = magnitude_of_vector(relative_vector);
      if (distance <= VISUAL_RANGE)
      {
         in_range.push_back(boid);
      }
   }
   
   // The multiplier are arbitrary nubmers which felt good
   acceleration += cohesion(in_range) * 0.10f;
   acceleration += seperation(in_range) * 3.0f;
   acceleration += alignment(in_range) * 3.0f;
}

sf::Vector2f Boid::cohesion(std::vector<Boid*> &nearby_boid) 
//Go to Avg position of nearby boids
{
   sf::Vector2f sum(0, 0);
   float count = 0.0f;
   for (auto &boid : nearby_boid)
   {
      if (id != boid->id){continue;}
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

   return sum;
}

sf::Vector2f Boid::alignment(std::vector<Boid*> &nearby_boid)
{
   //Get the avg velocity of nearby boids

   sf::Vector2f sum(0, 0);
   float count = 0;
   for (auto &boid : nearby_boid)
   {
      if (id != boid->id){continue;}
      sum += boid->velocity;
      count++;
   }
   if (count == 0){return sum;}
   sum /= count;
   normalize(sum);
   return sum;
}