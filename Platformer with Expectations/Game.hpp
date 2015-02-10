#pragma once
#include <SFML\Graphics.hpp>

#include "TheGrid\NonCopyable.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"
#include "TheGrid\SystemManager.hpp"
#include "TheGrid\Analytics.hpp"

#include "Systems.hpp"
#include "EntityFactory.hpp"


class Game :
	public NonCopyable
{
public:
	Game();
	void run();

	~Game();

private:
	void initialize(sf::RenderTarget & target);
	void update(double dt);
	

	EntityManager entityManager;
	EventManager eventManager;
	SystemManager systemManager;
	Analytics * an = nullptr;
};
