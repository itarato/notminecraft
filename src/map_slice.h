#pragma once

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "config.h"
#include "map_gen.h"
#include "raylib.h"

// Coord order: X then Z: grid[z][x].

const static int neighbour_offs_map[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct MapSlice {
  std::vector<std::vector<int>> height_map;
  std::vector<std::vector<u_int8_t>> visible_face_mask{};

  MapSlice(std::vector<std::vector<int>> height_map) : height_map(height_map) {
    init_visible_face_map();
  }

  void init_visible_face_map() {
    visible_face_mask.resize(MAP_SIZE);

    for (int z = 0; z < MAP_SIZE; z++) {
      visible_face_mask[z].resize(MAP_SIZE);

      for (int x = 0; x < MAP_SIZE; x++) {
        // Bottom is off for now.
        u_int8_t mask = 0b00111101;
        // Top is always expected to show.

        for (int k = 0; k < 4; k++) {
          int nx = x + neighbour_offs_map[k][0];
          int nz = z + neighbour_offs_map[k][1];
          if (nx < 0 || nz < 0 || nx >= MAP_SIZE || nz >= MAP_SIZE) continue;

          if (height_map[nz][nx] >= height_map[z][x]) {
            mask &= 0xff ^ (1 << (2 + k));
          }
        }

        visible_face_mask[z][x] = mask;
      }
    }
  }
};

MapSlice load_or_generate(int slice_xid, int slice_z_id) {
  std::string slice_xid_str = std::to_string(slice_xid);
  std::string slice_zid_str = std::to_string(slice_z_id);
  std::string file_path = "./terrain_" + slice_xid_str + "_" + slice_zid_str + ".map";

  std::ifstream file_check(file_path.c_str());
  if (!file_check.good()) {
    TraceLog(LOG_INFO, "Terrain file [%s] does not exist, generating.", file_path.c_str());
    generate_terrain(file_path);
  }
  file_check.close();

  std::vector<std::vector<int>> map{};
  std::ifstream map_file(file_path.c_str());

  if (!map_file.is_open()) {
    TraceLog(LOG_ERROR, "Failed to load map: %s", file_path.c_str());
  }

  map.resize(MAP_SIZE);

  for (int i = 0; i < MAP_SIZE; ++i) {
    map[i].resize(MAP_SIZE);
    for (int j = 0; j < MAP_SIZE; ++j) {
      map_file >> map[i][j];
    }
  }

  map_file.close();

  return MapSlice(map);
}
