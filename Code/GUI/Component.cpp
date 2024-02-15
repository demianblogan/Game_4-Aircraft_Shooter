#include "Component.h"

GUI::Component::~Component()
{ }

bool GUI::Component::IsSelected() const
{
	return isSelected;
}

void GUI::Component::Select()
{
	isSelected = true;
}

void GUI::Component::Deselect()
{
	isSelected = false;
}

bool GUI::Component::IsActive() const
{
	return isActive;
}

void GUI::Component::Activate()
{
	isActive = true;
}

void GUI::Component::Deactivate()
{
	isActive = false;
}