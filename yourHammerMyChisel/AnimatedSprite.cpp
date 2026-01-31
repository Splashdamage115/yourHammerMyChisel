#include "AnimatedSprite.h"
#include "Game.h"


AnimatedSprite::AnimatedSprite()
{
}

void AnimatedSprite::Start()
{
	frameSeq = { 0, 1, 2 };

	m_textures.emplace_back(TextureStore());

	if(!m_textures.at(m_textures.size() - 1).tex.loadFromFile("./ASSETS/IMAGES/bg.png"))
	{
		DEBUG_MSG("COULDNT LOAD BG");
	}
	else
	{
		m_textures.at(m_textures.size() - 1).texType = TextureType::bg;
	}

	m_textures.emplace_back(TextureStore());

	if (!m_textures.at(m_textures.size() - 1).tex.loadFromFile("./ASSETS/IMAGES/client.png"))
	{
		DEBUG_MSG("COULDNT LOAD client");
	}
	else
	{
		m_textures.at(m_textures.size() - 1).texType = TextureType::client;
	}

	m_textures.emplace_back(TextureStore());

	if (!m_textures.at(m_textures.size() - 1).tex.loadFromFile("./ASSETS/IMAGES/moodman.png"))
	{
		DEBUG_MSG("COULDNT LOAD moodman");
	}
	else
	{
		m_textures.at(m_textures.size() - 1).texType = TextureType::moodman;
	}
}

void AnimatedSprite::update()
{
	timeLeftToFrame -= Game::deltaTime;

	if (timeLeftToFrame <= 0.f)
	{
		timeLeftToFrame = FRAME_TIME;

		frameNum++;
		if (frameNum >= frameSeq.size())
		{
			frameNum = 0;
		}

		for (int i = 0; i < m_sprites.size(); i++)
		{
			m_sprites.at(i)->changeFrame(frameSeq.at(frameNum));
		}
	}
}

std::shared_ptr<Sprite> AnimatedSprite::getSprite(TextureType t_textureType)
{
	sf::Texture* tex = nullptr;

	for (int i = 0; i < m_textures.size(); i++)
	{
		if (m_textures.at(i).texType == t_textureType)
		{
			tex = &m_textures.at(i).tex;
			break;
		}
	}
	
	std::shared_ptr<Sprite> s = std::make_shared<Sprite>(*tex);

	m_sprites.push_back(s);

	return s;
}

Sprite::Sprite(sf::Texture& t_texture) : sprite(t_texture)
{
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(t_texture.getSize().x / 3.0f, t_texture.getSize().y)));
	sprite.setScale(sf::Vector2f(4.0f, 4.0f));
	xWidth = t_texture.getSize().x / 3.0f;
}

void Sprite::changeFrame(int newFrameNum)
{
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(xWidth * newFrameNum, 0), sf::Vector2i(sprite.getTextureRect().size.x, sprite.getTextureRect().size.y)));
}
