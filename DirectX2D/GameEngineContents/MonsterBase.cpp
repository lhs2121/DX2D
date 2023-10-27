#include "PreCompile.h"
#include "MonsterBase.h"


MonsterBase::MonsterBase()
{
}

MonsterBase::~MonsterBase()
{
}

void MonsterBase::Setting(std::string MonsterName)
{
	IdleAniName = MonsterName + "Idle";
	HitAniName = MonsterName + "Hit";
	DieAniName = MonsterName + "Die";

	Renderer->CreateAnimation(IdleAniName, IdleAniName, 0.2f);
	Renderer->CreateAnimation(HitAniName, HitAniName, 0.2f);
	Renderer->CreateAnimation(DieAniName, DieAniName, 0.3f);
	Renderer->ChangeAnimation(IdleAniName);
	Renderer->AutoSpriteSizeOn();

	ImageSize = Renderer->GetCurSprite().Texture->GetScale();
	Col->Transform.SetLocalScale(ImageSize);
	Col->Transform.AddLocalPosition({ 0,ImageSize.hY()});

	On();
}

void MonsterBase::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
	}
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
	}

	Off();
}

void MonsterBase::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
}

void MonsterBase::Release()
{
	
}


