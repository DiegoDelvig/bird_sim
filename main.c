#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

    // Variables changeable en temps réelle
    float separation_radius = 40.0;
    float cohesion_radius = 120.0;
    float separation_force = 0.5;


    while (!WindowShouldClose()) {
        for (int i = 0; i < MAX_BIRDS; i++) {

            Vector2 center_of_mass = {0, 0};
            int birds_in_sight = 0;
            Vector2 separation = {0, 0};
            int birds_too_close = 0;

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

                flock[i].vel.x += separation.x * separation_force;
                flock[i].vel.y += separation.y * separation_force;
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

            // WALLS
            if (flock[i].pos.x > SCREEN_WIDTH) {
                flock[i].pos.x -= SCREEN_WIDTH;
            }
            if (flock[i].pos.y > SCREEN_HEIGHT) {
                flock[i].pos.y -= SCREEN_HEIGHT;
            }
            if (flock[i].pos.x < 0) {
                flock[i].pos.x += SCREEN_WIDTH;
            }
            if (flock[i].pos.y < 0) {
                flock[i].pos.y += SCREEN_HEIGHT;
            }

        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dessin oiseau
        for (int i = 0; i < MAX_BIRDS; i++) {
            float angle = atan2f(flock[i].vel.y, flock[i].vel.x) * RAD2DEG + 90;
            DrawPoly(flock[i].pos, 3, 12, angle, SKYBLUE);
        }

        // Dessin GUI
        DrawRectangle(10, 10, 250, 150, Fade(LIGHTGRAY, 0.8));
        DrawText("Paramètres", 20, 20, 10, DARKGRAY);

        GuiSliderBar((Rectangle){110, 50, 100, 15}, "Rayon de séparation",
                     TextFormat("0.0", separation_radius), &separation_radius,
                     10.0, 100.0);
        GuiSliderBar((Rectangle){110, 80, 100, 15}, "Rayon de cohésion",
                     TextFormat("0.0", cohesion_radius), &cohesion_radius,
                     50.0, 300.0);
        GuiSliderBar((Rectangle){110, 110, 100, 15}, "Force esquive",
                     TextFormat("0.2", separation_force), &separation_force,
                     0.1, 2.0);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}
