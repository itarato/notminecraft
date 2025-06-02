#pragma once

#include "config.h"
#include "raylib.h"
#include "rlgl.h"

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color) {
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Define vertices for all faces
    // Vertices are defined in counter-clockwise order looking at each face from outside
    Vector3 vertices[24] = {
        // Front face
        {x - width/2, y - height/2, z + length/2},  // Bottom Left
        {x + width/2, y - height/2, z + length/2},  // Bottom Right
        {x + width/2, y + height/2, z + length/2},  // Top Right
        {x - width/2, y + height/2, z + length/2},  // Top Left
        
        // Back face
        {x + width/2, y - height/2, z - length/2},  // Bottom Left
        {x - width/2, y - height/2, z - length/2},  // Bottom Right
        {x - width/2, y + height/2, z - length/2},  // Top Right
        {x + width/2, y + height/2, z - length/2},  // Top Left
        
        // Top face
        {x - width/2, y + height/2, z - length/2},  // Bottom Left
        {x + width/2, y + height/2, z - length/2},  // Bottom Right
        {x + width/2, y + height/2, z + length/2},  // Top Right
        {x - width/2, y + height/2, z + length/2},  // Top Left
        
        // Bottom face
        {x - width/2, y - height/2, z - length/2},  // Bottom Left
        {x + width/2, y - height/2, z - length/2},  // Bottom Right
        {x + width/2, y - height/2, z + length/2},  // Top Right
        {x - width/2, y - height/2, z + length/2},  // Top Left
        
        // Right face
        {x + width/2, y - height/2, z - length/2},  // Bottom Left
        {x + width/2, y - height/2, z + length/2},  // Bottom Right
        {x + width/2, y + height/2, z + length/2},  // Top Right
        {x + width/2, y + height/2, z - length/2},  // Top Left
        
        // Left face
        {x - width/2, y - height/2, z + length/2},  // Bottom Left
        {x - width/2, y - height/2, z - length/2},  // Bottom Right
        {x - width/2, y + height/2, z - length/2},  // Top Right
        {x - width/2, y + height/2, z + length/2}   // Top Left
    };

    // Define texture coordinates for each vertex
    Vector2 texcoords[24] = {
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},  // Front
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},  // Back
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},  // Top
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},  // Bottom
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},  // Right
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}   // Left
    };

    rlBegin(RL_QUADS);
        rlSetTexture(texture.id);
        rlColor4ub(color.r, color.g, color.b, color.a);

        // Draw all faces
        for (int i = 0; i < 24; i += 4) {
            rlTexCoord2f(texcoords[i].x, texcoords[i].y);
            rlVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

            rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
            rlVertex3f(vertices[i + 1].x, vertices[i + 1].y, vertices[i + 1].z);

            rlTexCoord2f(texcoords[i + 2].x, texcoords[i + 2].y);
            rlVertex3f(vertices[i + 2].x, vertices[i + 2].y, vertices[i + 2].z);

            rlTexCoord2f(texcoords[i + 3].x, texcoords[i + 3].y);
            rlVertex3f(vertices[i + 3].x, vertices[i + 3].y, vertices[i + 3].z);
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

        // Load the texture when the app starts
        cubeTex = LoadTexture("asset/cube.png");
    }

    ~App() {
        UnloadTexture(cubeTex);
        CloseWindow();
    }

    void loop() {
        Vector3 cubePos{10.0f, 0.0f, 0.0f};

        while (!WindowShouldClose()) {
            UpdateCamera(&camera, CAMERA_FREE);

            BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            DrawCubeTexture(cubeTex, cubePos, 2.0f, 2.0f, 2.0f, WHITE);
            DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, BLACK);
            EndMode3D();

            DrawFPS(10, 10);
            EndDrawing();
        }
    }

private:
    Camera camera{0};
    Texture2D cubeTex;
};