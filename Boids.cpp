#include "Boids.hpp"


int Boid::next_id = 0;

Boid::Boid()
{
   id = next_id++; //This allows every boid to have a unique ID
   float x = 100 + rand() % (WIDTH - 200);
   float y = 100 + rand() % (HEIGHT - 200);

   position = sf::Vector2f(x,y);
   velocity = sf::Vector2f(2,2);
}

void Boid::update(float dt)
{
   stay_in_bounds();
   limit(acceleration,MAX_FORCE);
   
   position += velocity;
   velocity += acceleration;
   
   limit(velocity, MAX_SPEED);
   limit_min(velocity, MIN_SPEED);

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

sf::Vector2f Boid::steer_to(sf::Vector2f target_position)  // change to return force probably
{
   sf::Vector2f desired_velocity = target_position - position;
   normalize(desired_velocity);
   desired_velocity *= MAX_SPEED;
   return desired_velocity - velocity;
}

void Boid::stay_in_bounds()
{
   if (position.x < OUT_OF_BOUNDS_SIZE){acceleration.x += KEEP_IN_BOUNDS_FORCE;} 
   if (position.x > WIDTH - OUT_OF_BOUNDS_SIZE){acceleration.x -= KEEP_IN_BOUNDS_FORCE;}
   if (position.y < OUT_OF_BOUNDS_SIZE){acceleration.y += KEEP_IN_BOUNDS_FORCE;}
   if (position.y > HEIGHT - OUT_OF_BOUNDS_SIZE){acceleration.y -= KEEP_IN_BOUNDS_FORCE;}
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
  
   acceleration += cohesion(in_range);
   acceleration += seperation(in_range) * 0.5f;
   acceleration += alignment(in_range);
}

sf::Vector2f Boid::cohesion(std::vector<Boid*> &nearby_boid) 
//Avg position of nearby boids
{
   sf::Vector2f sum(0, 0);
   int count = 0;
   for (auto &boid : nearby_boid)
   {
      sum+= boid->position;
      count++;
   }
   if (count == 0){return sum;}
   
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
   sf::Vector2f sum(0, 0);
   float count = 0;
   for (auto &boid : nearby_boid)
   {
      sum += boid->velocity;
      count++;
   }
   if (count == 0){return sum;}
   sum /= count;
   return sum;
}