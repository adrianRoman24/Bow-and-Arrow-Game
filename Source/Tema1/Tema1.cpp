#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "MyObject2D.h"

#define NUM_SECONDS 1

using namespace std;

int my_time = 0;
double time_counter = 0;

int my_time_shoot = 0;
double time_counter_shoot = 0;
bool shooted = false;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// set values for objects' coordinates
	// map data
	xLimit = (float)window->GetResolution().x;
	yLimit = (float)window->GetResolution().y;
	marginsWidth = 10 * yLimit / xLimit;
	xLimit -= marginsWidth;
	yLimit -= marginsWidth;
	xOrigin = marginsWidth;
	yOrigin = marginsWidth;

	// bow data
	float bowRadius = yLimit / 22;
	float bowFactor = xLimit / yLimit;
	float bowX = xLimit / 20;
	float bowY = yLimit / 2;
	moveBowFactor = yLimit * 0.8f;
	float bowAngle = 0;

	// arrow data
	float arrowLength = xLimit / 20;
	float arrowHeight = yLimit / 200;
	float arrowX = bowX;
	float arrowY = bowY;
	float arrowPeak = xLimit / 50;
	arrowSpeed = shurikenSpeed = xLimit / 3.0f;
	float arrowAngle = 0;
	resetArrow = true;

	// baloon data
	baloonRadius = xLimit / 40;
	baloonFactor = 1.5f;
	baloonSpeed = yLimit / 3.6f;

	// shuriken and sharingan data
	shurikenCathetus = xLimit / 40;
	shurikenSpeed = xLimit / 6.4f;
	distructionFactor = 1.0f;
	rotateFactor = 0.4f;
	shurikensToSpawn = 5;
	
	// helper data
	lastMouseX = arrowX;
	lastMouseY = arrowY;
	arrowPressed = false;
	arrowPressed = false;
	thisTime = clock();
	lastTime = thisTime;

	// power scale data
	powerFactor = arrowSpeed / 50;
	powerBarLimit = 50;
	powerBarLength = xLimit / 30;
	powerBarX = bowX;
	powerBarY = bowY - xLimit / 10;

	// gameplay data
	lives = 3;
	score = 0;
	cout << "LEVEL 1" << endl;
	cout << "Score: " << score << endl;
	cout << "Lives: " << lives << endl;
	sharinganRadius = xLimit / 30;
	level = 1;
	levelUp = false;

	// create meshes
	// origin = left down
	powerBar = new PowerBar("power_bar", arrowSpeed, arrowSpeed / 50,
		0, xLimit / 20, powerBarX, powerBarY);
	Mesh *powerBarMesh = MyObject2D::CreatePowerBar("power_bar", powerBarLength, glm::vec3(0.7f, 0, 0.9f));
	AddMeshToList(powerBarMesh);

	// origin = left down / 2 line coordinates
	arrow = new Arrow("arrow", 0, 0, arrowAngle, arrowLength, arrowHeight, arrowPeak, arrowX, arrowY);
	Mesh *arrowMesh = MyObject2D::CreateArrow("arrow", arrowLength, arrowHeight, arrowPeak, glm::vec3(0, 1, 0));
	AddMeshToList(arrowMesh);

	// origin = semi circle coordinates
	bow = new Bow("bow", bowAngle, bowRadius, bowFactor, bowX, bowY);
	Mesh *bowMesh = MyObject2D::CreateBow("bow", bowRadius, bowFactor, glm::vec3(0, 1, 0));
	AddMeshToList(bowMesh);

	// origin = shuriken center
	Mesh *shurikenMesh = MyObject2D::CreateShuriken("shuriken", shurikenCathetus, glm::vec3(0, 0, 1));
	AddMeshToList(shurikenMesh);

	// origin = baloon center coordinates
	// red
	Mesh *redBaloonMesh = MyObject2D::CreateBaloon("baloon_red", baloonRadius, baloonFactor, glm::vec3(1, 0, 0));
	AddMeshToList(redBaloonMesh);
	// yellow
	Mesh *yellowBaloonMesh = MyObject2D::CreateBaloon("baloon_yellow", baloonRadius, baloonFactor, glm::vec3(1, 1, 0));
	AddMeshToList(yellowBaloonMesh);

	Mesh* margins = MyObject2D::CreateMargins("margins", marginsWidth, xLimit + marginsWidth, yLimit + marginsWidth,
		glm::vec3(0.7f, 0, 0.9f));
	AddMeshToList(margins);
	
	// origin = centre 
	Mesh *sharinganMesh = MyObject2D::CreateSharingan("sharingan", sharinganRadius);
	AddMeshToList(sharinganMesh);

	// white baloon poly line
	Mesh *baloonLine = MyObject2D::CreateBaloonLine("baloon_line", baloonRadius);
	AddMeshToList(baloonLine);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.1f, 0.2f, 0.1f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::LevelUp() {
	baloonSpeed *= 2;
	shurikenSpeed *= 2;
	shurikensToSpawn = 9;
}

void Tema1::DrawArrow() {
	modelMatrix = Transform2D::Rotate(arrow->angle);
	modelMatrix = Transform2D::Translate(arrow->x, arrow->y) * modelMatrix;
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawBow() {
	modelMatrix = Transform2D::Rotate(bow->angle) * modelMatrix;
	modelMatrix = Transform2D::Translate(bow->x, bow->y) * modelMatrix;
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	modelMatrix = modelMatrix * Transform2D::Translate(-bow->x, -bow->y);
}

void Tema1::DrawBaloons() {
	for (auto it = baloons.begin(); it != baloons.end(); ++it) {
		modelMatrix = glm::mat3(1);
		if ((*it)->hit) {
			modelMatrix = Transform2D::Scale((*it)->distructionFactor, (*it)->distructionFactor);
		}
		modelMatrix = Transform2D::Translate((*it)->x, (*it)->y) * modelMatrix;
		if ((*it)->color.compare("red") == 0) {
			RenderMesh2D(meshes["baloon_red"], shaders["VertexColor"], modelMatrix);
		}
		else {
			RenderMesh2D(meshes["baloon_yellow"], shaders["VertexColor"], modelMatrix);
		}
		modelMatrix = Transform2D::Translate(0, -baloonRadius * baloonFactor) * modelMatrix;
		RenderMesh2D(meshes["baloon_line"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::DrawShurikens() {
	for (auto it = shurikens.begin(); it != shurikens.end(); ++it) {
		modelMatrix = glm::mat3(1);
		if ((*it)->hit) {
			modelMatrix = Transform2D::Scale((*it)->distructionFactor, (*it)->distructionFactor);
		}
		modelMatrix = Transform2D::Rotate(rotateFactor) * modelMatrix;
		modelMatrix = Transform2D::Translate((*it)->x, (*it)->y) *modelMatrix;
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::DrawSharingans() {
	for (auto it = sharingans.begin(); it != sharingans.end(); ++it) {
		modelMatrix = glm::mat3(1);
		if ((*it)->hit) {
			modelMatrix = Transform2D::Scale((*it)->distructionFactor, (*it)->distructionFactor);
		}
		modelMatrix = Transform2D::Rotate(rotateFactor) * modelMatrix;
		modelMatrix = Transform2D::Translate((*it)->x, (*it)->y) *modelMatrix;
		RenderMesh2D(meshes["sharingan"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::DrawShootedArrows() {
	for (auto it = shootedArrows.begin(); it != shootedArrows.end(); ++it) {
		modelMatrix = Transform2D::Rotate((*it)->angle);
		modelMatrix = Transform2D::Translate((*it)->x, (*it)->y) * modelMatrix;
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::DrawPowerBar() {
	modelMatrix = Transform2D::Scale(2 * powerBar->speed / powerBar->limit + 0.05f, 1);
	modelMatrix = Transform2D::Translate(powerBar->x, powerBar->y) * modelMatrix;
	RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
}

void Tema1::UpdateBaloons(float deltaTimeSeconds) {
	auto it = baloons.begin();
	while(it != baloons.end()) {
		if ((*it)->y - (*it)->radius * (*it)->scaleFactor > yLimit ||
			(*it)->distructionFactor < 0.001f) {
			baloons.erase(it++);
		} else {
			++it;
		}
	}
	for (it = baloons.begin(); it != baloons.end(); ++it) {
		(*it)->y += baloonSpeed * deltaTimeSeconds;
		if (!(*it)->hit) {
			for (auto arr = shootedArrows.begin(); arr != shootedArrows.end(); ++arr) {
				if ((*it)->Collision(*arr)) {
					(*it)->hit = true;
					if ((*it)->color == "red") {
						score += 5;
					}
					else {
						score -= 3;
						if (score < 0) {
							score = 0;
						}
					}
					cout << "Score: " << score << endl;
					break;
				}
			}
		}
		else {
			(*it)->distructionFactor *= 0.9f;
		}
	}
}

void Tema1::UpdateShurikens(float deltaTimeSeconds) {
	auto it = shurikens.begin();
	while (it != shurikens.end()) {
		if ((*it)->x + (*it)->cathetus < xOrigin ||
			(*it)->distructionFactor < 0.001f) {
			shurikens.erase(it++);
		} else {
			++it;
		}
	}
	for (auto it = shurikens.begin(); it != shurikens.end(); ++it) {
		(*it)->x -= shurikenSpeed * deltaTimeSeconds;
		if (level == 2) {
			(*it)->y += (*it)->speedOy * deltaTimeSeconds;
		}
		if (!(*it)->hit) {
			for (auto arr = shootedArrows.begin(); arr != shootedArrows.end(); ++arr) {
				if ((*it)->Collision(*arr)) {
					(*it)->hit = true;
					score += 1;
					cout << "Score: " << score << endl;
					break;
				}
			}
			if (bow->Collision(*it) && !(*it)->bowCollision) {
				(*it)->bowCollision = true;
				lives--;
				cout << "Lives: " << lives << endl;
				if (lives == 0) {
					cout << "Game over!" << endl;
				}
			}
		} else {
			(*it)->distructionFactor *= 0.9f;
		}
	}
}

void Tema1::UpdateSharingans(float deltaTimeSeconds) {
	auto it = sharingans.begin();
	while (it != sharingans.end()) {
		if ((*it)->x + (*it)->radius < xOrigin ||
			(*it)->distructionFactor < 0.001f) {
			sharingans.erase(it++);
		}
		else {
			++it;
		}
	}
	for (auto it = sharingans.begin(); it != sharingans.end(); ++it) {
		(*it)->x -= shurikenSpeed * deltaTimeSeconds;
		if (level == 2) {
			(*it)->y += (*it)->speedOy * deltaTimeSeconds;
		}
		if (!(*it)->hit) {
			for (auto arr = shootedArrows.begin(); arr != shootedArrows.end(); ++arr) {
				if ((*it)->Collision(*arr)) {
					(*it)->hit = true;
					score += 1;
					cout << "Score: " << score << endl;
					(*it)->distructionFactor = 20;
					break;
				}
			}
			if (bow->Collision(*it) && !(*it)->bowCollision) {
				(*it)->bowCollision = true;
				lives--;
				cout << "Lives: " << lives << endl;
			}
		}
		else {
			(*it)->distructionFactor *= 0.9f;
		}
	}
}

void Tema1::UpdateShootedArrows(float deltaTimeSeconds) {
	auto it = shootedArrows.begin();
	while (it != shootedArrows.end()) {
		Arrow *arr = *it;
		if (arr->y - arr->height / 2 > yLimit || arr->y + arr->height / 2 < yOrigin || arr->x > xLimit) {
			shootedArrows.erase(it++);
		} else {
			++it;
			arr->Update(deltaTimeSeconds);
		}
	}
}

void Tema1::GenerateBaloons(int nrBaloons) {
	float xLim1 = xLimit - xLimit / 2.5f;
	float xLim2 = xLimit;
	float step = (xLim2 - xLim1) / (float)nrBaloons;
	for(float i = 0; i < nrBaloons; i++) {
		float x1 = xLim1 + step * i + baloonRadius;
		float x2 = xLim1 + step * (i + 1) - baloonRadius;
		float x = x1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (x2 - x1)));
		if (rand() % 2 == 0) {
			baloons.push_back(new Baloon("baloon", "red", baloonRadius, baloonFactor, x, yOrigin - baloonRadius,
				distructionFactor));
		} else {
			baloons.push_back(new Baloon("baloon", "yellow", baloonRadius, baloonFactor, x, yOrigin - baloonRadius,
				distructionFactor));
		}
	}
}

void Tema1::GenerateShurikens(int nrShurikens) {
	float yLim1 = xOrigin;
	float yLim2 = yLimit;
	float step = (yLim2 - yLim1) / (float)nrShurikens;
	for (float i = 0; i < nrShurikens; i++) {
		float y1 = yLim1 + step * i + shurikenCathetus * (float)sqrt(2);
		float y2 = yLim1 + step * (i + 1) - shurikenCathetus * (float)sqrt(2);
		float y = y1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (y2 - y1)));
		float sign = 1.0f;
		if (rand() % 2 == 0) {
			sign *= -1;
		}
		if (level == 2) {
			if (rand() % 2 == 0)
				shurikens.push_back(new Shuriken("shuriken", shurikenCathetus, xLimit + shurikenCathetus, y,
					distructionFactor, shurikenSpeed * sign / 3));
			else
				sharingans.push_back(new Sharingan("sharingan", sharinganRadius, xLimit + sharinganRadius, y,
					distructionFactor, shurikenSpeed * sign / 3));
		}
		else {
			shurikens.push_back(new Shuriken("shuriken", shurikenCathetus, xLimit + shurikenCathetus, y,
				distructionFactor, shurikenSpeed * sign / 3));
		}
	}
}

void Tema1::Update(float deltaTimeSeconds)
{
	// check if game is over
	if (lives == 0) {
		// draw last frame
		// draw margins
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["margins"], shaders["VertexColor"], modelMatrix);
		// draw bow
		DrawBow();
		// draw arrow
		if (resetArrow) {
			DrawArrow();
		}
		// draw shooted arrows
		DrawShootedArrows();
		// draw baloons
		DrawBaloons();
		// draw shurikens
		DrawShurikens();
		// draw sharingans
		DrawSharingans();
		// draw power bar
		DrawPowerBar();
		// draw power bar
		DrawPowerBar();
		return;
	}
	// update arrow and bow rotation angle
	float x = max((float)lastMouseX - (arrow->x), 0.0f);
	float y = (float)lastMouseY - arrow->y;
	if (mousePressed || arrowPressed) {
		arrow->angle = atan(y / x);
	}
	x = max((float)lastMouseX - (bow->x), 0.0f);
	y = (float)lastMouseY - (bow->y + arrow->height / 2);
	if (mousePressed || arrowPressed) {
		bow->angle = atan(y / x);
	}
	// draw margins
	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["margins"], shaders["VertexColor"], modelMatrix);

	// draw bow
	DrawBow();

	// draw arrow
	if (resetArrow) {
		DrawArrow();
	}

	// draw shooted arrows
	DrawShootedArrows();

	// draw baloons
	DrawBaloons();

	// draw shurikens
	DrawShurikens();

	// draw sharingans
	DrawSharingans();

	// draw power bar
	DrawPowerBar();

	// make updates
	// update power bar
	if (updatePowerBar && resetArrow) {
		if (powerBar->speed < powerBar->limit) {
			powerBar->speed += powerBar->factor;
		}
	} else {
		powerBar->speed = 0;
	}

	// update shooted arrows
	UpdateShootedArrows(deltaTimeSeconds);
	// update shuriken rotation factor
	rotateFactor -= 5 * deltaTimeSeconds;
	// update baloons
	UpdateBaloons(deltaTimeSeconds);
	// update shurikens
	UpdateShurikens(deltaTimeSeconds);
	// update shurikens
	UpdateSharingans(deltaTimeSeconds);
	// update buttons
	arrowPressed = false;
	mousePressed = false;
	// update time
	thisTime = clock();
	time_counter += (double)(thisTime - lastTime);
	lastTime = thisTime;
	if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
	{
		time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
		my_time++;
		// generate baloons
		GenerateBaloons(rand() % 4);

		// generate shurikens (and sharingans)
		GenerateShurikens(rand() % shurikensToSpawn);
	}
	// update shooting time
	if (shooted) {
		time_counter_shoot += (double)(shootTime - lastShootTime);
		lastShootTime = shootTime;
		shootTime = clock();

		if (time_counter_shoot > (double)(1 * NUM_SECONDS * CLOCKS_PER_SEC))
		{
			time_counter_shoot -= (double)(1 * NUM_SECONDS * CLOCKS_PER_SEC);
			my_time_shoot = 0;
			shooted = false;
			resetArrow = true;
		}
	}
	// update everything if resolution changes
	if ((int)(xLimit + xOrigin) != (int)window->GetResolution().x ||
		(int)(yLimit + yOrigin) != (int)window->GetResolution().y) {
		int lastLevel = level;
		Init();
		level = lastLevel;
		if (level == 2) {
			cout << "LEVEL 2" << endl;
			LevelUp();
			levelUp = true;
			level++;
			shurikensToSpawn = 10;
		}
	}

	// update level
	if (!levelUp) {
		if (score >= 20) {
			cout << "LEVEL 2" << endl;
			LevelUp();
			levelUp = true;
			level++;
			shurikensToSpawn = 10;
		}
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// aici folosesc window->keyhold
	// update arrow, bow and power bar coordinates
	if (lives == 0) {
		return;
	}
	if (window->KeyHold(GLFW_KEY_W)) {
		arrowPressed = true;
		if (bow->y < yLimit) {
			bow->y += moveBowFactor * deltaTime;
		}
		else {
			bow->y = yLimit;
		}
		powerBar->y = bow->y;
		arrow->y = bow->y;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		arrowPressed = true;
		if (bow->y > yOrigin) {
			bow->y -= moveBowFactor * deltaTime;
		}
		else {
			bow->y = yOrigin;
		}
		arrow->y = bow->y;
	}
	powerBar->y = bow->y - xLimit / 10;
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (lives == 0) {
		return;
	}
	mousePressed = true;
	lastMouseX = mouseX - marginsWidth;
	lastMouseY = yLimit - mouseY + marginsWidth;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	// activate power bar
	if (lives == 0) {
		return;
	}
	updatePowerBar = true;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	// update arrow, mouse coordinates and add shooting arrows
	if (lives == 0) {
		return;
	}
	if (resetArrow) {
		resetArrow = false;
		lastMouseX = mouseX - marginsWidth;
		lastMouseY = yLimit - mouseY + marginsWidth;
		// calculate speed on axis OX and OY
		// d = v * t; d^2 = dx^2 + dy^2; dx = vx * t; dy = vy * t
		xDistance = lastMouseX - arrow->x;
		yDistance = lastMouseY - arrow->y;
		float time = (float)sqrt(xDistance * xDistance + yDistance * yDistance) / (powerBar->speed + arrowSpeed);
		float speedX = xDistance / time;
		float speedY = yDistance / time;
		shootedArrows.push_back(new Arrow("arrow", speedX, speedY, arrow->angle,
			xLimit / 20, yLimit / 200, xLimit / 50, arrow->x, arrow->y));
	}
	// update time
	if (!shooted) {
		resetArrow = false;
		shooted = true;
		shootTime = clock();
		lastShootTime = shootTime;
	}
	// deactivate power bar
	updatePowerBar = false;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
