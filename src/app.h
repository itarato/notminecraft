#pragma once

#include "config.h"
#include "raylib.h"
#include "rlgl.h"

#define CUBE_SIZE 2.0f
#define CUBE_SIZE_HALF 1.0f

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

void DrawCubeTexture(Texture2D *textures, Vector3 position, Color color) {
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
  for (int i = 0; i < 8; i += 4) {
    rlSetTexture(textures[i / 4].id);
    DrawCubeFace(texcoords, vertices, i);
  }

  for (int i = 8; i < 24; i += 4) {
    rlSetTexture(textures[2].id);
    DrawCubeFace(texcoords, vertices, i);
  }

  rlEnd();
}

struct App {
  App() {
    camera.position = (Vector3){0.0f, 2.0f, 4.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NotMineCraft");
    SetTargetFPS(120);

    cubeTexs[0] = LoadTexture("asset/cube_top.png");
    cubeTexs[1] = LoadTexture("asset/cube_bottom.png");
    cubeTexs[2] = LoadTexture("asset/cube_side.png");
  }

  ~App() {
    for (int i = 0; i < 6; i++) UnloadTexture(cubeTexs[i]);
    CloseWindow();
  }

  void loop() {
    while (!WindowShouldClose()) {
      UpdateCamera(&camera, CAMERA_FREE);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);

      rlEnableBackfaceCulling();
      rlCullMode(RL_CULL_FACE_BACK);

      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          for (int k = 0; k < 10; k++) {
            Vector3 cubePos{0.0f + CUBE_SIZE * j, 0.0f + CUBE_SIZE * k, 0.0f + CUBE_SIZE * i};
            DrawCubeTexture(cubeTexs, cubePos, WHITE);
          }
        }
      }

      rlDisableBackfaceCulling();

      // DrawCubeWires(cubePos, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, BLACK);
      EndMode3D();

      DrawFPS(10, 10);
      DrawText(TextFormat("Camera: %f  :  %f  :  %f", camera.position.x, camera.position.y, camera.position.z), 10, 30,
               20, DARKGREEN);
      EndDrawing();
    }
  }

 private:
  Camera camera{0};
  Texture2D cubeTexs[3];
};