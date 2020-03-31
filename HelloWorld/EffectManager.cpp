#include "EffectManager.h"

Selectable EffectManager::m_selectable = Selectable("Effect Editor");


int EffectManager::m_numEffects = 0;
bool EffectManager::m_effectsInit = false;

int EffectManager::m_greyscale = -1;
int EffectManager::m_sepia = -1;
int EffectManager::m_vignette = -1;
int EffectManager::m_grain = -1;
int EffectManager::m_pixelate = -1;
int EffectManager::m_selectiveColor = -1;
int EffectManager::m_bloom = -1;

PostEffect* EffectManager::m_basicEffect;
std::vector<PostEffect*> EffectManager::m_effects;
PostEffect* EffectManager::m_compoundEffect;

EffectManager::~EffectManager()
{
	//If the buffer isn't nullptr
	if (m_basicEffect != nullptr)
	{
		//Unload it
		m_basicEffect->Unload();
		//delete the allocation
		delete m_basicEffect;
		//set it to nullptr
		m_basicEffect = nullptr;
	}

	if (m_compoundEffect != nullptr)
	{
		//Unload it
		m_compoundEffect->Unload();
		//delete the allocation
		delete m_compoundEffect;
		//Set it to nullptr
		m_compoundEffect = nullptr;
	}

	for (int i = 0; i < m_effects.size(); i++)
	{
		//If the buffer isn't nullptr
		if (m_effects[i] != nullptr)
		{
			//Unload it
			m_effects[i]->Unload();
			//Delete the allocation
			delete m_effects[i];
			//Set it to nullptr
			m_effects[i] = nullptr;
		}
	}
}
void EffectManager::CreateTab() {

	bool temp = false;

	if (ImGui::BeginTabItem(m_selectable.GetName().c_str(), m_selectable.GetSelected())) {
	
		temp=true;

		ImGui::EndTabItem();

	}

	if (temp)
		CreateEditor();
}

void EffectManager::CreateEditor() {

	if (m_selectable.GetSelected()) {
	
	
		if (ImGui::TreeNode("Sepia Effect")) {
		
			if (m_sepia != -1) {
			
				SepiaEffect* temp = (SepiaEffect*)EffectManager::GetEffect(m_sepia);
				float intensity = temp->GetIntensity();

				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Intensity", &intensity, 0.01f, 0.f, 1.f)) {
				
					temp->SetIntensity(intensity);
				
				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_sepia);

				}

			
			}
			else {
			
				ImGui::Text("None attached");
			
				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {
				
					EffectManager::CreateEffect(Sepia, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

				
				}
			
			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Greyscale Effect")) {

			if (m_greyscale != -1) {

				GreyscaleEffect* temp = (GreyscaleEffect*)EffectManager::GetEffect(m_greyscale);
				float intensity = temp->GetIntensity();

				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Intensity", &intensity, 0.01f, 0.f, 1.f)) {

					temp->SetIntensity(intensity);

				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_greyscale);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(Greyscale, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Vignette Effect")) {

			if (m_vignette != -1) {

				VignetteEffect* temp = (VignetteEffect*)EffectManager::GetEffect(m_vignette);
				float InnerRadius = temp->GetInnerRadius();
				float OuterRadius = temp->GetOuterRadius();
				float Opacity = temp->GetOpacity();

				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Inner Radius", &InnerRadius, 0.01f, 0.f, 1.f)) {

					temp->SetInnerRadius(InnerRadius);

				}

				if (ImGui::DragFloat("Outer Radius", &OuterRadius, 0.01f, 0.f, 1.f)) {

					temp->SetOuterRadius(OuterRadius);

				}

				if (ImGui::DragFloat("Opacity", &Opacity, 0.01f, 0.f, 1.f)) {

					temp->SetOpacity(Opacity);

				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_vignette);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(Vignette, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Noise Effect")) {

			if (m_grain != -1) {

				GrainEffect* temp = (GrainEffect*)EffectManager::GetEffect(m_grain);
				float Strength = temp->GetStrength();

				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Strength", &Strength, 2.f, 0.f, 100.f)) {

					temp->SetStrength(Strength);

				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_grain);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(Grain, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Pixelation Effect")) {

			if (m_pixelate != -1) {

				PixelateEffect* temp = (PixelateEffect*)EffectManager::GetEffect(m_pixelate);
				float PixelSize = temp->GetPixelSize();

				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Pixel Size", &PixelSize, 0.1f, 0.f, 16.f)) {

					temp->SetPixelSize(PixelSize);

				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_pixelate);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(Pixelate, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Bloom Effect")) {

			if (m_bloom != -1) {

				BloomEffect* temp = (BloomEffect*)EffectManager::GetEffect(m_bloom);
				float Passes = (float)temp->GetPasses();
				float Threshold = (float)temp->GetThreshold();


				ImGui::Text("Currently Attached");

				if (ImGui::DragFloat("Passes", &Passes, 0.1f, 0.f, 1.f)) {

					temp->SetPasses(Passes);

				}

				if (ImGui::DragFloat("Threshold", &Threshold, 0.1f, 0.f, 1.f)) {

					temp->SetPasses(Threshold);

				}


				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_bloom);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(Bloom, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}

		if (ImGui::TreeNode("Selective Color Effect")) {

			if (m_selectiveColor != -1) {

				SelectiveColorEffect* temp = (SelectiveColorEffect*)EffectManager::GetEffect(m_selectiveColor);
				float colorRange1[] = { temp->GetColorRange1().x, temp->GetColorRange1().y, temp->GetColorRange1().z };
				float colorRange2[] = { temp->GetColorRange2().x, temp->GetColorRange2().y, temp->GetColorRange2().z };


				ImGui::Text("Currently Attached");

				if (ImGui::SliderFloat3("Color Range 1", &colorRange1[0], 0.f, 1.f)) {

					temp->SetColorRange1(vec3(colorRange1[0], colorRange1[1], colorRange1[2]));

				}

				if (ImGui::SliderFloat3("Color Range 2", &colorRange2[0], 0.f, 1.f)) {

					temp->SetColorRange2(vec3(colorRange2[0], colorRange2[1], colorRange2[2]));

				}

				if (ImGui::Button("Remove Effect", ImVec2(100.f, 20.f))) {

					EffectManager::RemoveEffect(m_selectiveColor);

				}


			}
			else {

				ImGui::Text("None attached");

				if (ImGui::Button("Add Effect", ImVec2(100.f, 20.f))) {

					EffectManager::CreateEffect(SelectiveColor, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());


				}

			}
			ImGui::TreePop();

		}
	}

}

void EffectManager::InitEffectManager(unsigned width, unsigned height)
{
	//Init hte fullscreen quad
	Framebuffer::InitFullscreenQuad();

	//if the buffer init is false
		//We intialize the basic buffer
	if (!m_effectsInit)
	{
		m_basicEffect = new PostEffect();
		//Initialize the buffer with the above targets
		m_basicEffect->Init(width, height);

		m_compoundEffect = new PostEffect();
		//Initialize the buffer with the above targets
		m_compoundEffect->Init(width, height);

		m_effectsInit = true;
	}

}

int EffectManager::CreateEffect(EffectType type, unsigned width, unsigned height)
{
	//Grabs the index before you create the new framebuffer (which means this is essentially equal to
	//"m_buffers.size() - 1", which is just the last created buffer
	int index = int(m_effects.size());

	switch (type)
	{
	case Sepia:
		if (m_sepia == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new SepiaEffect());
			m_effects[index]->Init(width, height);
			m_sepia = index;
		}
		else
		{
			printf("Already has a sepia effect");
		}
		break;
	case Greyscale:
		if (m_greyscale == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new GreyscaleEffect());
			m_effects[index]->Init(width, height);
			m_greyscale = index;
		}
		else
		{
			printf("Already has a greyscale effect");
		}
		break;
	case Vignette:
		if (m_vignette == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new VignetteEffect());
			m_effects[index]->Init(width, height);
			m_vignette = index;
		}
		else
		{
			printf("Already has a Vignette effect");
		}
		break;
	case Grain:
		if (m_grain == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new GrainEffect());
			m_effects[index]->Init(width, height);
			m_grain = index;
		}
		break;
	case Pixelate:
		if (m_pixelate == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new PixelateEffect());
			m_effects[index]->Init(width, height);
			m_pixelate = index;
		}
		else
		{
			printf("Already has a Pixelate effect");
		}
		break;
	case SelectiveColor:
		if (m_selectiveColor == -1)
		{
			//The same as basic buffer
			m_effects.push_back(new SelectiveColorEffect());
			m_effects[index]->Init(width, height);
			m_selectiveColor = index;
		}
		else
		{
			printf("Already has a Selective Color effect");
		}
		break;
	case Bloom:
		if (m_bloom == -1)
		{
			m_effects.push_back(new BloomEffect());
			m_effects[index]->Init(width, height);
			m_bloom = index;
		}
		else
		{
			printf("Already has a bloom effect");
		}
		break;
	default:
		//The same as basic buffer
		m_effects.push_back(new PostEffect());
		m_effects[index]->Init(width, height);
		break;
	}

	//increase number of buffers
	m_numEffects++;

	return index;
}

PostEffect * EffectManager::GetEffect(int index)
{
	//returns the pointer to the buffer at that index
	return m_effects[index];
}

void EffectManager::AdjustIndices(int indexToRemove)
{
	if (m_sepia > indexToRemove)
		m_sepia--;
	else if (m_sepia == indexToRemove)
		m_sepia = -1;

	if (m_greyscale > indexToRemove)
		m_greyscale--;
	else if (m_greyscale == indexToRemove)
		m_greyscale= -1;

	if (m_vignette > indexToRemove)
		m_vignette--;
	else if (m_vignette == indexToRemove)
		m_vignette = -1;

	if (m_grain > indexToRemove)
		m_grain--;
	else if (m_grain == indexToRemove)
		m_grain= -1;

	if (m_pixelate > indexToRemove)
		m_pixelate--;
	else if (m_pixelate == indexToRemove)
		m_pixelate = -1;

	if (m_selectiveColor > indexToRemove)
		m_selectiveColor--;
	else if (m_selectiveColor == indexToRemove)
		m_selectiveColor = -1;

	if (m_bloom > indexToRemove)
		m_bloom--;
	else if (m_bloom == indexToRemove)
		m_bloom = -1;
}

void EffectManager::RemoveEffect(int index)
{
	//Delete the variable if it isn't = to nullptr and then set it to nullptr
	if (m_effects[index] != nullptr)
	{
		m_effects[index]->Unload();
		delete m_effects[index];
		m_effects[index] = nullptr;
	}

	//Adjusts the other indices to make sure that things don't give errors
	AdjustIndices(index);

	//Erases the now deleted buffer at that index
	m_effects.erase(m_effects.begin()+index);

	//Reduce number of buffers
	m_numEffects--;
}

void EffectManager::ClearBuffers()
{
	m_basicEffect->Clear();


	for (int i = 0; i < m_effects.size(); i++)
	{
		m_effects[i]->Clear();
	}

	m_compoundEffect->Clear();
}

void EffectManager::DrawEffects()
{
	PostEffect* previousBuffer = m_basicEffect;
	for (int i = 0; i < m_effects.size(); i++)
	{
		//applies effect
		m_effects[i]->ApplyEffect(previousBuffer);

		//Binds the current buffer as the previous buffer and loops again 
		//(unless it was the last iteration, then it draws the "previous buffer" to the backbuffer)
		previousBuffer = m_effects[i];
	}
	
	//draws the last buffer in the loop to the compound buffer
	m_compoundEffect->ApplyEffect(previousBuffer);

	//Draws the compound buffer to the screen
	DrawCompoundEffect();
}

void EffectManager::ReshapeBuffers(unsigned width, unsigned height)
{
	//Reshape the basic buffer
	if (m_basicEffect != nullptr)
		m_basicEffect->Reshape(width, height);

	if (m_compoundEffect != nullptr)
		m_compoundEffect->Reshape(width, height);

	//loop through all the buffers
	for (int i = 0; i < m_effects.size(); i++)
	{
		//reshape em
		m_effects[i]->Reshape(width, height);
	}
}

void EffectManager::BindColorTex(int textureSlot)
{
	m_compoundEffect->BindColorAsTexture(0, 0, textureSlot);
}

void EffectManager::BindDepthTex(int textureSlot)
{
	m_compoundEffect->BindDepthAsTexture(0, textureSlot);
}

void EffectManager::UnbindTexture(int textureSlot)
{
	m_compoundEffect->UnbindTexture(textureSlot);
}

void EffectManager::DrawCompoundEffect()
{
	m_compoundEffect->DrawToScreen();
}

void EffectManager::BindBasicEffect()
{
	m_basicEffect->BindBuffer(0);
}

void EffectManager::UnbindBasicEffect()
{
	m_basicEffect->UnbindBuffer();
}

bool EffectManager::GetEffectInit()
{
	return m_effectsInit;
}

int EffectManager::GetNumEffects()
{
	return m_numEffects;
}

int EffectManager::GetSepiaHandle()
{
	return m_sepia;
}

int EffectManager::GetGreyscaleHandle()
{
	return m_greyscale;
}

int EffectManager::GetVignetteHandle()
{
	return m_vignette;
}

int EffectManager::GetGrainHandle()
{
	return m_grain;
}

int EffectManager::GetPixelateHandle()
{
	return m_pixelate;
}

int EffectManager::GetSelectiveColorHandle()
{
	return m_selectiveColor;
}

int EffectManager::GetBloomHandle()
{
	return m_bloom;
}
