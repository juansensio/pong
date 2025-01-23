#include "ScenePlay.h"
#include "../GameEngine.h"

ScenePlay::ScenePlay(GameEngine& game_engine) 
	: Scene(game_engine)
	, _player(nullptr)
	, _enemy(nullptr)
	, _ball(nullptr)
	, _walls({nullptr, nullptr})
	, _goal(nullptr)
	, _death(nullptr) {}

ScenePlay::~ScenePlay() {}

void ScenePlay::init()
{
	_entity_manager = EntityManager();

	_levelManager = LevelManager();
	_levelManager.init();

	//game objects
	_player = Player(_entity_manager.addEntity(EntityType::PLAYER));  
	_ball = Ball(_entity_manager.addEntity(EntityType::BALL));  
	_enemy = Enemy(_entity_manager.addEntity(EntityType::ENEMY));  
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
	registerAction(MOUSE_LEFT_BUTTON, ActionName::CLICK);

	fpsBuffer.resize(100);

}

// cuando quiero cambiar de escena, no puede pasar nada después (si no me peta el juego)
void ScenePlay::update(const float& dt)
{
	if (!_paused) {
		_player.update(dt);
		_ball.update(dt);
		_enemy.update(dt);
		movement(dt);
		collisions();
		_entity_manager.update(); 

		// si no lo pongo al final me peta el juego
		if (_player.getLives() <= 0) {
			_game_engine.changeScene<SceneMenu>(SceneType::MENU);
		}

		if (_player.getScore() >= _levelManager.getLevel().getGoalsForNextLevel()) {
			if (_levelManager.getCurrentLevel() >= _levelManager.getNumLevels() - 1) {
				_game_engine.changeScene<SceneMenu>(SceneType::MENU);
			} else {
				_shop.init();
				_paused = true;
				_levelManager.loadNextLevel();
			}
		}
	}
	
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

	const char* livesText = TextFormat("Lives: %d", _player.getLives());
	const char* levelText = TextFormat("Level: %d", _levelManager.getCurrentLevel()); 
	const char* scoreText = TextFormat("Score: %d", _player.getScore());

	int livesWidth = MeasureText(livesText, 20);
	int levelWidth = MeasureText(levelText, 20);
	int scoreWidth = MeasureText(scoreText, 20);
	
	int totalWidth = livesWidth + levelWidth + scoreWidth + 40; // 40 for spacing between texts
	int startX = GetScreenWidth()/2 - totalWidth/2;
	
	DrawText(livesText, startX, 30, 20, WHITE);
	DrawText(levelText, startX + livesWidth + 20, 30, 20, WHITE);
	DrawText(scoreText, startX + livesWidth + levelWidth + 40, 30, 20, WHITE);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 10);  // Set consistent text size
	if (GuiButton(Rectangle{(float)GetScreenWidth() - 60, 30, 50, 25}, "MENU")) {
		_game_engine.changeScene<SceneMenu>(SceneType::MENU);
	}

	if(_shop.isActive()) {
		_shop.render();
	}

	renderGUI();
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
		else if (action.getName() == ActionName::CLICK) {
			if (_shop.isActive()) {
				_shop.click(GetMousePosition());
			}
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
			restart();
		}
	}
}

void ScenePlay::restart() {
	_ball.init();
}

void ScenePlay::renderGUI()
{
	#ifdef _DEBUG
		char fps_text[10];
		ImGui::Begin("Pong");
		if (ImGui::BeginTabBar("TabBar"))
		{
			if (ImGui::BeginTabItem("Game"))
			{
				float enemySpeed = _enemy.getSpeed();
				if (ImGui::SliderFloat("Enemy speed", &enemySpeed, 10.f, 200.f)) _enemy.setSpeed(enemySpeed);
				float playerSpeed = _player.getSpeed();
				if (ImGui::SliderFloat("Player speed", &playerSpeed, 10.f, 200.f)) _player.setSpeed(playerSpeed);
				float ballSpeed = _ball.getSpeed();
				if (ImGui::SliderFloat("Ball speed", &ballSpeed, 10.f, 200.f)) _ball.setSpeed(ballSpeed);
				if (ImGui::Button("Toggle AI")) _player.getEntity().get<CAI>().exists = !_player.getEntity().get<CAI>().exists;
				if (ImGui::Button("Restart Game")) restart();
				if (ImGui::Button("Next Level")) _levelManager.loadNextLevel();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Debug"))
			{
				fpsBuffer.erase(fpsBuffer.begin());
				float current_fps = GetFPS();
				fpsBuffer.push_back(current_fps);
				sprintf(fps_text, "%.1f", current_fps);
				ImGui::PlotLines("FPS", &fpsBuffer[0], fpsBuffer.size(), 0, fps_text, 0.0f, 120.0f, ImVec2(0, 80));
				ImGui::Text("Entities (%d):", _entity_manager.getEntities().size());
				for (auto e : _entity_manager.getEntities())
				{
					ImGui::Text("Entity %d: (%.1f, %.1f)", e->id(), e->get<CTransform>().position.x, e->get<CTransform>().position.y);
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	#endif
}

