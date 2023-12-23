#include "PreCompile.h"
#include "UI_BuffIcon.h"
#include "StatData.h"
#include "StatManager.h"

UI_BuffIcon::UI_BuffIcon()
{
}

UI_BuffIcon::~UI_BuffIcon()
{
}

void UI_BuffIcon::Setting(SkillType _Type)
{
	std::string SpriteName;
	switch (_Type)
	{
	case SkillType::SurekenBooster:
		SpriteName = "BoosterIcon.png";
		break;
	case SkillType::Haste:
		SpriteName = "HasteIcon.png";
		break;
	default:
		break;
	}
	Renderer->SetSprite(SpriteName);
}

void UI_BuffIcon::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->AutoSpriteSizeOn();
	Off();
}

void UI_BuffIcon::Update(float _Delta)
{
	CoolTime -= _Delta;
	if (CoolTime <= 0)
	{
		Off();
	}
}
