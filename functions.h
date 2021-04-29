#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include "cell.h"
#include "draw_map.h"

std::vector<int> PathFinder (std::vector<std::vector<Cell>> Cell_map, int x1, int y1, int x2, int y2, int W);

#endif // FUNCTIONS_H
