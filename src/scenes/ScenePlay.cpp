#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine) 
	: Scene(game_engine)
	, _player(nullptr)
	, _enemy(nullptr, _ball)
	, _ball(nullptr, _player)
	, _walls({nullptr, nullptr})
	, _goal(nullptr)
	, _death(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	// game objects
	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	_ball = Ball(_entity_manager.addEntity(EntityType::BALL), _player);
	_enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY), _ball);
	_walls = {
		Wall(_entity_manager.addEntity(EntityType::WALL)),
		Wall(_entity_manager.addEntity(EntityType::WALL)),
	};
	_goal = Goal(_entity_manager.addEntity(EntityType::GOAL));
	_death = Death(_entity_manager.addEntity(EntityType::DEATH));

	// init game objects
	_player.init();
	_enemy.init();
	_ball.init();
	_walls[0].init(10);
	_walls[1].init(GetScreenHeight() - 10);
	_goal.init();
	_death.init();

	// register actions
	registerAction(KEY_UP, ActionName::UP);
	registerAction(KEY_DOWN, ActionName::DOWN);
	registerAction(KEY_SPACE, ActionName::SPACE);
	registerAction(KEY_ENTER, ActionName::ENTER);
}

void ScenePlay::update(const float& dt)
{
	_player.update(dt);
	if (_player.getLives() <= 0) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}
	_ball.update(dt);
	_enemy.update(dt);
	movement(dt);
	collisions();
	_entity_manager.update(); 
}

void ScenePlay::movement(const float& dt)
{
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CAI>()) {
			Vector2 velocity = Vector2Subtract(
				_ball.getEntity().get<CTransform>().position, 
				entity->get<CTransform>().position
			);
			velocity.x = 0;
			velocity = Vector2Normalize(velocity);
			velocity = Vector2Scale(velocity, entity->get<CAI>().speed);
			entity->get<CTransform>().velocity = velocity;
		}
		if (entity->has<CTransform>()) {
			auto& transform = entity->get<CTransform>();
			transform.prevPosition = transform.position;
			transform.position += transform.velocity * dt;
		}
	}

}

void ScenePlay::collisions() {
	// ball vs walls / paddles
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>() && entity->id() != _ball.getEntity().id()) {
			auto overlaps = Physics::BoundingBoxOverlap(_ball.getEntity(), *entity);
			if (overlaps.overlap.x > 0 && overlaps.overlap.y > 0) {
				_ball.collision(entity, overlaps.prevOverlap);
			}
		}
	}
	// paddles vs walls
	for (auto& entity : _entity_manager.getEntities(EntityType::WALL)) {
		// player
		auto overlaps = Physics::BoundingBoxOverlap(_player.getEntity(), *entity);
		if (overlaps.overlap.x > 0 && overlaps.overlap.y > 0) {
			_player.collision(*entity);
		}
		// enemy
		overlaps = Physics::BoundingBoxOverlap(_enemy.getEntity(), *entity);
		if (overlaps.overlap.x > 0 && overlaps.overlap.y > 0) {
			_enemy.collision(*entity);
		}
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

	DrawText(TextFormat("Lives: %d", _player.getLives()), GetScreenWidth()/2 - 50, 20, 20, WHITE);
	DrawText(TextFormat("Score: %d", _player.getScore()), GetScreenWidth()/2 - 50, 40, 20, WHITE);

	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 10, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}
}

void ScenePlay::doAction(const Action& action)
{
	if (action.getType() == ActionType::START) {
		if (action.getName() == ActionName::UP) {
			_player.moveUp();
		}
		else if (action.getName() == ActionName::DOWN) {
			_player.moveDown();
		}
		else if (action.getName() == ActionName::ENTER) {
			_game_engine.changeScene<SceneMenu>(SceneType::MENU);
		}
	}
	else if (action.getType() == ActionType::END) {
		if (action.getName() == ActionName::UP) {
			_player.stopUp();
		}
		else if (action.getName() == ActionName::DOWN) {
			_player.stopDown();
		}
		else if (action.getName() == ActionName::SPACE) {
			_ball.init();
		}
	}
}
