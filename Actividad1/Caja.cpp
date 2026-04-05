#include "Caja.h"

Caja::Caja(const string rutaTextura, Vector2 pos, float esc, int num)
    : posicion(pos),
    escala(esc),
    numero(num),
    hitbox(32 * esc, 32 * esc),
    colisionada(false),
    activo(true),
    colorNumero(WHITE)
{
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);
    hitbox.DebugOn(true);
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

    //para dibujar el numero de la caja SOBRE la textura
    //primero se renderiza la textura de la caja (linea de arriba) y luego el numero
    string texto = to_string(numero);

    int fontSize = 20;
    int textWidth = MeasureText(texto.c_str(), fontSize);

    // centrar texto dentro de la caja
    float textX = posicion.x + (dest.width / 2) - (textWidth / 2);
    float textY = posicion.y + (dest.height / 2) - (fontSize / 2);

    DrawText(texto.c_str(), (int)textX, (int)textY, fontSize, colorNumero);

    hitbox.Draw();
}

void Caja::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

void Caja::Actualizar()
{
    hitbox.Sincro(posicion);
}

Vector2 Caja::GetPosicion() const
{
    return posicion;
}

int Caja::GetNumero() const
{
    return numero;
}

const Hitbox& Caja::GetHitbox() const
{
    return hitbox;
}

bool Caja::CheckColisionTrigger(const Hitbox& otra)
{
    bool colision = hitbox.Intersectan(otra);

    bool trigger = colision && !colisionada;

    colisionada = colision;

    return trigger;
}

bool Caja::EstaActiva() const { return activo; }

void Caja::Desactivar() { activo = false; }

void Caja::SetColor(Color c) { colorNumero = c; }