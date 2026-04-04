#include "Caja.h"

Caja::Caja(const string rutaTextura, Vector2 pos, float esc, int num)
    : posicion(pos),
    escala(esc),
    numero(num)
{
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);
}

Caja::~Caja()
{
    UnloadTexture(textura);
}

void Caja::Dibujar()
{
    Rectangle source = { 0, 0, (float)textura.width, (float)textura.height };
    Rectangle dest = { posicion.x, posicion.y, textura.width * escala, textura.height * escala };
    Vector2 origen = { 0, 0 };

    DrawTexturePro(textura, source, dest, origen, 0.0f, WHITE);
}

void Caja::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

Vector2 Caja::GetPosicion() const
{
    return posicion;
}