#ifndef __Tool
#define __Tool
#include<functional>

namespace nTool
{
	template<class Func_t>
	class CScopeGuard
	{
		std::function<Func_t> func_;
		bool exec_;
	public:
		template<class Func,class ... Args>
		explicit CScopeGuard(Func &&,Args &&...);
		CScopeGuard(const CScopeGuard &)=delete;
		CScopeGuard(CScopeGuard &&) noexcept;
		void clear();
		CScopeGuard& operator=(const CScopeGuard &)=delete;
		~CScopeGuard();
	};
}

#include"ToolT.cpp"

#endif