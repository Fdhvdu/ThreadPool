#include"CCTask.h"
#include<functional>	//bind

namespace nTool
{
	template<class Ret>
	template<class Func,class ... Args>
	CTask<Ret>::CTask(Func &&func,Args &&...args)
		:task_{std::bind(std::forward<Func>(func),std::forward<Args>(args)...)},fut_{task_.get_future()}{}
}