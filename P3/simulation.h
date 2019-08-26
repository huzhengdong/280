#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile);
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
void printGrid(const grid_t &grid);

#endif
