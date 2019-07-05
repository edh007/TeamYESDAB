#include "Player.h"


Player::Player() :Entity(nullptr, "Player")
{
	
}

Player::~Player()
{
	
}


void Player::Init()
{
	auto& componentContainer = GetComponentContainer();

	componentContainer.AddComponent(gi::ComponentTransform::CreateComponentTransform(this), gi::ComponentTransform::COMPONENT_ID);
	//componentContainer.AddComponent()

}