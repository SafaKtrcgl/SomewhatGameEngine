#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class AssetManager
	{
	public:
		static AssetManager& Instance();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void UnloadUnusedTextures();

	protected:
		AssetManager();

	private:
		static unique<AssetManager> _assetManager;
		Dictionary<std::string, shared<sf::Texture>> _loadedTextureMap;
	};
}