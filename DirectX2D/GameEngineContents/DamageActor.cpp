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
	Col->Transform.SetLocalScale({ 50, 50 });
	Col->SetCollisionType(ColType::AABBBOX2D);
}

void DamageActor::Hit()
{
	Off();
}


