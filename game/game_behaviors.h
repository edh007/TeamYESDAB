#pragma once

#include "GentleIdiots.h"

class BehaviorController : public gi::Behavior
{
public:
	BehaviorController(gi::Entity* pOwner);
	virtual ~BehaviorController() override;

	virtual void Run(float dt) override;

private:
};