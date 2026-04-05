#include "raylib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Frisky.h"
#include "Caja.h"
#include "Reloj.h"

//funciones auxiliares
vector<Caja> CrearCajas(int cantidad);
vector<int> GenerarNumerosUnicos(int cantidad);
void DibujarMensaje(const char* msj, Color c);
void OrdenarVisualmente(vector<Caja*>& orden);

int main() {

    InitWindow(1100, 768, "Actividad 1");
    SetTargetFPS(60);

    //init de audio
    InitAudioDevice();

    int indiceSiguiente = 0;
    bool juegoTerminado = false;
    bool juegoGanado = false;

    Frisky frisky("assets/frisky.png", { 500, 600 }, 2.4f);
    vector<Caja> cajas = CrearCajas(10);
    vector<Caja*> orden;   //vector de puntero de cajas
    Reloj reloj(60);

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
        //ACTUALIZACIONES
        if (!juegoTerminado)
        {
            frisky.ActualizarPos();
            reloj.Actualizar();
        }

        for (int i = 0; i < cajas.size(); i++)
        {
            cajas[i].Actualizar();
        }

        //COLISIONES Y ESTADO DE JUEGO
        if (!juegoTerminado) {
            for (int i = 0; i < cajas.size(); i++)
            {
                Caja& caja = cajas[i];

                if (caja.EstaActiva() && caja.CheckColisionTrigger(frisky.GetHitbox()))
                {
                    if (&caja == orden[indiceSiguiente])
                    {
                        caja.SetColor(GREEN);
                        caja.Desactivar();
                        indiceSiguiente++;

                        if (indiceSiguiente >= orden.size())
                        {
                            juegoTerminado = true;
                            juegoGanado = true;
                            frisky.SetActivo(false);
                            OrdenarVisualmente(orden);
                        }
                    }
                    else
                    {
                        caja.SetColor(RED);
                        reloj.RestarTiempo(10.0f);
                    }
                }
            }
        }

        //RESOLUCION DE ESTADO FINAL
        if (!juegoTerminado && reloj.TiempoAgotado())
        {
            juegoTerminado = true;
            juegoGanado = false;
            frisky.SetActivo(false);
            frisky.SetPosicion({ 500, 600 });
            OrdenarVisualmente(orden);
        }

        //RENDER
        BeginDrawing();
        ClearBackground(DARKBLUE);

        frisky.Dibujar();
        reloj.Dibujar(20, 20);

        for (int i = 0; i < cajas.size(); i++)
        {
            cajas[i].Dibujar(); //las cajas se dibujan desordenadas - el vector de punteros a estas cajas es el que se ordena
        }

        if (juegoTerminado)
        {
            if (juegoGanado)
                DibujarMensaje("GANASTE!", GREEN);
            else
                DibujarMensaje("PERDISTE!", RED);
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

//Pantalla de victoria / derrota

void DibujarMensaje(const char* msj, Color c) {

        int fontSize = 40;
        int textWidth = MeasureText(msj, fontSize);

        int x = (GetScreenWidth() / 2) - (textWidth / 2);
        int y = 250;

        DrawText(msj, x, y, fontSize, c);
}

//Ordenamiento de cajas
void OrdenarVisualmente(vector<Caja*>& orden)
{
    for (int i = 0; i < orden.size(); i++)
    {
        Vector2 nuevaPos = { 75.0f + i * 100.0f, 400.0f };
        orden[i]->SetPosicion(nuevaPos);
    }
}