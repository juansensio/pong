#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine) 
	: Scene(game_engine)
	, _player(nullptr)
	, _enemy(nullptr)
	, _ball(nullptr, _player)
	, _walls({nullptr, nullptr})
	, _goal(nullptr)
	, _death(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));
	_enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY));
	_ball = Ball(_entity_manager.addEntity(EntityType::BALL), _player);
	_walls = {
		Wall(_entity_manager.addEntity(EntityType::WALL)),
		Wall(_entity_manager.addEntity(EntityType::WALL)),
	};
	_goal = Goal(_entity_manager.addEntity(EntityType::GOAL));
	_death = Death(_entity_manager.addEntity(EntityType::DEATH));

	_player.init();
	_enemy.init();
	_ball.init();
	_walls[0].init(10);
	_walls[1].init(GetScreenHeight() - 10);
	_goal.init();
	_death.init();

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
	movement(dt);
	collisions();
	_entity_manager.update(); 
}

void ScenePlay::movement(const float& dt)
{
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CTransform>()) {
			auto& transform = entity->get<CTransform>();
			transform.prevPosition = transform.position;
			transform.position += transform.velocity * dt;
		}
	}
}

void ScenePlay::collisions() {
	CBoundingBox bb = _ball.getEntity().get<CBoundingBox>();
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>() && entity->id() != _ball.getEntity().id()) {
			CBoundingBox bb2 = entity->get<CBoundingBox>();
			auto position1 = _ball.getEntity().get<CTransform>().position;
			auto position2 = entity->get<CTransform>().position;
			// detect collision
			Vector2 delta = {
				abs(position1.x - position2.x),
				abs(position1.y - position2.y)
			};
			Vector2 overlap = {
				bb.halfSize.x + bb2.halfSize.x - abs(delta.x),
				bb.halfSize.y + bb2.halfSize.y - abs(delta.y)
			};
			if (overlap.x > 0 && overlap.y > 0) {
				// resolve collision
				auto prevPos1 = _ball.getEntity().get<CTransform>().prevPosition;
				auto prevPos2 = entity->get<CTransform>().prevPosition;
				Vector2 prevDelta = {
					abs(prevPos1.x - prevPos2.x),
					abs(prevPos1.y - prevPos2.y)
				};
				Vector2 prevOverlap = {
					bb.halfSize.x + bb2.halfSize.x - abs(prevDelta.x),
					bb.halfSize.y + bb2.halfSize.y - abs(prevDelta.y)
				};
				if (prevOverlap.y > 0 && prevOverlap.x <= 0) { // side collision
					if (prevPos1.x < prevPos2.x) {
						_ball.getEntity().get<CTransform>().position.x -= overlap.x;
					} else {
						_ball.getEntity().get<CTransform>().position.x += overlap.x;
					}
				} else if (prevOverlap.x > 0 && prevOverlap.y <= 0) { // top/bottom collision
					if (prevPos1.y < prevPos2.y) { // bottom collision
						_ball.getEntity().get<CTransform>().position.y -= overlap.y;
					} else { // top collision
						_ball.getEntity().get<CTransform>().position.y += overlap.y;
					}
				} else { // diagonal collision
					// move ball to the side since will always be a paddle
					if (prevPos1.x < prevPos2.x) { 
						_ball.getEntity().get<CTransform>().position.x -= overlap.x;
					} else {
						_ball.getEntity().get<CTransform>().position.x += overlap.x;
					}
				}
				_ball.collision(entity, prevOverlap);
			}
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

	// DEBUG: render bounding boxes
	for (auto& entity : _entity_manager.getEntities()) {
		if (entity->has<CBoundingBox>()) {
			auto position = entity->get<CTransform>().position;
			CBoundingBox bb = entity->get<CBoundingBox>();
			DrawRectangleLines(position.x - bb.halfSize.x, position.y - bb.halfSize.y, bb.size.x, bb.size.y, RED);
		}
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
