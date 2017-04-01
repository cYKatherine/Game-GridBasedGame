#include "Tiles.h"
#include "Player.h"


std::vector<Vector3> Tiles::BLUE_TILES = {};

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;
	
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
		int randHealth = rand() % 50 + 1;
		m_player->loseHealth(randHealth);
	}
	else if (m_color == "green" && !m_visited) {
		int randHealth = rand() % 50 + 1;
		m_player->getHealth(randHealth);
	}
	else if (m_color == "orange" && !m_visited) {
	
	}
	else if (m_color == "purple" && !m_visited) {
		
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
