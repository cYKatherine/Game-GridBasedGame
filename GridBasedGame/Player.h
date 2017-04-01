#ifndef PLAYER_H
#define PLAYER_H

#include "Direct3D.h"
#include "InputController.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Move.h"
#include "Character.h"
#include <iostream>
#include <vector>

class Tiles;

class Player : public Character{
private:
	InputController* m_input;

	Mesh* m_mesh;
	Matrix m_world;
	Texture* m_texture;
	Shader* m_shader;
	Vector3 m_position;
	Move* m_move;

	float m_uniformScale;
	int m_enemyKilled;
	int m_score;

	bool insideWall(Vector3 currentPosition, std::vector< std::vector<Tiles*> > m_grid);
public:
	Player(Mesh* mesh, InputController* input, Shader* shader, Texture* texture, Move* move, Vector3 position);

	void Player::teleport(Vector3 newPosition);
	void Update(std::vector<std::vector<Tiles*>> m_grid, TextureManager* m_textureManager);
	void Render(Direct3D* renderer, Camera* cam);

	void loseHealth(int newHealth);
	void gainHealth(int newHealth);
	virtual void damageTarget(Character* target, int damage);
	virtual void attack(std::vector<Character*> targets);
	Vector3 getPosition();
};

#endif