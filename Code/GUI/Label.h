#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "../ResourceManagement/ResourceIdentifiers.h"
#include "../ResourceManagement/ResourceHolder.h"
 
namespace GUI
{
	// Label is just a GUI entity with a text, nothing else.
	class Label : public Component
	{
	public:
		using Pointer = std::shared_ptr<Label>;

		Label(const std::string& text, const FontHolder& fontHolder);

		virtual bool IsSelectable() const override;
		virtual void HandleEvent(const sf::Event& event) override;

		void SetText(const std::string& text);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::Text text;
	};
}