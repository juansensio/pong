#pragma once

#include "Scene.h"
#include "SceneLoading.h"
#include "SceneMenu.h"
#include "ScenePlay.h"
#include "SceneCredits.h"
#include "SceneResults.h"

enum SceneType {
	LOADING = 0,
	MENU = 1,
	PLAY = 2,
	CREDITS = 3,
	RESULTS = 4
};