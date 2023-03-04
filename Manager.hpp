#pragma once
#include "Grid.hpp"

class Manager
{
   public:
      void update(Flock& flock, Grid& grid)
      {
         grid.update_grid(flock); //We determine in which cell any boid is

         std::vector<Boid*> nearby_boid_p;
         for (auto& boid: flock.boids)
         {
            nearby_boid_p = grid.get_nearby_boids(boid);
            //make_calculations(boid, nearby_boid_p);
            boid.update();
         }
      }
}