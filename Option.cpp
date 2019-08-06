#include "Option.h"

void Option::Draw(sf::RenderWindow &Window)
{
}

Option::Option()
{
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = inactive_function;
	_inactiveParams = inactive_params;
}

void Option::Active()
{
	state = true;
	_util->ButtonAction(_activefunction, _activeParams);
}

void Option::InActive()
{
	state = false;

	//what if not set?
	_util->ButtonAction(_inactivefunction, _inactiveParams);
}

void Option::Click()
{
	state ? InActive() : Active();
}

Option::~Option()
{
}
