#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define MAX_BIRDS 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float speed;
} Bird;

void initBird(Bird *bird) {
    bird->pos = (Vector2) {GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)};
    float angle = GetRandomValue(0, 360);
    bird->speed = (float) GetRandomValue(2, 4);
    bird->vel = (Vector2) {cosf(angle) * bird->speed, sinf(angle) * bird->speed};
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bird Sim - Sim Nuée");
    SetTargetFPS(60);

    Bird flock[MAX_BIRDS];

    for (int i = 0; i < MAX_BIRDS; i++) {
        initBird(&flock[i]);
    }

    while (!WindowShouldClose()) {
        for (int i = 0; i < MAX_BIRDS; i++) {
            flock[i].pos.x += flock[i].vel.x;
            flock[i].pos.y += flock[i].vel.y;

            // Collisions
            if (flock[i].pos.x < 0 || flock[i].pos.x > SCREEN_WIDTH){
                flock[i].vel.x *= -1;
            }
            if (flock[i].pos.y < 0 || flock[i].pos.y > SCREEN_HEIGHT){
                flock[i].vel.y *= -1;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_BIRDS; i++) {
            float angle = atan2f(flock[i].vel.y, flock[i].vel.x) * RAD2DEG + 90;
            DrawPoly(flock[i].pos, 3, 12, angle, SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
