#pragma once
#include "GameObject.h"

#include <vector>
#include <unordered_map>

struct TileInfo
{
public:
	sf::Texture& texture;
	bool collidable;

public:
	TileInfo(sf::Texture& texture, bool collidable = false)
		: texture(texture), collidable(collidable)
	{ }
};

struct Tile
{
private:
	TileInfo* info;
	sf::Sprite sprite;
public:
	Tile(TileInfo* info, sf::Vector2f pos)
		: info(info), sprite(info->texture)
	{
		sprite.setPosition(pos);
	}

	void render(sf::RenderWindow& window, float deltaTime)
	{
		window.draw(sprite);
	}

	const TileInfo* getInfo()
	{
		return info;
	}

	void setInfo(TileInfo* info)
	{
		this->info = info;
	}
};

class TileObject : public GameObject
{
public:
	std::vector<TileInfo> tileset;
	std::vector<std::vector<Tile>> tilemap;
public:
	TileObject(std::vector<TileInfo> tileset, std::vector<std::vector<size_t>> tilemapInfo, int tag = 0)
		: GameObject(tag), tileset(tileset)
	{
		sf::Vector2u size = tileset[0].texture.getSize();

		for (size_t i = 0; i < tilemapInfo.size(); i++) // each row
		{
			std::vector<Tile> col;
			for (size_t j = 0; j < tilemapInfo[i].size(); j++) // each col
			{
				sf::Vector2f pos(j * size.x, i * size.y);
				col.push_back(Tile(&this->tileset[tilemapInfo[i][j]], pos));
			}
			tilemap.push_back(col);
		}
	}

	void render(sf::RenderWindow& window, float deltaTime) override
	{
		for (auto& row : tilemap)
		{
			for (auto& tile : row)
			{
				tile.render(window, deltaTime);
			}
		}
	}

	bool canCollide(sf::Vector2f pos)
	{
		sf::Vector2u size = tileset[0].texture.getSize();
		int i = pos.x / size.x;
		int j = pos.y / size.y;
		if (j >= 0 && j < tilemap.size() && i >= 0 && i < tilemap[j].size())
			return tilemap[j][i].getInfo()->collidable;
		else
			return false;
	}
};
