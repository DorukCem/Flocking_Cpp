#include "vector_calculations.hpp"

float magnitude_of_vector(sf::Vector2f &vec)
{
   return sqrt(vec.x * vec.x + vec.y * vec.y);
}


void normalize(sf::Vector2f &vec)
{
   float magnitude = magnitude_of_vector(vec);
   if (magnitude == 0){return ;}
   vec.x /= magnitude;
   vec.y /= magnitude;
}

void limit(sf::Vector2f &vec, float limit)
{
   float magnitude = magnitude_of_vector(vec);
   if (magnitude > limit)
   {
      float multiplier = limit/magnitude;
      vec *= multiplier;
   }
}  