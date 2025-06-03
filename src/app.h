#pragma once

#include "config.h"
#include "raylib.h"
#include "rlgl.h"

void DrawCubeFace(Vector2* texcoords, Vector3* vertices, int i) {
  rlTexCoord2f(texcoords[i].x, texcoords[i].y);
  rlVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

  rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
  rlVertex3f(vertices[i + 1].x, vertices[i + 1].y, vertices[i + 1].z);

  rlTexCoord2f(texcoords[i + 2].x, texcoords[i + 2].y);
  rlVertex3f(vertices[i + 2].x, vertices[i + 2].y, vertices[i + 2].z);

  rlTexCoord2f(texcoords[i + 3].x, texcoords[i + 3].y);
  rlVertex3f(vertices[i + 3].x, vertices[i + 3].y, vertices[i + 3].z);
}

void DrawCubeTexture(Texture2D texture_top, Texture2D texture_side, Texture2D texture_bottom, Vector3 position,
                     float width, float height, float length, Color color) {
  float x = position.x;
  float y = position.y;
  float z = position.z;

  // Enable backface culling
  rlEnableBackfaceCulling();

  // Define vertices for all faces
  // Vertices defined clockwise for each face when looking at the face from outside
  Vector3 vertices[24] = {
      // Top face (+Y)
      {x - width / 2, y + height / 2, z - length / 2},  // Bottom Left
      {x - width / 2, y + height / 2, z + length / 2},  // Top Left
      {x + width / 2, y + height / 2, z + length / 2},  // Top Right
      {x + width / 2, y + height / 2, z - length / 2},  // Bottom Right

      // Bottom face (-Y)
      {x + width / 2, y - height / 2, z + length / 2},  // Top Right
      {x - width / 2, y - height / 2, z + length / 2},  // Top Left
      {x - width / 2, y - height / 2, z - length / 2},  // Bottom Left
      {x + width / 2, y - height / 2, z - length / 2},  // Bottom Right

      // Front face (+Z)
      {x + width / 2, y + height / 2, z + length / 2},  // Top Right
      {x + width / 2, y - height / 2, z + length / 2},  // Bottom Right
      {x - width / 2, y - height / 2, z + length / 2},  // Bottom Left
      {x - width / 2, y + height / 2, z + length / 2},  // Top Left

      // Back face (-Z)
      {x - width / 2, y + height / 2, z - length / 2},  // Top Right
      {x - width / 2, y - height / 2, z - length / 2},  // Bottom Right
      {x + width / 2, y - height / 2, z - length / 2},  // Bottom Left
      {x + width / 2, y + height / 2, z - length / 2},  // Top Left

      // Right face (+X)
      {x + width / 2, y + height / 2, z + length / 2},  // Top Right
      {x + width / 2, y + height / 2, z - length / 2},  // Top Left
      {x + width / 2, y - height / 2, z - length / 2},  // Bottom Left
      {x + width / 2, y - height / 2, z + length / 2},  // Bottom Right

      // Left face (-X)
      {x - width / 2, y + height / 2, z + length / 2},  // Top Right
      {x - width / 2, y + height / 2, z - length / 2},  // Top Left
      {x - width / 2, y - height / 2, z - length / 2},  // Bottom Left
      {x - width / 2, y - height / 2, z + length / 2},  // Bottom Right
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

  rlSetTexture(texture_side.id);
  for (int i = 8; i < 24; i += 4) DrawCubeFace(texcoords, vertices, i);

  rlEnd();

  // Disable backface culling (return to default state)
  rlDisableBackfaceCulling();
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

    cubeTexTop = LoadTexture("asset/cube_top.png");
    cubeTexSide = LoadTexture("asset/cube_side.png");
    cubeTexBottom = LoadTexture("asset/cube_bottom.png");
  }

  ~App() {
    UnloadTexture(cubeTexTop);
    UnloadTexture(cubeTexSide);
    UnloadTexture(cubeTexBottom);
    CloseWindow();
  }

  void loop() {
    Vector3 cubePos{10.0f, 0.0f, 0.0f};

    while (!WindowShouldClose()) {
      UpdateCamera(&camera, CAMERA_FREE);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
      DrawCubeTexture(cubeTexTop, cubeTexSide, cubeTexBottom, cubePos, 2.0f, 2.0f, 2.0f, WHITE);
      DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, BLACK);
      EndMode3D();

      DrawFPS(10, 10);
      EndDrawing();
    }
  }

 private:
  Camera camera{0};
  Texture2D cubeTexTop{0};
  Texture2D cubeTexSide{0};
  Texture2D cubeTexBottom{0};
};