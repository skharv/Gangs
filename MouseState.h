#ifndef _MOUSESTATE_H
#define _MOUSESTATE_H

#include <SFML/Graphics.hpp>

namespace ms
{
	enum Stage1 { Zone, Build };
	enum Stage2 { SocialClass, TileIndex };
	enum Stage3 { LowIncome, MediumIncome, HighIncome, House1, House2, House3, House4 };
}

class MouseState
{
private:
public:
	MouseState();
	~MouseState();
};

#endif