#include "asset_loader.h"

namespace Nata
{
	unsigned int NAssetLoader::m_IterID = 0;
	std::vector<NAsset*> NAssetLoader::m_LoadedAssets;

	void NAssetLoader::Submit(NAsset* asset)
	{
		asset->ID = m_IterID;
		m_IterID++;
		m_LoadedAssets.push_back(asset);
	}

	NAsset::NAsset()
	{
		ID = 0;
	}
	NAsset::NAsset(std::string path)
	{
		ID = 0;
	}
}