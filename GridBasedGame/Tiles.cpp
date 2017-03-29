#include "Tiles.h"

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, std::string color) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;
	
	m_color = color;
	m_visited = false;
}

Tiles::Tiles(Mesh* mesh, Shader* shader, Texture* texture, float positionX, float positionZ, bool visited) {
	m_mesh = mesh;
	m_position = Vector3(positionX, 0, positionZ);
	m_texture = texture;
	m_shader = shader;

	m_color = "";
	m_visited = visited;
}

void Tiles::setTexture() {
	const char* fileName = ("Assets/Textures/tile_%c.png", m_color).c_str();
	std::cout << fileName << "\n";
	TextureManager* m_textureManager = new TextureManager;
	m_texture = m_textureManager->GetTexture("Assets/Textures/tile_blue.png");
}

void Tiles::Render(Direct3D* renderer, Camera* cam) {
	if (m_mesh) {
		m_world = Matrix::CreateScale(1.0f, 1.0f, 1.0f) * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}
