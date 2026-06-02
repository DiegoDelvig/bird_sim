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

            // Cohésion
            Vector2 center_of_mass = {0, 0};
            int birds_in_sight = 0;
            float cohesion_radius = 120.0;

            // Séparation
            Vector2 separation = {0, 0};
            int birds_too_close = 0;
            float separation_radius = 40.0;

            for (int j = 0; j < MAX_BIRDS; j++) {
                if (i != j) {
                    float dx = flock[i].pos.x - flock[j].pos.x;
                    float dy = flock[i].pos.y - flock[j].pos.y;
                    float dist = sqrtf(dx*dx + dy*dy);

                    // Séparation
                    if (dist < separation_radius && dist > 0) {
                        separation.x += dx / dist;
                        separation.y += dy / dist;
                        birds_too_close++;
                    }

                    // Cohésion
                    if (dist < cohesion_radius && dist > 0) {
                        center_of_mass.x += flock[j].pos.x;
                        center_of_mass.y += flock[j].pos.y;
                        birds_in_sight++;
                    }
                }
            }

            // Application des forces

            // Séparation
            if (birds_too_close > 0) {
                separation.x /= birds_too_close;
                separation.y /= birds_too_close;

                flock[i].vel.x += separation.x * 0.5;
                flock[i].vel.y += separation.y * 0.5;
            }

            // Attraction
            if (birds_in_sight > 0) {
                center_of_mass.x /= birds_in_sight;
                center_of_mass.y /= birds_in_sight;

                Vector2 cohesion = {
                    center_of_mass.x - flock[i].pos.x,
                    center_of_mass.y - flock[i].pos.y
                };

                flock[i].vel.x += cohesion.x * 0.005;
                flock[i].vel.y += cohesion.y * 0.005;
            }

            float curr_speed = sqrtf(flock[i].vel.x * flock[i].vel.x + flock[i].vel.y * flock[i].vel.y);
            if (curr_speed > 0) {
                flock[i].vel.x = (flock[i].vel.x / curr_speed) * flock[i].speed;
                flock[i].vel.y = (flock[i].vel.y / curr_speed) * flock[i].speed;
            }

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
