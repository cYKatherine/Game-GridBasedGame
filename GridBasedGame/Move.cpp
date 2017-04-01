#include "Move.h"

Move::Move(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) {
	m_mesh = mesh;
	m_shader = shader;
	m_texture = texture;

	m_position = position;
	moveLeft = 10;
	m_uniformScale = (double)moveLeft / 50.00;
	m_world = Matrix::Identity;
}

void Move::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Move::Update() {
	m_uniformScale = (double)moveLeft / 50.00;
	m_world = Matrix::CreateScale(Vector3(m_uniformScale, m_uniformScale, m_uniformScale)) * Matrix::CreateTranslation(m_position);
}

void Move::updateMoveLeft(int move) {
	moveLeft += move;
}

void Move::updatePosition(Vector3 position) {
	m_position = position;
}

int Move::getMoveLeft() {
	return moveLeft;
}