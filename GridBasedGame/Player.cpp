#include "Player.h"
#include "Tiles.h"

void Player::damageTarget(Character* target, int damage)
{
	target->setHealth(target->getHealth() - damage);
	if (target->getHealth() <= 0) {
		m_enemyKilled += 1;
		if (dynamic_cast<Enemy*>(target)->getRank() == "Hatchling") m_score += 1;
		else if (dynamic_cast<Enemy*>(target)->getRank() == "Grunt") m_score += 2;
		else if (dynamic_cast<Enemy*>(target)->getRank() == "baby") m_score += 3;
		else if (dynamic_cast<Enemy*>(target)->getRank() == "Queen") m_score += 4;
		else if (dynamic_cast<Enemy*>(target)->getRank() == "Berserker") m_score += 5;
		else if (dynamic_cast<Enemy*>(target)->getRank() == "Red") m_score += 6;
	}
}

Player::Player(Mesh* mesh, InputController* input, Shader* shader, Texture* texture, Move* move, Vector3 position) : Character(m_health, m_strength, m_magic) {
	m_mesh = mesh;
	m_input = input;
	m_shader = shader;
	m_texture = texture;
	m_position = position;
	m_move = move;
	m_strength = 50;
	m_magic = 50;
	m_enemyKilled = 0;
	m_score = 0;

	m_health = 2000;
	m_uniformScale = (double)m_health / 2000.00;
	m_world = Matrix::Identity;
}

void Player::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Player::attack(std::vector<Character*> targets) {

	std::vector<Character*>::iterator iter;
	int choice = rand() % targets.size();
	int damage = 0;

	Character* target = targets[choice];

	//Example damage calculation involving strength and magic stats of both characters
	damage = 25 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));

	damageTarget(target, damage);
}

void Player::Update(std::vector<std::vector<Tiles*>> m_grid, TextureManager* m_textureManager) {
	if (m_health <= 0) {
		std::string message = "Your have defeated " + m_enemyKilled;
		MessageBox(0, message.c_str(), "FIT2096 - Assignment 1", MB_OK);
		PostQuitMessage(0);
	}
	if (m_move->getMoveLeft() <= 0) {
		std::string message = "Defeated: " + m_enemyKilled;
		MessageBox(0, message.c_str(), "FIT2096 - Assignment 1", MB_OK);
		PostQuitMessage(0);
	}
	if (m_input->GetKeyDown(VK_LEFT) && insideWall(m_position + Vector3(-1, 0, 0), m_grid)) {
		m_position += Vector3(-1, 0, 0);
		m_move->updateMoveLeft(-1);
	}
	if (m_input->GetKeyDown(VK_RIGHT) && insideWall(m_position + Vector3(1, 0, 0), m_grid)) {
		m_position += Vector3(1, 0, 0);
		m_move->updateMoveLeft(-1);
	}
	if (m_input->GetKeyDown(VK_UP) && insideWall(m_position + Vector3(0, 0, 1), m_grid)) {
		m_position += Vector3(0, 0, 1);
		m_move->updateMoveLeft(-1);
	}
	if (m_input->GetKeyDown(VK_DOWN) && insideWall(m_position + Vector3(0, 0, -1), m_grid)) {
		m_position += Vector3(0, 0, -1);
		m_move->updateMoveLeft(-1);
	}

	m_grid[m_position.x + 5][m_position.z + 4]->event(this, m_textureManager);
	m_grid[m_position.x + 5][m_position.z + 4]->Update(m_textureManager);
	m_move->updatePosition(Vector3(m_position.x, 0.5, m_position.z));
	m_move->Update();

	m_uniformScale = (double)m_health / 2000.00;
	m_world = Matrix::CreateScale(Vector3(m_uniformScale, m_uniformScale, m_uniformScale)) * Matrix::CreateTranslation(m_position);
}

bool Player::insideWall(Vector3 currentPosition, std::vector<std::vector<Tiles*>> m_grid) {
	if ((currentPosition.x >= -5 && currentPosition.x <= 4
		&& currentPosition.z >= -4 && currentPosition.z <= 5
		) && !(m_grid[currentPosition.x + 5][currentPosition.z + 4]->getVisited())
		&& (m_health > 0) && (m_move->getMoveLeft() > 0)
		) return true;
	else return false;
}

void Player::teleport(Vector3 newPosition) {
	m_position = newPosition;
}

void Player::loseHealth(int newHealth) {
	m_health -= newHealth;
}

void Player::gainHealth(int newHealth) {
	m_health += newHealth;
}

Vector3 Player::getPosition() {
	return m_position;
}