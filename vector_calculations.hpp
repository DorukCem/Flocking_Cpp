#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

float magnitude_of_vector(sf::Vector2f &vec);
void normalize(sf::Vector2f &vec);
void limit(sf::Vector2f &vec, float limit);