#pragma once
#include "../../Other/VComponent.h"

class Uninject : public VModule {
public:
	Uninject() : VModule::VModule("Uninject", "Removes the Client from the Game") {};
	void onEnable();
};