#pragma once
#include "raylib.h"
#include <string>

#include "hitbox.h"

using namespace std;

class Caja {

private:
	Texture2D textura;
	Vector2 posicion;
	float escala;

	int numero;	//numero generado aleatoriamente

	Hitbox hitbox;

public:
	Caja(const string rutaTextura, Vector2 pos, float esc, int num);
	~Caja();

	void Dibujar();

	void SetPosicion(Vector2 pos);

	Vector2 GetPosicion() const;
	int GetNumero() const;
	const Hitbox& GetHitbox() const;

};