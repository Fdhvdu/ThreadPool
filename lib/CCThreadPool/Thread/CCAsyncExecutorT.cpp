#include"CCAsyncExecutor.h"
#include<functional>	//bind

namespace nTool
{
	template<class Func_t>
	template<class Func,class ... Args>
	CAsyncExecutor<Func_t>::CAsyncExecutor(Func &&func,Args &&...args)
		:task_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...)),fut_(task_.get_future()){}

	template<class Func_t>
	template<class ... Args>
	void CAsyncExecutor<Func_t>::init(Args &&...args)
	{
		CAsyncExecutor temp(std::forward<Args>(args)...);
		std::swap(*this,temp);
	}
}