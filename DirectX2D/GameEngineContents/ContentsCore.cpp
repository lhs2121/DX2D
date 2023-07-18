#include "PreCompile.h"
#include "ContentsCore.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{

}

void ContentsCore::Update(float _Delta)
{
	HDC DC;
	{
		// ������ Ŭ����
		DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	}


	{
		// ��ü�μ��� ũ�� ȸ�� ��ġ
		static float4 Scale = {100, 100}; // ũ��
		static float4 Rotation = {0, 0, 0}; // ȸ��
		// ������ ���ð� ���尡 �ְ�
		// �� ���ð� ���� ������� �ڽ��� ��ġ�� �ؼ��Ҽ� �ִ�.
		static float4 Position = {100, 100}; // �̵�

		static float Dir = 1.0f;

		Scale -= float4(100.0f, 100.0f, 100.0f) * _Delta * Dir;

		if (100.0f <= abs(Scale.X))
		{
			Dir *= -1.0f;
		}


		Rotation.Z += 360.0f * _Delta;
		Position.X += 10.0f * _Delta;

		// ���ð� ������ �����Դϴ�.
		// �簢���� ����� ���ؼ� ���� 4�� ��������ϴ�.
		// �ٷ� ����� �ٷθ����
		// ������ �������� �ʴ´�.

		// ���û���
		std::vector<float4> Vertex;
		Vertex.resize(4);
		Vertex[0] = { -0.5f, -0.5f };
		Vertex[1] = { 0.5f, -0.5f };
		Vertex[2] = { 0.5f, 0.5f };
		Vertex[3] = { -0.5f, 0.5f };

		// std::vector<std::vector<int>> Index;

		std::vector<POINT> WinPoint;
		WinPoint.resize(4);
		for (size_t i = 0; i < Vertex.size(); i++)
		{
			// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
			float4 WorldPoint = Vertex[i];

			// ��ġ ũ�� ȸ���� �����ų�� ���������� �����
			// �������� ������ �ֽ��ϴ�.
			// ũ�� ȸ�� ��ġ ������� ������Ѿ� �մϴ�.

			WorldPoint *= Scale;
			WorldPoint = WorldPoint.GetRotationToDegZ(Rotation.Z);
			WorldPoint += Position;
			WinPoint[i] = WorldPoint.WindowPOINT();
		}
		Polygon(DC, &WinPoint[0], static_cast<int>(Vertex.size()));

		GameEngineCore::MainWindow.DoubleBuffering();
	}
}

void ContentsCore::Release()
{

}