#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

template <typename SFML_Asset>
void CenterOrigin(SFML_Asset& asset)
{
	sf::FloatRect bounds = asset.getLocalBounds();
	asset.setOrigin(bounds.width / 2, bounds.height / 2);
}

std::string ConvertKeyToString(sf::Keyboard::Key key);

float ConvertDegreesToRadians(float degrees);
float ConvertRadiansToDegrees(float radians);

float GetLength(const sf::Vector2f& vector);
sf::Vector2f GetUnitVector(const sf::Vector2f vector);