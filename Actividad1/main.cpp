#include "raylib.h"
#include <string>

#include "Frisky.h"

int main() {
    //init de pantalla
    InitWindow(1024, 600, "Actividad 1");
    SetTargetFPS(60);

    Frisky frisky("assets/frisky.png", { 50, 450 }, 4.0f, 0.0f, 5.0f, true);

    while (!WindowShouldClose())
    {
        ClearBackground(DARKBLUE);

        frisky.ActualizarPos();   //control del movimiento en cada frame

        BeginDrawing();
        frisky.Dibujar();     //render del sprite
        EndDrawing();
    }

    return 0;
}