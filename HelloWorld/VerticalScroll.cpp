#include "VerticalScroll.h"

VerticalScroll::VerticalScroll() {


}

Camera* VerticalScroll::GetCam() const {
	return m_cam;
}

void VerticalScroll::SetCam(Camera* cam) {

	m_cam = cam;

}

Transform* VerticalScroll::GetFocus() const {
	return m_focus;
}

void VerticalScroll::SetFocus(Transform* focus) {

	m_focus = focus;

}

float VerticalScroll::GetOffset() const {
	return m_offset;
}

void VerticalScroll::SetOffset(float offset) {

	m_offset = offset;

}

void VerticalScroll::Update() {

	//Above focus
	if (m_focus->GetPosition().y > m_cam->m_localPosition.y + m_offset) {


		//Calculate the amount the focus has pushed the camera right by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y + m_offset);

		//Adjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, m_cam->GetPosition().y + difference, m_cam->GetPosition().z));

	}

	if (m_focus->GetPosition().y < m_cam->m_localPosition.y - m_offset) {

		float difference2 = m_focus->GetPosition().y - (m_cam->m_localPosition.y - m_offset);
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, m_cam->GetPosition().y + difference2, m_cam->GetPosition().z));

	}
}
