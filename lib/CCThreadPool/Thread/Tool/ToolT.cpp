#include"Tool.h"
#include<utility>

namespace nTool
{
	template<class Func_t>
	template<class Func,class ... Args>
	CScopeGuard<Func_t>::CScopeGuard(Func &&func,Args &&... args)
		:func_{std::bind(std::forward<Func>(func),std::forward<Args>(args)...)},exec_{true}{}

	template<class Func_t>
	CScopeGuard<Func_t>::CScopeGuard(CScopeGuard &&rVal) noexcept
		:func_{std::move(rVal.func_)},exec_(rVal.exec_)
	{
		rVal.exec_=false;
	}

	template<class Func_t>
	void CScopeGuard<Func_t>::clear()
	{
		exec_=false;
	}

	template<class Func_t>
	CScopeGuard<Func_t>::~CScopeGuard()
	{
		if(exec_)
			func_();
	}
}