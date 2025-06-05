#pragma once

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <numbers>
#include <string>
#include <vector>

#include "config.h"

void apply_bump_on_terrain(std::vector<std::vector<float>> &map, int x, int z, int height, int spread) {
  for (int xoffs = -spread; xoffs <= spread + 1; xoffs++) {
    for (int zoffs = -spread; zoffs <= spread + 1; zoffs++) {
      int xabs = x + xoffs;
      int zabs = z + zoffs;
      if (xabs < 0 or zabs < 0 or xabs >= MAP_SIZE or zabs >= MAP_SIZE) continue;

      float dist = std::sqrt((float)(xoffs * xoffs) + (float)(zoffs * zoffs));
      if (dist >= spread) continue;

      float lift = std::sin(((float)spread - dist) / ((float)spread / std::numbers::pi * 2.0)) * (float)height;
      map[x + xoffs][z + zoffs] += lift;
    }
  }
}

void generate_terrain(std::string file_path) {
  std::vector<std::vector<float>> map;
  map.resize(MAP_SIZE);

  for (int i = 0; i < MAP_SIZE; i++) {
    map[i].resize(MAP_SIZE);
  }

  for (int i = 0; i < MAP_BUMP_COUNT; i++) {
    int x = rand() % MAP_SIZE;
    int z = rand() % MAP_SIZE;
    apply_bump_on_terrain(map, x, z, MAP_BUMP_HEIGHT, MAP_BUMP_SPREAD);
  }

  std::ofstream map_file(file_path);

  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      map_file << std::round(map[i][j]) << " ";
    }
    map_file << std::endl;
  }

  map_file.close();
}
