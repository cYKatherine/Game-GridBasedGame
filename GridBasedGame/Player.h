#ifndef PLAYER_H
#define PLAYER_H

#include "Direct3D.h"
#include "InputController.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Tiles.h"
#include <iostream>
#include <vector>

class Player {
private:
	InputController* m_input;

	Mesh* m_mesh;
	Matrix m_world;
	Texture* m_texture;
	Shader* m_shader;
	Vector3 m_position;

	float m_uniformScale;
	int m_health;

	bool insideWall(Vector3 currentPosition, std::vector<std::vector<Tiles*>> m_grid);
public:
	Player(Mesh* mesh, InputController* input, Shader* shader, Texture* texture);

	void Update(std::vector<std::vector<Tiles*>> m_grid);
	void Render(Direct3D* renderer, Camera* cam);
};

#endif