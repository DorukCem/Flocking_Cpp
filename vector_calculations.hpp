#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

float magnitude_of_vector(sf::Vector2f &vec);
void normalize(sf::Vector2f &vec);
void limit(sf::Vector2f &vec, float limit);
void limit_min(sf::Vector2f &vec, float limit);
sf::Color lerp(sf::Color a, sf::Color b, float t);