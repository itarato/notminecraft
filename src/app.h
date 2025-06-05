#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "config.h"
#include "map_slice.h"
#include "raylib.h"
#include "rlgl.h"

#define CUBE_SIZE 2.0f
#define CUBE_SIZE_HALF 1.0f

#define TEX_SOIL_TOP 0
#define TEX_SOIL_BOTTOM 1
#define TEX_SOIL_SIDE 2
#define TEX_SAND 3

const static int tex_grass_indices[3] = {TEX_SOIL_TOP, TEX_SOIL_BOTTOM, TEX_SOIL_SIDE};
const static int tex_soil_indices[3] = {TEX_SOIL_SIDE, TEX_SOIL_SIDE, TEX_SOIL_SIDE};
const static int tex_sand_indices[3] = {TEX_SAND, TEX_SAND, TEX_SAND};

void DrawCubeFace(Vector2 *texcoords, Vector3 *vertices, int i) {
  rlTexCoord2f(texcoords[i].x, texcoords[i].y);
  rlVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

  rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
  rlVertex3f(vertices[i + 1].x, vertices[i + 1].y, vertices[i + 1].z);

  rlTexCoord2f(texcoords[i + 2].x, texcoords[i + 2].y);
  rlVertex3f(vertices[i + 2].x, vertices[i + 2].y, vertices[i + 2].z);

  rlTexCoord2f(texcoords[i + 3].x, texcoords[i + 3].y);
  rlVertex3f(vertices[i + 3].x, vertices[i + 3].y, vertices[i + 3].z);
}

void DrawCubeTexture(Texture2D &texture_top, Texture2D &texture_bottom, Texture2D &texture_side, Vector3 position,
                     Color color) {
  float x = position.x;
  float y = position.y;
  float z = position.z;

  // Enable backface culling

  // Define vertices for all faces
  // Vertices defined clockwise for each face when looking at the face from outside
  Vector3 vertices[24] = {
      // Top face (+Y)
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Left
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Left
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Right
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Right

      // Bottom face (-Y)
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Right
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Left
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Left
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Right

      // Front face (+Z)
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Right
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Left
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Bottom Left
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Bottom Right

      // Back face (-Z)
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Top Right
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Top Left
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Left
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Right

      // Right face (+X)
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Right
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Bottom Right
      {x + CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Left
      {x + CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Top Left

      // Left face (-X)
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Top Left
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z - CUBE_SIZE_HALF},  // Bottom Left
      {x - CUBE_SIZE_HALF, y - CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Bottom Right
      {x - CUBE_SIZE_HALF, y + CUBE_SIZE_HALF, z + CUBE_SIZE_HALF},  // Top Right
  };

  // Define texture coordinates for each vertex
  Vector2 texcoords[24] = {
      {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},  // Top
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},  // Bottom
      {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},  // Front
      {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},  // Back
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},  // Right
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},  // Left
  };

  rlBegin(RL_QUADS);
  rlColor4ub(color.r, color.g, color.b, color.a);

  // Draw all faces
  rlSetTexture(texture_top.id);
  DrawCubeFace(texcoords, vertices, 0);

  rlSetTexture(texture_bottom.id);
  DrawCubeFace(texcoords, vertices, 4);

  for (int i = 8; i < 24; i += 4) {
    rlSetTexture(texture_side.id);
    DrawCubeFace(texcoords, vertices, i);
  }

  rlEnd();
}

struct App {
  App() {
    camera.position = Vector3(5.0f, 40.0f, 4.0f);
    camera.target = Vector3(0.0f, 2.0f, 0.0f);
    camera.up = Vector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NotMineCraft");
    SetTargetFPS(120);

    DisableCursor();

    textures.push_back(LoadTexture("asset/cube_top.png"));
    textures.push_back(LoadTexture("asset/cube_bottom.png"));
    textures.push_back(LoadTexture("asset/cube_side.png"));
    textures.push_back(LoadTexture("asset/cube_sand.png"));
  }

  ~App() {
    for (auto &texture : textures) UnloadTexture(texture);
    CloseWindow();
  }

  void loop() {
    MapSlice map_slice = load_or_generate(0, 0);

    while (!WindowShouldClose()) {
      UpdateCamera(&camera, CAMERA_FREE);

      BeginDrawing();
      ClearBackground(Color(220, 230, 255, 255));

      BeginMode3D(camera);

      rlEnableBackfaceCulling();

      for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
          const static int *tex_indices;
          if (map_slice.height_map[j][i] >= 1) {
            tex_indices = tex_grass_indices;
          } else {
            tex_indices = tex_sand_indices;
          }

          Vector3 cube_pos{0.0f + CUBE_SIZE * j, map_slice.height_map[j][i] * CUBE_SIZE, 0.0f + CUBE_SIZE * i};
          DrawCubeTexture(textures[*(tex_indices + 0)], textures[*(tex_indices + 1)], textures[*(tex_indices + 2)],
                          cube_pos, WHITE);

          for (int k = map_slice.height_map[j][i] - 1; k >= 0; k--) {
            Vector3 cube_pos{0.0f + CUBE_SIZE * j, k * CUBE_SIZE, 0.0f + CUBE_SIZE * i};
            DrawCubeTexture(textures[TEX_SOIL_BOTTOM], textures[TEX_SOIL_BOTTOM], textures[TEX_SOIL_BOTTOM], cube_pos,
                            WHITE);
          }
        }
      }

      rlDisableBackfaceCulling();

      EndMode3D();

      DrawFPS(10, 10);
      EndDrawing();
    }
  }

 private:
  Camera camera{0};
  std::vector<Texture2D> textures{};
};