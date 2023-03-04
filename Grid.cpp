#include "Grid.hpp"

Grid::Grid()
{
   cells.resize(NUM_HORIZONTAL_CELLS * NUM_VERTICAL_CELLS);
   for (auto& cell: cells)
   {
      cell.reserve(NUM_BOIDS);
   }
}

void Grid::update_grid(Flock &flock)
{
   for (auto& cell: cells)
   {
      cell.clear();
   }

   for (auto& boid : flock.boids)
   {
      boid.calculate_grid_position();
      cells[boid.grid_position].push_back(&boid);
   }
}

std::vector<Boid*> Grid::get_nearby_boids(Boid &boid)
{
   ;
}