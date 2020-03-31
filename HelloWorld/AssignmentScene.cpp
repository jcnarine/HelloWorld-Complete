#include "AssignmentScene.h"

AssignmentScene::AssignmentScene(std::string name)
	:Scene(name)
{

}
void AssignmentScene::Flower(int number) {
	{

		auto Flower = File::LoadJSON("Flower.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components 
		std::string filename = "Flowers.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		//animController.InitUVs(filename);
		animController.InitUVs(filename);
		//Adds first animation
		animController.AddAnimation(Flower["Flower"]);
		//Sets active animation
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 21, 30, true, &animController);
		switch (number) {
		case(0):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(84.f, 226.f, 0.f));
			break;
		case(1):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(105.f, 226.f, 0.f));
			break;
		case(2):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(126.f, 226.f, 0.f));
			break;
		case(3):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(147.f, 226.f, 0.f));
			break;
		case(4):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-145.f, 226.f, 0.f));
			break;
		case(5):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-124.f, 226.f, 0.f));
			break;
		case(6):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-103.f, 226.f, 0.f));
			break;
		case(7):
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-82.f, 226.f, 0.f));
			break;
		}
		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Flower8");
	}
}
void AssignmentScene::InitScene(float windowWidth, float windowHeight)
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
			ECS::AttachComponent<VerticalScroll>(entity);

			vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();

			ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));

			ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

			//Sets the offset and the cam
			ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
			ECS::GetComponent<HorizontalScroll>(entity).SetOffset(5.f);

			ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
			ECS::GetComponent<VerticalScroll>(entity).SetOffset(5.f);

			unsigned int bitHolder = EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
			ECS::SetUpIdentifier(entity, bitHolder, "Horizontal Scrolling Cam");

			unsigned int bitHolder2 = EntityIdentifier::VertScrollCameraBit() | EntityIdentifier::CameraBit();
			ECS::SetUpIdentifier(entity, bitHolder2, "Vertical Scrolling Cam");

			ECS::SetIsMainCamera(entity, true);

		}

		{

		auto Player = File::LoadJSON("Blueberry.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components 
		std::string filename = "BlueberryWalk.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(filename);
		//Adds first animation
		animController.AddAnimation(Player["WalkRight"]); //index 0
		animController.AddAnimation(Player["WalkLeft"]);
		//Sets active animation
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 60, 50, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(100.f, -6.f, 99.f));

		//Sets up the Identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blueberry");
}

		//Creates Background Entity
		{

			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components 
			std::string filename = "Twinleaf.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 512, 512);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -5.f));

			//Sets up the Identifier 
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "Background");

		}

		//Creates Player Entity
		{
			auto Player = File::LoadJSON("Player.json");

			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			//Sets up components 
			std::string filename = "Player.png";
			
			auto& animController = ECS::GetComponent<AnimationController>(entity);

			animController.InitUVs(filename);
			//Adds first animation
			animController.AddAnimation(Player["WalkDown"]); //index 0
			animController.AddAnimation(Player["WalkUp"]); //index 1
			animController.AddAnimation(Player["WalkLeft"]); //index 2
			animController.AddAnimation(Player["WalkRight"]); //index 3
			//Sets active animation
			animController.SetActiveAnim(0);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 25, true, &animController);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(71.f, -6.f, 99.f));

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
			animController.AddAnimation(Pokemon["LuxrayRight"]);
			animController.AddAnimation(Pokemon["RoseradeLeft"]);
			//Sets active animation
			animController.SetActiveAnim(0);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 39, 20, true, &animController);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-48.f, -32.f, 1.f));
			//Sets up the Identifier 
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(entity, bitHolder, "Pokemon");
		}

		for (int i = 0; i < 8; i++) {
			Flower(i);
		}
		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));		
	}
	