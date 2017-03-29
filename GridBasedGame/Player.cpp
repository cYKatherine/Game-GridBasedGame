#include "Player.h"

Player::Player(Mesh* mesh, InputController* input, Shader* shader, Texture* texture) {
	m_mesh = mesh;
	m_input = input;
	m_shader = shader;
	m_texture = texture;

	m_position = Vector3::Zero;
	m_uniformScale = 1.0f;
	m_world = Matrix::Identity;
	m_health = 100;
}

void Player::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

bool insideWall(Vector3 current_position) {
	if (current_position.x >= 0 && current_position.x <= 100
		&& current_position.z >= 0 && current_position.z <= 100
		) return true;
	else return false;
}

void Player::Move() {
	if (m_input->GetKeyDown(VK_LEFT) && insideWall(m_position + Vector3(-1, 0, 0))) m_position += Vector3(-1, 0, 0);
	if (m_input->GetKeyDown(VK_RIGHT) && insideWall(m_position + Vector3(1, 0, 0))) m_position += Vector3(1, 0, 0);
	if (m_input->GetKeyDown(VK_UP) && insideWall(m_position + Vector3(0, 0, 1))) m_position += Vector3(0, 0, 1);
	if (m_input->GetKeyDown(VK_DOWN) && insideWall(m_position + Vector3(0, 0, -1))) m_position += Vector3(0, 0, -1);
}