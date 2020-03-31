#pragma once
#include "Scene.h"
class HelloWorld : public Scene
{
public:
	HelloWorld(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	int GetPokemonCompanion();
	int GetLegendaryBird();
private:
	int m_Pokemon = -1;
	int m_LegendaryBird = -1;
};