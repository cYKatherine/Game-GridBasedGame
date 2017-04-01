/*	FIT2049 - GridBaseGame
*	Game.cpp
*	Created by Katherine Chen based on Week4 base code
*/

#include "Game.h"
#include "TexturedShader.h"

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_unlitTexturedShader = NULL;
	m_unlitVertexColouredShader = NULL;
}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;
	m_meshManager = new MeshManager();
	m_textureManager = new TextureManager();
	m_currentCam = new Camera();

	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;

	InitGameWorld();

	return true;
}

bool Game::InitShaders()
{
	m_unlitVertexColouredShader = new Shader();
	if (!m_unlitVertexColouredShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
		return false;
	
	m_unlitTexturedShader = new TexturedShader();
	if (!m_unlitTexturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	return true;
}

bool Game::LoadMeshes()
{
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/floor_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/wall_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/player_capsule.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/progress_cube.obj"))
		return false;
	
	return true;
}

bool Game::LoadTextures()
{
	// TODO load checkerboard texture
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_orange.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_purple.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_disabled.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/checkerboard.jpg"))
		return false;
	
	return true;
}

void Game::InitGameWorld()
{
	const std::string COLOR_SET[7] = { "red", "green", "blue", "orange", "purple", "disabled", "white"};
	// Create some Tiles so we can see our grid
	for (int i = 0; i < 10; i++) {
		std::vector<Tiles*> tmp;
		for (int j = 0; j < 10; j++) {
			Tiles* tmpTile;
			// Get a random color for the tile
			int randNum = rand() % 13;

			if (randNum == 5) {
				tmpTile = new Tiles(
					m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"),
					i - 5,
					j - 4,
					true
				);
			}
			else {
				if (randNum > 6) randNum = 6;
				// Generate the texture file name for the specific color
				std::string fileName = "Assets/Textures/tile_" + COLOR_SET[randNum] + ".png";
				const char* file = fileName.c_str();

				tmpTile = new Tiles(
					m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture(file),
					i - 5,
					j - 4,
					COLOR_SET[randNum]
				);
			}
			tmp.push_back(tmpTile);
		}
		m_grid.push_back(tmp);
	}

	// Create some walls
	for (int i = -1; i < 11; i++) {
		std::vector<Tiles*> tmp;
		for (int j = -1; j < 11; j++) {
			if (i == -1 || i == 10 || j == -1 || j == 10) {
				Tiles* tmpTile = new Tiles(
					m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
					i - 5,
					j - 4,
					true
				);
				tmp.push_back(tmpTile);
			}
		}
		m_wall.push_back(tmp);
	}

	m_player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"), m_input, m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"));
}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();
	
	m_player->Update(m_grid);

	m_currentCam->Update(timestep);

	m_input->EndUpdate();
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// Render all tiles
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_grid[i][j]->Render(m_renderer, m_currentCam);
		}
	}

	// Render all walls
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < m_wall[i].size(); j++) {
			m_wall[i][j]->Render(m_renderer, m_currentCam);
		}
	}

	m_player->Render(m_renderer, m_currentCam);

	m_renderer->EndScene();		
}

void Game::Shutdown()
{
	// Delete all tiles
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			delete m_grid[i][j];
		}
	}

	// Delete all walls
	for (int i = 0; i <12; i++) {
		for (int j = 0; j < m_wall[i].size(); j++) {
			delete m_wall[i][j];
		}
	}

	delete m_player;

	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_unlitVertexColouredShader)
	{
		m_unlitVertexColouredShader->Release();
		delete m_unlitVertexColouredShader;
		m_unlitVertexColouredShader = NULL;
	}

	if (m_meshManager)
	{
		m_meshManager->Release();
		delete m_meshManager;
		m_meshManager = NULL;
	}

	if (m_textureManager)
	{
		m_textureManager->Release();
		delete m_textureManager;
		m_textureManager = NULL;
	}

}