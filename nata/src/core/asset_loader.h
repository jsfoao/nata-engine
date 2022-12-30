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
	enum class AssetType
	{
		None = 0,
		Shader = 1,
		Model = 2,
	};

	class NAsset
	{
	protected:
		static std::vector<NAsset*> m_LoadedAssets;
		static unsigned int m_IterID;

		std::string m_Name;
		std::string m_OrigPath;
		std::string m_Path;
		unsigned int m_ID;
		AssetType m_Type;

	public:
		NAsset();
		NAsset(std::string path, std::string destPath, std::string name);
		virtual bool Load() { return false; };

		static void Submit(NAsset* asset);

		template<typename T>
		static T* Get(std::string path)
		{
			for (NAsset* asset : m_LoadedAssets)
			{
				std::string fullPath = asset->m_Path + "\\" + asset->m_Name;
				if (fullPath == path)
				{
					return (T*)asset;
				}
			}
		}

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

		inline static std::vector<NAsset*> GetLoadedAssets() { return m_LoadedAssets; }

	private:
		// template, not to be used
		bool Create(std::string path, std::string dest, std::string name)
		{
			NAsset* asset = new NAsset(path, dest, name);
			bool valid = asset->Load();
			if (!valid)
			{
				std::string message = "NASSET::CREATE : Failed to create asset " + name;
				std::cout << message << std::endl;
				return false;
			}
			NAsset::Submit(asset);
			return true;
		}
	};
}