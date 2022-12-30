#pragma once
#include <vector>
#include <queue>
namespace Nata
{
	template<typename T>
	class NDComponent
	{
	public:
		unsigned int Size = 100;
		std::vector<T> Data;

		friend class NComponentPool;

	public:
		NDComponent()
		{
			Size = 0;
		}

		void Init(unsigned int size)
		{
			Size = size;
			Data.reserve(Size);
			for (unsigned int i = 0; i < Size; i++)
			{
				T value = T();
				Data.push_back(value);
			}
		}

		inline std::vector<T> GetData() { return Data; }
		inline void SetSize(unsigned int size) { Size = size; Data.reserve(size); }

		T& operator[](const int i)
		{
			return Data[i];
		}
	};

	class NDComponentPool
	{
	public:
		unsigned int Size;
		std::queue<unsigned int> m_Disabled;
		std::vector<unsigned int> m_Enabled;

	public:
		NDComponentPool()
		{
			m_Enabled.reserve(Size);

			Size = 0;
		}

		NDComponentPool(unsigned int size)
		{
			m_Enabled.reserve(Size);
			Size = size;

			for (unsigned int i = 0; i < Size; i++)
			{
				m_Disabled.push(i);
			}

		}

		int EnableID()
		{
			if (m_Disabled.empty())
			{
				std::cout << "NDCOMPONENTPOOL::ENABLEID : Maxed out ids" << std::endl;
				return -1;
			}
			int id = m_Disabled.front();
			m_Enabled.push_back(id);
			m_Disabled.pop();
			return id;
		}

		void DisableID(unsigned int id)
		{
			for (unsigned int i = 0; i < m_Enabled.size(); i++)
			{
				if (m_Enabled[i] == id)
				{
					m_Enabled.erase(m_Enabled.begin() + i);
					m_Disabled.push(id);
					return;
				}
			}
		}
	};
}