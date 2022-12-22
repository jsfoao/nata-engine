#include "asset_loader.h"

namespace Nata
{
	unsigned int NAssetLoader::m_IterID = 0;
	std::vector<NAsset*> NAssetLoader::m_LoadedAssets;

	void NAssetLoader::Submit(NAsset* asset)
	{
		asset->m_ID = m_IterID;
		m_IterID++;
		m_LoadedAssets.push_back(asset);
	}

	NAsset::NAsset()
	{
		m_ID = 0;
		m_Type = 0;
	}
	NAsset::NAsset(std::string path)
	{
		m_ID = 0;
		m_Type = 0;
	}
}