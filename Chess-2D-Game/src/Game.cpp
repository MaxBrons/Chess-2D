#include "c2dpch.h"
#include "C2DCore.h"
#include "GameScene.h"

int main()
{
	using namespace C2DCore;

	std::unique_ptr<EventManager> eventManager = std::make_unique<EventManager>();
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->AddBehaviour(new C2DGame::GameScene("LEVEL 1"));
	app->Run();
	return 0;
}