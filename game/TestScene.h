#pragma once

#include "GentleIdiots.h"

class TestScene : public gi::Scene
{
public:
	TestScene();
	virtual ~TestScene() override;

	virtual void Load() override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Shutdown() override;
	virtual void Unload() override;

private:

};