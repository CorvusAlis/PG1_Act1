#include "Reloj.h"

Reloj::Reloj(float tiempoInicial)
    : tiempoRestante(tiempoInicial), activo(true)
{
}

void Reloj::Actualizar()
{
    if (!activo) return;

    tiempoRestante -= GetFrameTime();

    if (tiempoRestante <= 0)
    {
        tiempoRestante = 0;
        activo = false;
    }
}

void Reloj::Dibujar(int x, int y)
{
    int tiempoEntero = (int)tiempoRestante;

    DrawText(TextFormat("Tiempo: %d", tiempoEntero), x, y, 30, WHITE);
}

void Reloj::RestarTiempo(float segundos)
{
    tiempoRestante -= segundos;

    if (tiempoRestante < 0)
        tiempoRestante = 0;
}

float Reloj::GetTiempo() const
{
    return tiempoRestante;
}

bool Reloj::TiempoAgotado() const
{
    return tiempoRestante <= 0;
}