#include "PreCompile.h"
#include "Monster.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
}


void Monster::Start()
{
	GameEngineRandom NewRandom;
	float4 Scale = NewRandom.RandomVectorBox2D(10, 100, 10, 100);

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(30);


		NewRandom.SetSeed(reinterpret_cast<long long>(this));

		Renderer->SetSprite("HoHoYee_AttackABC2");
		Renderer->Transform.SetLocalScale(Scale);
	}

	{
		std::shared_ptr<GameEngineCollision> Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		// Col->Transform.SetLocalScale(Scale);
	}
}
