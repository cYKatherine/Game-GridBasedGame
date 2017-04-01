#include "Tiles.h"

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;
	
	m_color = color;
	if (color == "diabled") m_visited = true;
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

std::string Tiles::getColor() {
	return m_color;
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

void Tiles::Update() {
	m_visited = true;
}
