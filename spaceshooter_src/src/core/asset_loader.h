#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "utils/fileutils.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

namespace Nata
{
	class NAsset;
	class NAssetLoader
	{
	protected:
		static std::vector<NAsset*> m_LoadedAssets;
		static unsigned int m_IterID;

	public:
		static void Submit(NAsset* asset);

		// loads all assets in folder
		template<typename T>
		static void Load(std::string folderPath)
		{
			for (const auto& dirEntry : recursive_directory_iterator(folderPath))
			{
				std::string path = dirEntry.path().string();
				new T(path);
			}
		}
		
		template<typename T>
		static T* Get(std::string path)
		{
			for (NAsset* asset : m_LoadedAssets)
			{
				if (asset->m_Path == path)
				{
					return (T*)asset;
				}
			}
		}
		
		template<typename T>
		static NAsset* Get(unsigned int id)
		{
			for (NAsset* asset : m_LoadedAssets)
			{
				if (asset->ID == id)
				{
					return (T*)asset;
				}
			}
		}
	};

	class NAsset
	{
	public:
		friend class NAssetLoader;

	protected:
		std::string m_Path;
		unsigned int m_ID;
		unsigned int m_Type;

	public:
		NAsset();
		NAsset(std::string path);

	public:
		virtual bool Load() { return false; };
	};
}