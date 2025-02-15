#include "framework/AssetManager.h"
#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	unique<AssetManager> AssetManager::_assetManager{ nullptr };

	AssetManager& AssetManager::Instance()
	{
		if (!_assetManager)
		{
			_assetManager = unique<AssetManager>{ new AssetManager };
		}

		return *_assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto texturePair = _loadedTextureMap.find(path);
		if (texturePair != _loadedTextureMap.end())
		{
			return texturePair->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(_rootDirectory + path))
		{
			_loadedTextureMap.insert({path, newTexture});
			return newTexture;
		}

		Logger::LogMessage("Texture is not loaded correctly!");		//TODO: log error instead of message!
		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::UnloadUnusedTextures()
	{
		for (auto iterator = _loadedTextureMap.begin(); iterator != _loadedTextureMap.end();)
		{
			if (iterator->second.unique())
			{
				iterator = _loadedTextureMap.erase(iterator);
			}
			else
			{
				++iterator;
			}
		}
	}

	void AssetManager::SetRootDirectory(const std::string& directory)
	{
		_rootDirectory = directory;
	}

	AssetManager::AssetManager()
		: _rootDirectory {}
	{
	}
}