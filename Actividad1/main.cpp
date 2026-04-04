#include "raylib.h"
#include <string>
#include <vector>

#include "Frisky.h"
#include "Caja.h"

int main() {
    //init de pantalla
    InitWindow(1024, 768, "Actividad 1");
    SetTargetFPS(60);

    Frisky frisky("assets/frisky.png", { 50, 600 }, 3.0f, 0.0f, 5.0f, true);
    Caja cajaTest("assets/crate.png", { 400, 600 }, 2.0f, 1);
    vector<Caja> cajas;

    while (!WindowShouldClose())
    {
        ClearBackground(DARKBLUE);

        frisky.ActualizarPos();   //control del movimiento en cada frame

        BeginDrawing();

        frisky.Dibujar();
        cajaTest.Dibujar();

        EndDrawing();
    }

    return 0;
}