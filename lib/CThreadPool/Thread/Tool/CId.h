#ifndef CID
#define CID
#include<atomic>
#include<cstddef>

namespace nTool
{
	class CId
	{
		std::atomic<std::size_t> id_;
	public:
		CId(std::size_t init=0) noexcept;
		CId(const CId &)=delete;
		inline std::size_t get() const noexcept
		{
			return id_;
		}
		inline std::size_t operator++()
		{
			return ++id_;
		}
		inline std::size_t operator++(int)
		{
			return id_++;
		}
		CId& operator=(const CId &)=delete;
	};
}

#endif