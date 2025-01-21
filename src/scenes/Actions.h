#pragma once

#include <string>

enum ActionName
{
	UP = 0,
	DOWN = 1,
	ENTER = 2,
	SPACE = 3,
	CLICK = 4,
	HUD = 5
};

enum ActionType
{
	START = 0,
	END = 1,
};

class Action
{
	ActionName _name;
	ActionType _type;

public:
	Action() = default;
	Action(const ActionName& name, const ActionType& type) : _name(name), _type(type) {}

	const ActionName& getName() const { return _name; }
	const ActionType& getType() const { return _type; }
};