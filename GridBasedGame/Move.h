#ifndef MOVE_H
#define MOVE_H

#include "Direct3D.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <iostream>
#include <vector>

class Move {
private:
	Mesh* m_mesh;
	Matrix m_world;
	Texture* m_texture;
	Shader* m_shader;
	Vector3 m_position;

	float m_uniformScale;
	int moveLeft;
public:
	Move(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);

	void Update();
	void Render(Direct3D* renderer, Camera* cam);

	void updateMoveLeft(int move);
	void updatePosition(Vector3 position);
};

#endif
