#include "PreCompile.h"
#include "DamageActor.h"


DamageActor::DamageActor()
{
}

DamageActor::~DamageActor()
{
}

void DamageActor::Start()
{
	Col = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerSkill);
	Col->SetCollisionType(ColType::AABBBOX2D);
	Off();
}

void DamageActor::Hit()
{
	Off();
}


