#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <list> 
#include <iterator>

#include "Arrow.h"
#include "Bow.h"
#include "Shuriken.h"
#include "Baloon.h"
#include "PowerBar.h"
#include "Sharingan.h"
#include <time.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();
	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	// draw functions
	void DrawBaloons();
	void DrawShurikens();
	void DrawArrow();
	void DrawBow();
	void DrawShootedArrows();
	void DrawPowerBar();
	void DrawSharingans();
	// update functions
	void UpdateBaloons(float deltaTimeSeconds);
	void UpdateShurikens(float deltaTimeSeconds);
	void UpdateShootedArrows(float deltaTimeSeconds);
	void UpdateSharingans(float deltaTimeSeconds);
	// generate functions
	void GenerateBaloons(int nrBaloons);
	void GenerateShurikens(int nrShurikens);

	void LevelUp();

protected:
	glm::mat3 modelMatrix;
	float xLimit, yLimit, xOrigin, yOrigin, marginsWidth;
	float moveBowFactor, rotateFactor, lastMouseX, lastMouseY, distructionFactor;
	float baloonSpeed, baloonRadius, baloonFactor;
	float shurikenSpeed, shurikenCathetus;
	int shurikensToSpawn;
	bool resetArrow, mousePressed, arrowPressed;
	float arrowSpeed, xDistance, yDistance;
	float powerFactor;
	float powerBarLimit, powerBarX, powerBarY, powerBarLength;
	float lives;
	bool updatePowerBar;
	int score;
	float sharinganRadius;
	Arrow *arrow;
	Bow *bow;
	PowerBar *powerBar;
	std::list<Shuriken *> shurikens;
	std::list<Baloon *> baloons;
	std::list<Arrow *> shootedArrows;
	std::list<Sharingan *> sharingans;
	clock_t thisTime, lastTime, shootTime, lastShootTime;
	int level;
	float levelUp;
};
