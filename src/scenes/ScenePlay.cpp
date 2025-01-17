#include "ScenePlay.h"
#include "../GameEngine.h"

#include <iostream>

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	_player.init();
	
	_wall = Wall(_entity_manager.addEntity(EntityType::WALL));
	_wall.init();

}

void ScenePlay::update(const float& dt)
{
	_entity_manager.update();
	_player.update(dt);
	// Colisión
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	float playerX = _player.position().x;
	float playerY = _player.position().y;
	float wallX = _wall.position().x;
	float wallY = _wall.position().y;
	float wallWidth = _wall.getEntity()->get<CRectShape>().width;
	float wallHeight = _wall.getEntity()->get<CRectShape>().height;
	float playerRadius = _player.getEntity()->get<CCircleShape>().radius;
	if (playerX >= wallX - wallWidth && playerX <= wallX - wallWidth + 10 &&
		playerY + playerRadius >= wallY - wallHeight/2 && playerY - playerRadius <= wallY + wallHeight/2) {
		_player.destroy();
	}
}

void ScenePlay::render()
{
	for (auto& entity : _entity_manager.getEntities()) {
		Vector2 position = entity->get<CTransform>().position;
		if (entity->has<CCircleShape>()) {
			CCircleShape circle = entity->get<CCircleShape>();
			DrawCircle(position.x, position.y, circle.radius, circle.color);
		}
		if (entity->has<CRectShape>()) {
			CRectShape rect = entity->get<CRectShape>();
			DrawRectangle(position.x - rect.width/2, position.y - rect.height/2, rect.width, rect.height, rect.color);
		}
	}

	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>("menu");
	}

	// DEBUG
	DrawText(TextFormat("Entities: %d", _entity_manager.getEntities().size()), 10, 30, 20, RED);
}