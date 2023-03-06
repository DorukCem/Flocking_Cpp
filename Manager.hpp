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
            std::cout << nearby_boid.size();

            std::vector<Boid*> in_range;
            for (auto &nearby : nearby_boid)
            {
            ;
            }
            std::cout << std::endl;
         }
      }
};