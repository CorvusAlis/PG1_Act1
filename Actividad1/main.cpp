#include "raylib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Frisky.h"
#include "Caja.h"

vector<Caja> CrearCajas(int cantidad);
vector<int> GenerarNumerosUnicos(int cantidad);

int main() {
    //init de pantalla
    InitWindow(1105, 768, "Actividad 1");
    SetTargetFPS(60);

    int indiceSiguiente = 0;

    Frisky frisky("assets/frisky.png", { 50, 600 }, 2.4f);
    //Caja cajaTest("assets/crate.png", { 400, 600 }, 2.0f, 1);
    vector<Caja> cajas = CrearCajas(10);
    vector<Caja*> orden;   //vector de puntero de cajas

    for (int i = 0; i < cajas.size(); i++)
    {
        orden.push_back(&cajas[i]); //con &cajas paso la direccion de una caja
    }

    //ordenamiento de los PUNTEROS a las cajas. Las cajas originales en el vector cajas no se modifican
    sort(orden.begin(), orden.end(), [](Caja* a, Caja* b) 
       {
          return a->GetNumero() < b->GetNumero();
       });

    while (!WindowShouldClose())
    {
        ClearBackground(DARKBLUE);

        frisky.ActualizarPos();   //control del movimiento en cada frame

        BeginDrawing();

        //for (int i = 0; i < orden.size(); i++)
        //{
        //    DrawText(
        //        TextFormat("%d", orden[i]->GetNumero()),
        //        50,
        //        50 + i * 20,
        //        20,
        //        YELLOW
        //    );
        //}

        frisky.Dibujar();
        //cajaTest.Dibujar();
        for (int i = 0; i < cajas.size(); i++)
        {
            cajas[i].Dibujar(); //las cajas se dibujan desordenadas - el vector de punteros a estas cajas es el que se ordena
        }

        EndDrawing();
    }

    return 0;
}

//funciones auxiliares

//creacion de cajas en vector
vector<Caja> CrearCajas(int cantidad)
{
    vector<Caja> cajas;
    cajas.reserve(cantidad);

    //numeros aleatorios del 1 al 99 SIN REPETIR
    vector<int> numeros = GenerarNumerosUnicos(cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        Vector2 pos = { 75.0f + i * 100.0f, 400.0f }; //distribución horizontal

        //uso de emplace_back para creacion de objetos complejos en vector - evita errores de creacion temporal de objetos presente en push_back
        cajas.
            emplace_back("assets/crate.png", pos, 2.3f, numeros[i]);
    }

    return cajas;
}

//10 numeros aleatorios
//creo un arreglo con numeros ordenados del 1 al 99 - los desordeno con shuffle - tomo los primeros 10
vector<int> GenerarNumerosUnicos(int cantidad)
{
    vector<int> numeros;

    //lleno un arreglo de numeros con rango 1–99
    for (int i = 1; i <= 99; i++)
    {
        numeros.push_back(i);
    }

    //para hacer el desordenamiento random
    random_device rd;
    mt19937 g(rd());    //mt19937 generador pseudoaleatorio de numeros

    shuffle(numeros.begin(), numeros.end(), g);

    //tomar solo los necesarios (en este caso los 10 primeros)
    numeros.resize(cantidad);

    return numeros;
}