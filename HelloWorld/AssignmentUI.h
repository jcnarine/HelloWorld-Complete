#ifndef __ASSIGNMENTUI_H__
#define __ASSIGNMENTUI_H__

#include <entt/entity/registry.hpp>
#include <imgui/imgui_impl.h>
#include <vector>

#include "BackEnd.h"
#include "Scene.h"
#include "EntityIdentifier.h"
#include "HelloWorld.h"
#include "AssignmentScene.h"

class AssignmentUI
{
public:
	static void CreateTab(entt::registry* reg, Scene* scene);
	static void CreateEditor(entt::registry* reg, Scene* scene);
private:
	static Selectable m_selectable;
};

#endif // !__ASSIGNMENTUI_H__