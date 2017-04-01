#include "Player.h"

Player::Player(Mesh* mesh, InputController* input, Shader* shader, Texture* texture) {
	m_mesh = mesh;
	m_input = input;
	m_shader = shader;
	m_texture = texture;


	m_position = Vector3(rand() % 10 - 5, 0, rand() % 10 - 4);
	m_health = 100;
	m_uniformScale = (double)m_health / 100.00;
	m_world = Matrix::Identity;
}

void Player::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Player::Update(std::vector<std::vector<Tiles*>> m_grid) {
	if (m_input->GetKeyDown(VK_LEFT) && insideWall(m_position + Vector3(-1, 0, 0), m_grid)) m_position += Vector3(-1, 0, 0);
	if (m_input->GetKeyDown(VK_RIGHT) && insideWall(m_position + Vector3(1, 0, 0), m_grid)) m_position += Vector3(1, 0, 0);
	if (m_input->GetKeyDown(VK_UP) && insideWall(m_position + Vector3(0, 0, 1), m_grid)) m_position += Vector3(0, 0, 1);
	if (m_input->GetKeyDown(VK_DOWN) && insideWall(m_position + Vector3(0, 0, -1), m_grid)) m_position += Vector3(0, 0, -1);

	std::string color = m_grid[m_position.x + 5][m_position.z + 4]->getColor();
	m_grid[m_position.x + 5][m_position.z + 4]->Update();

	m_uniformScale = (double)m_health / 100.00;
	m_world = Matrix::CreateScale(Vector3(m_uniformScale, m_uniformScale, m_uniformScale)) * Matrix::CreateTranslation(m_position);
}

bool Player::insideWall(Vector3 currentPosition, std::vector<std::vector<Tiles*>> m_grid) {
	if ((currentPosition.x >= -5 && currentPosition.x <= 4
		&& currentPosition.z >= -4 && currentPosition.z <= 5
		) && !(m_grid[currentPosition.x + 5][currentPosition.z + 4]->getVisited())) return true;
	else return false;
}
