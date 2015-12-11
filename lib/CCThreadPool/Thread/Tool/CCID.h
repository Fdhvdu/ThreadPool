#ifndef __CCID
#define __CCID
#include<cstddef>

namespace nTool
{
	class CID
	{
		std::size_t id_;
	public:
		CID(const std::size_t init=0) noexcept;
		CID(const CID &)=delete;
		inline std::size_t get() const noexcept
		{
			return id_;
		}
		inline std::size_t& operator++()
		{
			return ++id_;
		}
		inline std::size_t operator++(int)
		{
			return id_++;
		}
		CID& operator=(const CID &)=delete;
	};
}

#endif