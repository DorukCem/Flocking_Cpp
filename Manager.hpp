#pragma once
#include "Grid.hpp"

class Manager
{
   public:
      void update(Flock& flock, Grid& grid)
      {
         grid.update_grid(flock); //We determine in which cell any boid is

         std::vector<Boid*> nearby_boid;
         
         for (auto& boid: flock.boids)
         {
            nearby_boid = grid.get_nearby_boids(boid);
            boid.num_nearby = nearby_boid.size();
            boid.flocking_behaviour(nearby_boid);
            
            boid.update();
         }
      }
};