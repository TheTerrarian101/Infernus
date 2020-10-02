#pragma once
#include "Utils.h"

class VModule {
public:
	std::string name, description;
	uint64_t key;
	bool isEnabled = false, wasEnabled = false;
	VModule(std::string name, std::string description, uint64_t key = NULL) { this->name = name, this->description = description; this->key = key; };

	/* Events */
	virtual void onLoop(); //For ticking each module and handling the onEnable & onDisable events
	virtual void onTick();
	virtual void onEnable();
	virtual void onDisable();

	virtual void onMouse(char, bool) {};
	virtual void onMouseMove() {};

	virtual void EnabledCall(VModule*) {};
	virtual void DisabledCall(VModule*) {};

	/* Events handled by hooks */
	virtual void onGmTick() {};
	virtual void onRender() {};
	virtual void onKey(uint64_t WinKey, bool isDown) {};

	virtual void onLerpMotion(Vec3* velocity) {};
	virtual void onJump(float*) {};
	virtual void onEntityTick(std::vector<class Actor*>*) {};
	virtual void onSpeed(float*) {};

	virtual void onDestroyBlock(class GameMode*, Vec3_i*, uint8_t) {};

	/* VWindow Stuff */
	virtual void onVButtonClick(class VWindowObj*) {};
};

class VHook {
public:
	virtual void Init() {};
};

/* Virtual Object Events */

class VCategory {
public:
	std::string name;
	std::vector<VModule*> modules;
	VCategory(std::string name) { this->name = name; };
};

#include "RenderUtils.h"
#include <functional>

class VWindowObj {
public:

	int objType = 0;
	Vec4 position; //Gets updated by VWindow

	/* Both */
	std::string text;
	float textAlpha;
	MC_Colour textColour;

	/* Button */
	float backgroundAlpha;
	MC_Colour backgroundColour;
	bool toggleState;
	bool hoveringOver = false;

	bool contains(float pX, float pY) {
		return position.x < pX && position.y < pY && position.z > pX && position.w > pY;
	};

	void updateCopyData() {
		this->textCopy = this->text;
		this->textAlphaCopy = textAlpha;
		this->backgroundAlphaCopy = backgroundAlpha;
		this->textColourCopy = textColourCopy;
		this->backgroundColourCopy = backgroundColour;
	};

	/* Mostly for event related stuff */

	std::string textCopy;
	float textAlphaCopy;
	float backgroundAlphaCopy;
	MC_Colour textColourCopy;
	MC_Colour backgroundColourCopy;

	void setButtonState(bool newState) {
		if (objType == 2) {
			toggleState = newState;
		};
		return;
	};

	void toggleButtonState() {
		if (objType == 2) {
			toggleState = !toggleState;
		};
		return;
	};
};

class VWindowText : public VWindowObj {
public:
	VWindowText(std::string text, MC_Colour colour = MC_Colour(255, 255, 255), float textAlpha = 1.0f) {
		this->text = text;
		this->textColour = colour;
		this->textAlpha = textAlpha;
		this->objType = 1; //Text
		this->updateCopyData();
	};
};

class VWindowButton : public VWindowObj {
public:
	VWindowButton(std::string text, MC_Colour textColour = MC_Colour(255, 255, 255), MC_Colour backgroundColour = MC_Colour(180, 180, 180), float textAlpha = 1.0f, float backgroundAlpha = 1.0f, bool toggle = false) {
		this->text = text;
		this->textAlpha = textAlpha;
		this->textColour = textColour;
		this->backgroundColour = backgroundColour;
		this->textAlpha = textAlpha;
		this->backgroundAlpha = backgroundAlpha;
		this->toggleState = toggle;
		this->objType = 2; //Button
		this->updateCopyData();
	};
};

class VWindow {
public:
	static std::vector<VWindow*> FetchWindows();

	std::string name;
	Vec4 position;
	Vec2 scale;
	MC_Colour backgroundColour;
	MC_Colour textColour;
	float backgroundTransparency;
	float textTransparency;
	bool isHidden;
	bool isBeingDragged = false;
	MC_Colour windowTitleBarColour;

	std::vector<VWindowObj*> WindowObjects;

	VWindow(std::string name, Vec4 position, MC_Colour backgroundColour = MC_Colour(120, 120, 120), MC_Colour textColour = MC_Colour(255, 255, 255), float backgroundAlpha = 1.0f, float textAlpha = 1.0f, bool isHidden = false) {
		this->name = name;
		this->position = position;
		this->scale = Vec2((position.z - position.x), (position.w - position.y));
		this->backgroundColour = backgroundColour;
		this->textColour = textColour;
		this->backgroundTransparency = backgroundAlpha;
		this->textTransparency = textAlpha;
		this->isHidden = isHidden;
		this->windowTitleBarColour = MC_Colour(120, 160, 255);
	};

	void setPosition(Vec2);
	void Render();
	void addObject(VWindowObj* object);
	bool withinWindowBar(float pX, float pY);
	bool hoveringOverTitleBar();
	static short getMouseX();
	static short getMouseY();
};