#pragma once
#include "Scene.h"

class AssignmentScene : public Scene
{
public:
	AssignmentScene(std::string name);
	void Flower(int number);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update();
	int GetPokemonCompanion() { return m_Pokemon; }

private:
	int m_Pokemon = -1;
};