#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string name)
 :Scene(name)
{

}

int HelloWorld::GetPokemonCompanion() {
	return m_Pokemon; 
}
int HelloWorld::GetLegendaryBird() {
	return m_LegendaryBird;
}
void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);
	float aspectRatio = windowWidth / windowHeight;

	//Sets up Main Camera
	{

		//creates Camera entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();

		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Sets the offset and the cam
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(5.f);

		unsigned int bitHolder = EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Horizontal Scrolling Cam");
		ECS::SetIsMainCamera(entity, true);

	}

	//Creates Background Entity
	{

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components 
		std::string filename = "Background.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -5.f));

		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Background");

	}

	//Creates Ho-Oh Entity
	{

		auto entity = ECS::CreateEntity();
		m_LegendaryBird = entity;

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components 
		std::string filename = "HO-OH.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 22, 18);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(59.f, 25.f, -1.f));

		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HO-OH");

	}

	//Creates Player Entity
	{

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components 
		std::string filename = "Player.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);
		//Adds first animation
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);

		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(337.f, 60.f), vec2(361.f, 37.f));
		anim.AddFrame(vec2(372.f, 60.f), vec2(396.f, 37.f));
		anim.AddFrame(vec2(407.f, 60.f), vec2(431.f, 37.f));

		anim.SetRepeating(true);

		anim.SetSecPerFrame(0.1667f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 20, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(38.f, -54.f, 0.f));

		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Player");
		ECS::SetIsMainPlayer(entity, true);
	}

	//Creates Pokemon Entity
	{

		auto Pokemon = File::LoadJSON("Pokemon.json");

		auto entity = ECS::CreateEntity();
		m_Pokemon = entity;

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components 
		std::string filename = "Luxray.png";
		std::string filename2 = "Roserade.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		//animController.InitUVs(filename);
		animController.InitUVs(filename);
		//Adds first animation
		animController.AddAnimation(Pokemon["LuxrayLeft"]);
		animController.AddAnimation(Pokemon["RoseradeLeft"]);
		//Sets active animation
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 18, 20, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(60.f, -55.f, 1.f));

		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Pokemon");
	}

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

//Code to make the HealthBar work

				/*{
					auto entity = ECS::CreateEntity();
					ECS::AttachComponent<HealthBar>(entity);
					ECS::GetComponent<HealthBar>(entity).SetHealth(.7f);
					unsigned int bitHolder = EntityIdentifier::healthBarBit();
					ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
				}*/


//Previous Code in HelloWorld Cpp

				/*
				m_sceneReg = new entt::registry;
				ECS::AttachRegister(m_sceneReg);
				float aspectRatio = windowWidth / windowHeight;

				//Setup new Entity
				{
					//Creates entity
					auto entity = ECS::CreateEntity();

					//Add components 
					ECS::AttachComponent<Sprite>(entity);
					ECS::AttachComponent<Transform>(entity);
					//ECS::AttachComponent<AnimationController>(entity);

					//Sets up components 
					std::string filename = "HelloWorld.png";

					ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 50, 25);
					ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -25.f, 100.f));

					//Sets up the Identifier 
					unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
					ECS::SetUpIdentifier(entity, bitHolder, "Hello World Sign");

					EntityIdentifier::MainCamera(entity);


					ECS::AttachComponent<Camera>(entity);
					vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
					ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
					ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
					unsigned int bitHolder2 = EntityIdentifier::CameraBit();
					ECS::SetUpIdentifier(entity, bitHolder2, "Main Camera");
					ECS::SetIsMainCamera(entity, true);

				*/
