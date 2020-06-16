#pragma once
#include "Resourse_Managers/Resourses.h"
#include "UI/Button.h"

class Signal
{
public:

	struct ButtonSignal 
	{
		Button::ID id;
	};

	enum SignalType
	{
		ButtonClicked
	};

	SignalType type;
	union
	{
		ButtonSignal button;
	};
};