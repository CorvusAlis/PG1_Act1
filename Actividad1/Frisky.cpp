#include "Frisky.h"

using namespace std;

Frisky::Frisky(const string& rutaTextura, Vector2 pos, float escala)
    : posicion(pos),
    activo(true),
    escala(escala),
    rotacion(0.0f),
    velocidad(5.0f),
    direccion(true),
    saltando(false),
    subiendo(false),
    alturaSalto(150.0f),
    velocidadSalto(7.0f),
    pisoY(pos.y),
    hitbox(32 * escala, 32 * escala)
{
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);
    hitbox.DebugOn(true);

    //carga de sonidos
    salto = LoadSound("assets/salto.wav");
    SetSoundVolume(salto, 0.5f);
}

Frisky::~Frisky()
{
    UnloadTexture(textura);
}

void Frisky::Dibujar()
{
    hitbox.Sincro(posicion);

    //dibuja todo el ancho y alto de la imagen "textura" (el sprite) y lo renderiza desde el pixel 0,0
    //crea un cuadrado con el tamaño del sprite
    Rectangle frisky = { 0, 0, (float)textura.width, (float)textura.height };

    //controlo para donde esta mirando, e invierte el ancho del rectángulo fuente (frisky), la imagen queda "espejada", segun a donde mire
    if (!direccion)
        frisky.width = -frisky.width;

    //controlo la posicion en pantalla
    Rectangle dest = { posicion.x, posicion.y, textura.width * escala, textura.height * escala };
    Vector2 origen = { 0, 0 }; //usa 0,0 del sprite para rotarlo

    //con WHITE en Color se muestra el color original de la imagen
    DrawTexturePro(textura, frisky, dest, origen, rotacion, WHITE);
    hitbox.Draw();
}

void Frisky::Mover(float x, float y)
{
    posicion.x += x;
    posicion.y += y;
}

void Frisky::ActualizarPos() {

    if (!activo) {
        saltando = false;
        return;
    }

    if (IsKeyPressed(KEY_SPACE) && !saltando) Saltar();
    Salto();

    if (IsKeyDown(KEY_RIGHT)) {
        Mover(velocidad, 0);
        direccion = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        Mover(-velocidad, 0);
        direccion = false;
    }

}

void Frisky::Saltar() {

    //control para evitar spam de salto
    //mientras este en medio del salto, apretar el espacio no hace que salte nuevamente
    if (!saltando) {
        saltando = true;
        subiendo = true;
        PlaySound(salto);
    }
}

void Frisky::Salto() {

    if (!saltando) return;

    if (saltando) {
        if (subiendo) {

            //velocidad del salto - que tantos pixeles "sube" por unidad de tiempo
            posicion.y -= velocidadSalto;

            if (posicion.y <= pisoY - alturaSalto)
                subiendo = false;
        }

        else {
            posicion.y += velocidadSalto;

            if (posicion.y >= pisoY) {
                posicion.y = pisoY; 
                saltando = false;
            }
        }
    }
}

void Frisky::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

void Frisky::SetActivo(bool estado)
{
    activo = estado;
}

Vector2 Frisky::GetPosicion() const
{
    return posicion;
}

Hitbox Frisky::GetHitbox() const {
    return hitbox;
}