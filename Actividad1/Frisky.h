#pragma once
#include "raylib.h"
#include <string>

#include "hitbox.h"

using namespace std;

class Frisky {

private:


	Texture2D textura;
	float escala;
	float rotacion;
	bool direccion;

	//atributos para control de movimiento
	Vector2 posicion;
	float velocidad;
	bool activo;

	//atributos para controlar el salto
	bool saltando;
	bool subiendo;
	float alturaSalto;
	float velocidadSalto;
	float pisoY;

	Sound salto;

	Hitbox hitbox;

public:

	//constructor
	Frisky(const string& rutaTextura, Vector2 pos, float escala = 1.0f);

	//destructor
	~Frisky();

	void Dibujar();

	void Mover(float x, float y);
	void SetActivo(bool estado);

	//trabajan en conjunto para 1) ver si esta saltando 2) saltar propiamente
	void Salto();
	void Saltar();

	void SetPosicion(Vector2 pos);

	//controlador principal de movimiento
	void ActualizarPos();

	Vector2 GetPosicion() const;
	Hitbox GetHitbox() const;
};