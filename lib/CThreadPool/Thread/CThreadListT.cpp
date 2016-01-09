#include"CThreadList.h"
#include<utility>

namespace nTool
{
	template<class T>
	template<class ... Args>
	void CThreadList<T>::emplace_back(Args &&...args)
	{
		std::lock_guard<std::mutex> lock{insertMut_};
		list_.emplace_back(std::forward<Args>(args)...);
		insert_.notify_all();
	}

	template<class T>
	template<class UnaryPred>
	void CThreadList<T>::remove_if(UnaryPred pred)
	{
		std::lock_guard<std::mutex> lock{insertMut_};
		list_.remove_if(pred);
	}

	template<class T>
	T CThreadList<T>::wait_and_pop()
	{
		std::unique_lock<std::mutex> lock{insertMut_};
		insert_.wait(lock,[&]{return size();});
		const auto temp{list_.front()};
		list_.pop_front();
		lock.unlock();
		return temp;
	}
}