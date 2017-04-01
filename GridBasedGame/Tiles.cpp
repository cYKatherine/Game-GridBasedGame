#include "Tiles.h"
#include "Player.h"


std::vector<Vector3> Tiles::BLUE_TILES = {};

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;
	m_enemy = {};
	
	m_color = color;
	if (color == "diabled") m_visited = true;
	if (color == "blue") BLUE_TILES.push_back(m_position);
	else m_visited = false;
}

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, bool visited) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;

	m_color = "";
	m_visited = visited;
}

void Tiles::event(Player* m_player, TextureManager* m_textureManager) {
	if (m_color == "blue" && !m_visited) {
		m_texture = m_textureManager->GetTexture("Assets/Textures/tile_disabled.png");
		m_visited = true;
		if (BLUE_TILES.size() > 0) {
			int randNum = rand() % (int)BLUE_TILES.size();
			Vector3 newPosition = BLUE_TILES[randNum];
			m_player->teleport(newPosition);
			BLUE_TILES.erase(BLUE_TILES.begin() + randNum);
		}
	}
	else if (m_color == "red" && !m_visited) {
		int randHealth = rand() % 500 + 1;
		m_player->loseHealth(randHealth);
	}
	else if (m_color == "green" && !m_visited) {
		int randHealth = rand() % 500 + 1;
		m_player->gainHealth(randHealth);
	}
	else if (m_color == "orange" && !m_visited) {
		//Create `participants` vector
		m_visited = true;
		std::vector<Character*> participants;
		participants.push_back(m_player);
		for (int i = 0; i < 5; i++) {
			participants.push_back(EnemyFactory::getInstance()->makeEnemy());
		}

		//Fight continues until player is defeated or there are no enemies left
		std::vector<Character*> stillAlive = participants;
		while (m_player->getHealth() > 0 && stillAlive.size() > 1) {
			//Iterates through the participants vector and calls each character's attack function
			for (Character* attacker : stillAlive) {
				//Ensures that any defeated participants do not get to attack
				if (attacker->getHealth() > 0) {
					attacker->attack(stillAlive);
				}
			}

			// remove dead participants
			// (by extracting the ones that are alive into a new vector and then copying it back to the original)
			std::vector<Character*> tmp;
			for (Character* c : stillAlive) {
				if (c->getHealth() > 0) {
					tmp.push_back(c);
				}
			}
			stillAlive = tmp;
		}


		//Iterates through the participants vector and deletes all participants (but not the player!)
		for (Character* p : participants) {
			if (p != m_player) {
				delete p;
			}
		}
	}
	else if (m_color == "purple" && !m_visited) {
		m_visited = true;
		std::vector<Character*> participants;
		participants.push_back(m_player);
		participants.push_back(EnemyFactory::getInstance()->makeEnemy());

		//Fight continues until player is defeated or there are no enemies left
		std::vector<Character*> stillAlive = participants;
		while (m_player->getHealth() > 0 && stillAlive.size() > 1) {

			//Iterates through the participants vector and calls each character's attack function
			for (Character* attacker : stillAlive) {
				//Ensures that any defeated participants do not get to attack
				if (attacker->getHealth() > 0) {
					attacker->attack(stillAlive);
				}
			}

			// remove dead participants
			// (by extracting the ones that are alive into a new vector and then copying it back to the original)
			std::vector<Character*> tmp;
			for (Character* c : stillAlive) {
				if (c->getHealth() > 0) {
					tmp.push_back(c);
				}
			}
			stillAlive = tmp;
		}

		//Iterates through the participants vector and deletes all participants (but not the player!)
		for (Character* p : participants) {
			if (p != m_player) {
				delete p;
			}
		}
	}
}

bool Tiles::getVisited() {
	return m_visited;

}

void Tiles::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_world = Matrix::CreateScale(1.0f, 1.0f, 1.0f) * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Tiles::Update(TextureManager* m_textureManager) {
	m_visited = true;
	m_texture = m_textureManager->GetTexture("Assets/Textures/tile_disabled.png");
}
