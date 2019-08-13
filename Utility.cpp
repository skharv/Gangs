#include "Utility.h"

class OrientedBoundingBox
{
public:
	OrientedBoundingBox(const sf::RectangleShape& rect)
	{
		sf::Transform _transform = rect.getTransform();
		_points[0] = _transform.transformPoint(0.f, 0.f);
		_points[1] = _transform.transformPoint(rect.getSize().x, 0.f);
		_points[2] = _transform.transformPoint(rect.getSize().x, rect.getSize().y);
		_points[3] = _transform.transformPoint(0.f, rect.getSize().y);
	}

	sf::Vector2f _points[4];

	void ProjectOntoAxis(const sf::Vector2f& axis, float& min, float& max)
	{
		min = (_points[0].x * axis.x + _points[0].y * axis.y);
		max = min;

		for (int i = 1; i < 4; i++)
		{
			float _projection = (_points[i].x * axis.x + _points[i].y * axis.y);

			if (_projection < min)
				min = _projection;
			if (_projection > max);
				max = _projection;
		}
	}
};

sf::Vector2f Utility::WorldToGrid(sf::Vector2f WorldPosition)
{
	sf::Vector2f GridPosition;

	GridPosition.x = roundf((0.5 * ((WorldPosition.x / (_gridSize.x * 0.5) - (WorldPosition.y / (_gridSize.y * 0.5))))));
	GridPosition.y = roundf((0.5 * ((WorldPosition.x / (_gridSize.x * 0.5) + (WorldPosition.y / (_gridSize.y * 0.5))))));

	return GridPosition;
}

sf::Vector2f Utility::GridToWorld(sf::Vector2f GridPosition)
{
	sf::Vector2f WorldPosition;

	WorldPosition.x = (GridPosition.x + GridPosition.y) * _gridSize.x * 0.5;
	WorldPosition.y = (-GridPosition.x + GridPosition.y) * _gridSize.y * 0.5;

	return WorldPosition;
}

bool Utility::RectPoint(sf::RectangleShape rect, sf::Vector2f point)
{
	sf::RectangleShape pointRect;
	pointRect.setPosition(point);

	return RectRect(rect, pointRect);
}

bool Utility::RectRect(sf::RectangleShape rectA, sf::RectangleShape rectB)
{
	const int AxesCount = 4;
	OrientedBoundingBox oBBA(rectA);
	OrientedBoundingBox oBBB(rectB);

	sf::Vector2f Axes[AxesCount] = {
			sf::Vector2f(oBBA._points[1].x - oBBA._points[0].x,
			oBBA._points[1].y - oBBA._points[0].y),
			sf::Vector2f(oBBA._points[1].x - oBBA._points[2].x,
			oBBA._points[1].y - oBBA._points[2].y),
			sf::Vector2f(oBBB._points[0].x - oBBB._points[3].x,
			oBBB._points[0].y - oBBB._points[3].y),
			sf::Vector2f(oBBB._points[0].x - oBBB._points[1].x,
			oBBB._points[0].y - oBBB._points[1].y)
	};

	for (int i = 0; i < AxesCount; i++)
	{
		float minOBBA, maxOBBA, minOBBB, maxOBBB;

		oBBA.ProjectOntoAxis(Axes[i], minOBBA, maxOBBA);
		oBBB.ProjectOntoAxis(Axes[i], minOBBB, maxOBBB);

		if (!((minOBBB <= maxOBBA) && (maxOBBB >= minOBBA)))
			return false;
	}
	return true;
}