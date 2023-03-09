#pragma once
#include "Boids.hpp"
#include <vector>

class Flock
{
public:
   std::vector<Boid> boids;

   Flock(int num_boids)
   {
      for (int i = 0; i<num_boids; i++)
      {
         Boid b;
         boids.push_back(b);
      }
   }

   void update(float dt, sf::Vector2f mpos)
   {
      for (auto &boid : boids)
      {
         boid.update(dt);
      }
   }
   
};