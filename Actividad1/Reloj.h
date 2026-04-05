#pragma once
#include "raylib.h"

class Reloj
{
private:
    float tiempoRestante;
    bool activo;

public:
    Reloj(float tiempoInicial);

    void Dibujar(int x, int y);

    void Actualizar();
    void RestarTiempo(float segundos);

    float GetTiempo() const;
    bool TiempoAgotado() const;
};