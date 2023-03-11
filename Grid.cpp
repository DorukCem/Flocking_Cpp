#include "Grid.hpp"
#include <iostream>

bool is_valid(int i,int j)
{
   return (i >= 0 && i < NUM_VERTICAL_CELLS && j >= 0 && j < NUM_HORIZONTAL_CELLS);
}

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
      if (boid.grid_position != -1) //Only if the boid is inside the screen 
      {
         cells[boid.grid_position].push_back(&boid);
      }
   }
}

std::vector<Boid*> Grid::get_nearby_boids(Boid &boid)
{
   //Get all boids in cell and adjacent cells
   std::vector<Boid*> nearby_boids;
   if (boid.grid_position == -1) {return nearby_boids;}

   int row = int(boid.grid_position / NUM_HORIZONTAL_CELLS);
   int col = boid.grid_position % NUM_HORIZONTAL_CELLS;

   for (int i = row - 1; i <= row + 1; i++) {
      for (int j = col - 1; j <= col + 1; j++) 
      {
         if (is_valid(i,j))
         {
            int cell_index = j + i * NUM_HORIZONTAL_CELLS;
            for (auto nearby : cells[cell_index])
            {
               if (nearby != &boid) {
                  nearby_boids.push_back(nearby);
               }
            }
         }  
      
      }
   }
   
   return nearby_boids;
}