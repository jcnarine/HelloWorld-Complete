#include "Game.h"

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	///m_name = "Hello World";
	m_name = "Assignment Scene";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	m_scenes.push_back(new AssignmentScene("Challenge Two"));
	
	//Sets active scene reference to our scene
	m_activeScene = m_scenes[0];

    m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
	Game::PokemonUpdate();
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}
void Game::PokemonUpdate() {

	AssignmentScene* scene = (AssignmentScene*)m_activeScene;

	auto& change = m_register->get<Transform>(scene->GetPokemonCompanion());
	auto& sprite = m_register->get<AnimationController>(scene->GetPokemonCompanion());

	if (change.GetPositionX() <= -118) {;
		movement = .1;
		sprite.SetActiveAnim(1);
	}
	if (change.GetPositionX() >= -35) {
		movement = -.1;
		sprite.SetActiveAnim(0);
	}
	change.SetPositionX((change.GetPositionX()) + movement);
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//Gamepad button stroked (pressed)
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i)) {
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			//If the controller is connected, we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController * con)
{
	//Gamepad button stroke (press)
	if (con->IsButtonStroked(Buttons::A)) {
		printf("A Stroked\n");
	}
	
}

void Game::GamepadUp(XInputController * con)
{
	//Gamepad button up
	if (con->IsButtonReleased(Buttons::RB)) {
		printf("RB Release\n");
	}
}

void Game::GamepadDown(XInputController * con)
{
	//Gamepad button down
	if (con->IsButtonPressed(Buttons::THUMB_LEFT)) {
		printf("Left Thumbstick Clicked in\n");
	}
}

void Game::GamepadStick(XInputController * con)
{
	//Gamepad stick stuffs
	Stick sticks[2];
	con->GetSticks(sticks);

	if (sticks[0].x < -0.1f) {
		printf("Left Pointing\n");
	}
	if (sticks[0].x > 0.1f) {
		printf("Right Pointing\n");
	}
	if (sticks[0].y < -0.1f) {
		printf("Down Pointing\n");
	}
	if (sticks[0].y > 0.1f) {
		printf("Up Pointing\n");
	}

	//system("cls");
}

void Game::GamepadTrigger(XInputController * con)
{
	Triggers triggers;
	con->GetTriggers(triggers);

	
	if (triggers.RT > 0.5f && triggers.RT < 0.8f) {
		printf("Half Press\n");
	}
	if (triggers.RT > 0.8f) {
		printf("Full Press\n");
	}
	
}



void Game::KeyboardHold()
{

	auto& change = m_register->get<AnimationController>(EntityIdentifier::MainPlayer());

	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	
	vec2 totalForce = vec2(0.f, 0.f);
	
	//Keyboard button held
	if (Input::GetKey(Key::F3)) {

	}
	if (Input::GetKey(Key::F4)) {
		printf("F4 key is Held\n");
	}

	if (Input::GetKey(Key::DownArrow)) {
		totalForce.y = -15.f;
		change.SetActiveAnim(0);
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y - (speed * Timer::deltaTime));
	}

	if (Input::GetKey(Key::UpArrow)) {
		totalForce.y = 15.f;
		change.SetActiveAnim(1);
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y + (speed*Timer::deltaTime));
	}

	if (Input::GetKey(Key::LeftArrow)) {
		totalForce.x = -15.f;
		change.SetActiveAnim(2);
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x - (speed * Timer::deltaTime));
	}

	if (Input::GetKey(Key::RightArrow)) {
		totalForce.x = 15.f;
		change.SetActiveAnim(3);
		//m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x + (speed * Timer::deltaTime));
	}

	vec2 acceleration = totalForce / m_mass;

	if (!(m_velocity.GetMagnitude() > 10.f)) {
	
		m_velocity = m_velocity + (acceleration * Timer::deltaTime);
	
	}

	position = position + (vec3(m_velocity.x, m_velocity.y, 0.f) * Timer::deltaTime) + (vec3(acceleration.x, acceleration.y, 0.f) * (0.5f)*(Timer::deltaTime*Timer::deltaTime));
	m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPosition(position);

	if (m_velocity.x < -20.f) {
		m_velocity.x = -19.8f;
	}
	else if (m_velocity.x > 20.f) {
		m_velocity.x = 19.8f;
	}
	else {
		m_velocity.x = m_velocity.x + (acceleration.x * Timer::deltaTime);
	}

	if (m_velocity.y < -20.f) {
		m_velocity.y = -19.8f;
	}
	else if (m_velocity.y > 20.f) {
		m_velocity.y = 19.8f;
	}
	else {
		m_velocity.y = m_velocity.y + (acceleration.y * Timer::deltaTime);
	}
}

void Game::KeyboardDown()
{


	if (Input::GetKeyDown(Key::Space)) {

	}
	//Keyboard button down
	if (Input::GetKeyDown(Key::F2)) {

	}
	if (Input::GetKeyDown(Key::F4)) {
		printf("F4 key is Down\n");
	}
}

void Game::KeyboardUp()
{

	if (Input::GetKeyUp(Key::Space)) {

	}
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::F4)) {
		printf("F4 key is Released\n");
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	printf("Mouse Moved(%f,%f)\n", float(evnt.x), float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_LEFT)) {
		printf("Left Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		printf("Right Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		printf("Middle Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("Mouse Scroll %f\n", float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
