#pragma once

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "config.h"
#include "map_gen.h"
#include "raylib.h"

struct MapSlice {
  std::vector<std::vector<int>> height_map;
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

  std::vector<std::vector<int>> map;
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

  return std::move(MapSlice(map));
}
