#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	// GUI in my project has a hierarchy. All GUI entities have some similar fields
	// and behaviour. All of them has their position, can be drawn onto the window,
	// might be selected and active. This is why Component class is the base class
	// for all of them. A component is active, when you hover your mouse over it, or
	// come to this component by pressing keys. A component is selected, when you
	// click on it, or press ENTER key.
	class Component : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
	{
	public:
		using Pointer = std::shared_ptr<Component>;

		virtual ~Component();
		
		virtual bool IsSelectable() const = 0;
		bool IsSelected() const;
		virtual void Select();
		virtual void Deselect();

		virtual bool IsActive() const;
		virtual void Activate();
		virtual void Deactivate();

		virtual void HandleEvent(const sf::Event& event) = 0;

	private:
		bool isSelected = false;
		bool isActive = false;
	};
}