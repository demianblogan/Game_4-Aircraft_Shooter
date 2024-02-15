#pragma once

#include <vector>

#include "Component.h"

namespace GUI
{
	// You can group GUI entities in Container class. So it's just
	// a group of other GUI entities, that implements a list of them
	// where you can go through them (it's like a menu, etc.).
	class Container : public Component
	{
	public:
		using Pointer = std::shared_ptr<Container>;

		void AddComponent(Component::Pointer component);

		virtual bool IsSelectable() const override;
		virtual void HandleEvent(const sf::Event& event);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool HasSelectedChild() const;
		void Select(int index);
		void SelectNext();
		void SelectPrevious();

		std::vector<Component::Pointer> children;
		int selectedChildIndex = -1;
	};
}