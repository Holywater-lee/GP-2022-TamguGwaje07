#define WIDTH (600)
#define HEIGHT (400)

#include "Game.h"
#include "InputHandler.h"

#include "Walker.h"

Game* Game::s_pInstance = 0;

bool Game::setup()
{
	bool result;

	result = init("Nature of Code", 100, 100, WIDTH, HEIGHT, false);

	_walker = new Walker(WIDTH / 4, HEIGHT / 4);

	for (int i = 0; i < WIDTH; i += 10)
	{
		walls.push_back(Vector2D(i, 0));
		walls.push_back(Vector2D(i, HEIGHT));
	}
	for (int i = 0; i < HEIGHT; i += 10)
	{
		walls.push_back(Vector2D(0, i));
		walls.push_back(Vector2D(WIDTH, i));
	}

	return result;
}

void Game::update()
{
	target = *InputHandler::Instance()->getMousePosition();

	_walker->seek(target);
	for (auto w : walls)
	{
		if (_walker->NearWall(w))
			_walker->seek(w);
	}
	_walker->update();
	_walker->edges();
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

	filledCircleRGBA(m_pRenderer, target.getX(), target.getY(), 32, 255, 0, 0, 150);
	aacircleRGBA(m_pRenderer, target.getX(), target.getY(), 32, 255, 0, 0, 255);

	for (auto w : walls)
	{
		aacircleRGBA(m_pRenderer, w.getX(), w.getY(), 4, 255, 0, 0, 255);
	}

	_walker->draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	delete _walker;

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	m_pWindow = NULL;
	m_pRenderer = NULL;

	SDL_Quit();
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);

	if (m_pWindow != NULL)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pRenderer);
	}
	else
	{
		return false;
	}

	m_bRunning = true;

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

	return true;
}

bool Game::running()
{
	return m_bRunning;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}