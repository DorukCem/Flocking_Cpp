#pragma once
#include "Flock.hpp"

class Grid
{
public:
   Grid();
   std::vector<std::vector<Boid*>> cells;   
   void update_grid(Flock &flock);
   std::vector<Boid*> get_nearby_boids(Boid &boid);

};