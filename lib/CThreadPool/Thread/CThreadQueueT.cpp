#include"CThreadQueue.h"
#include<utility>

namespace nTool
{
	template<class T>
	template<class ... Args>
	void CThreadQueue<T>::emplace(Args &&...args)
	{
		std::lock_guard<std::mutex> lock{pushMut_};
		queue_.emplace(std::forward<Args>(args)...);
		push_.notify_all();
	}

	template<class T>
	T CThreadQueue<T>::wait_and_pop()
	{
		std::unique_lock<std::mutex> lock{pushMut_};
		push_.wait(lock,[&]{return size();});
		const auto temp{queue_.front()};
		queue_.pop();
		lock.unlock();
		return temp;
	}
}