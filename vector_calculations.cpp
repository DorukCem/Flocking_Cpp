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

void limit_min(sf::Vector2f &vec, float limit)
{
   float magnitude = magnitude_of_vector(vec);
   if (magnitude == 0){return;}
   if (magnitude < limit)
   {
      float multiplier = limit/magnitude;
      vec *= multiplier;
   }
}

//Lınear Interpolation between colors
sf::Color lerp(sf::Color a, sf::Color b, float t)
{
    return sf::Color(
        (1 - t) * a.r + t * b.r,
        (1 - t) * a.g + t * b.g,
        (1 - t) * a.b + t * b.b,
        (1 - t) * a.a + t * b.a
    );
}