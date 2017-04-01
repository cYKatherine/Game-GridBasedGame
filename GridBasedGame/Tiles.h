#ifndef TILES_H
#define TILES_H

#include "Direct3D.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include <iostream>
#include <cstdlib>
#include <vector>

class Player;

class Tiles {
private:
	std::string m_color;

	Mesh* m_mesh;
	Shader* m_shader;
	Texture* m_texture;
	Matrix m_world;
	Vector3 m_position;

	bool m_visited;
	std::vector<Enemy*> m_enemy;
public:
	Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color);
	Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, bool visited);

	void event(Player* m_player, TextureManager* m_textureManager);
	bool getVisited();

	void Render(Direct3D* renderer, Camera* cam);
	void Update(TextureManager* m_textureManager);

	static std::vector<Vector3>BLUE_TILES;
};
#endif // !TILES_H
