#ifndef TILES_H
#define TILES_H

#include "Direct3D.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureManager.h"
#include <iostream>
#include <cstdlib>


class Tiles {
private:
	//const std::string COLOR_SET[6] = { "red", "green", "blue", "grey", "orange", "purple" };
	std::string m_color;

	Mesh* m_mesh;
	Shader* m_shader;
	Texture* m_texture;
	Matrix m_world;
	Vector3 m_position;

	bool m_visited;
public:
	Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color);
	Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, bool visited);

	std::string getColor();
	bool getVisited();

	void Render(Direct3D* renderer, Camera* cam);
	void Update();
};
#endif // !TILES_H
