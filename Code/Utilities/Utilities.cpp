#include "Utilities.h"

#include <cassert>
#include <cmath>
#include <numbers>

#define KEY_TO_STRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

std::string ConvertKeyToString(sf::Keyboard::Key key)
{
	switch (key)
	{
		KEY_TO_STRING_CASE(Unknown)
		KEY_TO_STRING_CASE(A)
		KEY_TO_STRING_CASE(B)
		KEY_TO_STRING_CASE(C)
		KEY_TO_STRING_CASE(D)
		KEY_TO_STRING_CASE(E)
		KEY_TO_STRING_CASE(F)
		KEY_TO_STRING_CASE(G)
		KEY_TO_STRING_CASE(H)
		KEY_TO_STRING_CASE(I)
		KEY_TO_STRING_CASE(J)
		KEY_TO_STRING_CASE(K)
		KEY_TO_STRING_CASE(L)
		KEY_TO_STRING_CASE(M)
		KEY_TO_STRING_CASE(N)
		KEY_TO_STRING_CASE(O)
		KEY_TO_STRING_CASE(P)
		KEY_TO_STRING_CASE(Q)
		KEY_TO_STRING_CASE(R)
		KEY_TO_STRING_CASE(S)
		KEY_TO_STRING_CASE(T)
		KEY_TO_STRING_CASE(U)
		KEY_TO_STRING_CASE(V)
		KEY_TO_STRING_CASE(W)
		KEY_TO_STRING_CASE(X)
		KEY_TO_STRING_CASE(Y)
		KEY_TO_STRING_CASE(Z)
		KEY_TO_STRING_CASE(Num0)
		KEY_TO_STRING_CASE(Num1)
		KEY_TO_STRING_CASE(Num2)
		KEY_TO_STRING_CASE(Num3)
		KEY_TO_STRING_CASE(Num4)
		KEY_TO_STRING_CASE(Num5)
		KEY_TO_STRING_CASE(Num6)
		KEY_TO_STRING_CASE(Num7)
		KEY_TO_STRING_CASE(Num8)
		KEY_TO_STRING_CASE(Num9)
		KEY_TO_STRING_CASE(Escape)
		KEY_TO_STRING_CASE(LControl)
		KEY_TO_STRING_CASE(LShift)
		KEY_TO_STRING_CASE(LAlt)
		KEY_TO_STRING_CASE(LSystem)
		KEY_TO_STRING_CASE(RControl)
		KEY_TO_STRING_CASE(RShift)
		KEY_TO_STRING_CASE(RAlt)
		KEY_TO_STRING_CASE(RSystem)
		KEY_TO_STRING_CASE(Menu)
		KEY_TO_STRING_CASE(LBracket)
		KEY_TO_STRING_CASE(RBracket)
		KEY_TO_STRING_CASE(SemiColon)
		KEY_TO_STRING_CASE(Comma)
		KEY_TO_STRING_CASE(Period)
		KEY_TO_STRING_CASE(Quote)
		KEY_TO_STRING_CASE(Slash)
		KEY_TO_STRING_CASE(BackSlash)
		KEY_TO_STRING_CASE(Tilde)
		KEY_TO_STRING_CASE(Equal)
		KEY_TO_STRING_CASE(Dash)
		KEY_TO_STRING_CASE(Space)
		KEY_TO_STRING_CASE(Return)
		KEY_TO_STRING_CASE(BackSpace)
		KEY_TO_STRING_CASE(Tab)
		KEY_TO_STRING_CASE(PageUp)
		KEY_TO_STRING_CASE(PageDown)
		KEY_TO_STRING_CASE(End)
		KEY_TO_STRING_CASE(Home)
		KEY_TO_STRING_CASE(Insert)
		KEY_TO_STRING_CASE(Delete)
		KEY_TO_STRING_CASE(Add)
		KEY_TO_STRING_CASE(Subtract)
		KEY_TO_STRING_CASE(Multiply)
		KEY_TO_STRING_CASE(Divide)
		KEY_TO_STRING_CASE(Left)
		KEY_TO_STRING_CASE(Right)
		KEY_TO_STRING_CASE(Up)
		KEY_TO_STRING_CASE(Down)
		KEY_TO_STRING_CASE(Numpad0)
		KEY_TO_STRING_CASE(Numpad1)
		KEY_TO_STRING_CASE(Numpad2)
		KEY_TO_STRING_CASE(Numpad3)
		KEY_TO_STRING_CASE(Numpad4)
		KEY_TO_STRING_CASE(Numpad5)
		KEY_TO_STRING_CASE(Numpad6)
		KEY_TO_STRING_CASE(Numpad7)
		KEY_TO_STRING_CASE(Numpad8)
		KEY_TO_STRING_CASE(Numpad9)
		KEY_TO_STRING_CASE(F1)
		KEY_TO_STRING_CASE(F2)
		KEY_TO_STRING_CASE(F3)
		KEY_TO_STRING_CASE(F4)
		KEY_TO_STRING_CASE(F5)
		KEY_TO_STRING_CASE(F6)
		KEY_TO_STRING_CASE(F7)
		KEY_TO_STRING_CASE(F8)
		KEY_TO_STRING_CASE(F9)
		KEY_TO_STRING_CASE(F10)
		KEY_TO_STRING_CASE(F11)
		KEY_TO_STRING_CASE(F12)
		KEY_TO_STRING_CASE(F13)
		KEY_TO_STRING_CASE(F14)
		KEY_TO_STRING_CASE(F15)
		KEY_TO_STRING_CASE(Pause)
	
	default:
		return "";
	}
}

float ConvertDegreesToRadians(float degrees)
{
	return float(std::numbers::pi) / 180.0f * degrees;
}

float ConvertRadiansToDegrees(float radians)
{
	return 180.0f / float(std::numbers::pi) * radians;
}

float GetLength(const sf::Vector2f& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f GetUnitVector(const sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0, 0));
	return vector / GetLength(vector);
}