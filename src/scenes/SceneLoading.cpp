#include "SceneLoading.h"
#include "../GameEngine.h"

void SceneLoading::init()
{
	_elapsedTime = 0.0f;
	// TODO: asset manager en GameEngine
	_texture = LoadTexture("assets/janus.png");
}

void SceneLoading::update(const float& elapsed)
{
	_elapsedTime += GetFrameTime();
	if (_elapsedTime >= 3.0f) {
		_game_engine.changeScene<SceneMenu>("menu");
	}
}

void SceneLoading::render()
{
	// Calculate progress (0 to 1) for the first 2 seconds
	float progress = _elapsedTime / 2.0f;
	if (progress > 1.0f) progress = 1.0f;  // Clamp at 1.0 to hold final state
	
	// Cubic ease-in-out function
	float eased;
	if (progress < 0.5f) {
		// First half: ease in (accelerate)
		eased = 4 * progress * progress * progress;
	} else {
		// Second half: ease out (decelerate)
		float p = progress - 1;
		eased = 1 + (4 * p * p * p);
	}
	
	// Calculate scale (0.1 to 0.5)
	float scale = 0.1f + (0.2f * eased);
	
	// Calculate position based on current scale
	Vector2 position = {
		GetScreenWidth() / 2.0f - (_texture.width * scale) / 2.0f,
		GetScreenHeight() / 2.0f - (_texture.height * scale) / 2.0f
	};
	
	// Apply the same easing to opacity
	unsigned char alpha = static_cast<unsigned char>(eased * 255);
	Color tint = { 255, 255, 255, alpha };
	
	DrawTextureEx(
		_texture,
		position,
		0.0f,
		scale,
		tint
	);
}