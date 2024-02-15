#include "Container.h"

#include <SFML/Graphics/RenderTarget.hpp>

void GUI::Container::AddComponent(Component::Pointer component)
{
	children.push_back(component);

	if (!HasSelectedChild() && component->IsSelectable())
		Select(int(children.size()) - 1);
}

bool GUI::Container::IsSelectable() const
{
	return false;
}

void GUI::Container::HandleEvent(const sf::Event& event)
{
	// If we have selected a child then pass it the event:
	if (HasSelectedChild() && children[selectedChildIndex]->IsActive())
	{
		children[selectedChildIndex]->HandleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			SelectPrevious();
			break;

		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			SelectNext();
			break;

		case sf::Keyboard::Space:
		case sf::Keyboard::Enter:
			if (HasSelectedChild())
				children[selectedChildIndex]->Activate();
			break;
		}
	}
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const Component::Pointer& child : children)
		target.draw(*child, states);
}

bool GUI::Container::HasSelectedChild() const
{
	return selectedChildIndex >= 0;
}

void GUI::Container::Select(int index)
{
	if (children[index]->IsSelectable())
	{
		if (HasSelectedChild())
			children[selectedChildIndex]->Deselect();

		children[index]->Select();
		selectedChildIndex = index;
	}
}

void GUI::Container::SelectNext()
{
	if (!HasSelectedChild())
		return;

	// Search next component that is selectable, wrap around if necessary:
	int nextSelectableChildIndex = selectedChildIndex;
	do
	{
		nextSelectableChildIndex = (nextSelectableChildIndex + 1) % children.size();

	} while (!children[nextSelectableChildIndex]->IsSelectable());

	Select(nextSelectableChildIndex);
}

void GUI::Container::SelectPrevious()
{
	if (!HasSelectedChild())
		return;

	// Search previous component that is selectable, wrap around if necessary:
	int previousSelectableChildIndex = selectedChildIndex;
	do
	{
		previousSelectableChildIndex = (previousSelectableChildIndex + int(children.size()) - 1) % children.size();

	} while (!children[previousSelectableChildIndex]->IsSelectable());

	Select(previousSelectableChildIndex);
}