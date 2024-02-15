#pragma once

#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "../States/State.h"
#include "../ResourceManagement/ResourceHolder.h"
#include "../ResourceManagement/ResourceIdentifiers.h"

class SoundPlayer;

namespace GUI
{
	// Button is a GUI entity. It has its text, different backgrounds, pressing sound,
	// and can be clickable. When pressing it, it calls linked callback function.
	class Button : public Component
	{
	public:
		using Pointer = std::shared_ptr<Button>;
		using Callback = std::function<void()>;

		enum class Type
		{
			Normal,
			Selected,
			Pressed,
			Count
		};

		Button(State::Context context);

		void SetCallback(Callback callback);
		void SetText(const std::string& text);
		void SetToggle(bool flag);

		virtual bool IsSelectable() const override;
		virtual void Select() override;
		virtual void Deselect() override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		virtual void HandleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void ChangeTexture(Type buttonType);

		Callback callback;
		sf::Sprite sprite;
		sf::Text text;
		SoundPlayer& soundPlayer;
		bool isToggle = false;
	};
}