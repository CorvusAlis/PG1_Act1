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
	Color colorNumero;

	int numero;	//numero generado aleatoriamente

	Hitbox hitbox;
	bool colisionada;
	bool activo;

public:
	Caja(const string rutaTextura, Vector2 pos, float esc, int num);
	~Caja();

	void Dibujar();

	void SetPosicion(Vector2 pos);
	void Actualizar();

	Vector2 GetPosicion() const;
	int GetNumero() const;

	const Hitbox& GetHitbox() const;
	bool CheckColisionTrigger(const Hitbox& otra);

	bool EstaActiva() const;
	void Desactivar();
	void SetColor(Color c);

};