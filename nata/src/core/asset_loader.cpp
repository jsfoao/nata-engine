#include "asset_loader.h"

namespace Nata
{
	unsigned int NAsset::m_IterID = 0;
	std::vector<NAsset*> NAsset::m_LoadedAssets;

	void NAsset::Submit(NAsset* asset)
	{
		for (auto& assets : m_LoadedAssets)
		{
			if (asset->m_Name == assets->m_Name)
			{
				std::string message = "NASSET::SUBMIT : Could not create asset " + asset->m_Name + ", file with same name already exists";
				std::cout << message << std::endl;
				return;
			}
		}

		asset->m_ID = m_IterID;
		m_IterID++;

		std::ofstream file(asset->m_Path + "\\" + asset->m_Name + ".nasset");
		file << "#NataAsset\n";
		file << "Type=" + std::to_string((int)asset->m_Type) + "\n";
		file << "Name=" + asset->m_Name + "\n";
		file << "ID=" + std::to_string(asset->m_ID) + "\n";
		file << "Path=" + asset->m_Path + "\n";
		file << "ObjectPath=" + asset->m_OrigPath + "\n";
		file.close();
		
		m_LoadedAssets.push_back(asset);
	}

	NAsset::NAsset()
	{
		m_OrigPath = "";
		m_Path = "";
		m_Name = "";
		m_ID = 0;
		m_Type = AssetType::None;
	}

	NAsset::NAsset(std::string path, std::string destPath, std::string name)
	{
		m_OrigPath = path;
		m_Path = destPath;
		m_Name = name;
		m_ID = 0;
		m_Type = AssetType::None;
		NAsset::Submit(this);
	}
}