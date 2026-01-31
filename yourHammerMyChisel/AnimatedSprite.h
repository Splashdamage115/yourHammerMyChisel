#pragma once

#include "Library.h"

struct Sprite
{
	Sprite(sf::Texture& t_texture);
	sf::Sprite sprite;

	void changeFrame(int newFrameNum);

	float xWidth = 0;
};

enum class TextureType
{
	bg, client, moodman
};

struct TextureStore
{
	sf::Texture tex;
	TextureType texType;
};

class AnimatedSprite
{
public:
	AnimatedSprite();
	void Start();
	void update();

	std::shared_ptr<Sprite> getSprite(TextureType t_textureType);
private:
	std::vector<std::shared_ptr<Sprite>> m_sprites;
	std::vector < TextureStore > m_textures;

	float timeLeftToFrame = FRAME_TIME;
	int frameNum = 0;
	std::vector<int> frameSeq;
};

