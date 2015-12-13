#include"CCTask.h"
#include<functional>	//bind

namespace nTool
{
	template<class Func_t>
	template<class Func,class ... Args>
	CTask<Func_t>::CTask(Func &&func,Args &&...args)
		:task_{std::bind(std::forward<Func>(func),std::forward<Args>(args)...)},fut_{task_.get_future()}{}
}