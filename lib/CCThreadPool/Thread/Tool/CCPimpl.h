#ifndef __CCPimpl
#define __CCPimpl
#include<memory>	//std::unique_ptr

namespace nTool
{
	template<class T>
	class CPimpl
	{
		std::unique_ptr<T> p_;
	public:
		CPimpl();
		CPimpl(const CPimpl &);
		CPimpl(CPimpl &&) noexcept;
		template<class ... Args>
		CPimpl(Args &&...);
		inline T& get() const noexcept
		{
			return *p_.get();
		}
		CPimpl& operator=(const CPimpl &);
		CPimpl& operator=(CPimpl &&) noexcept;
		~CPimpl();
	};
}

#include"CCPimplT.cpp"

#endif