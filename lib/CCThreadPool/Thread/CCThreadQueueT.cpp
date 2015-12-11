#include"CCThreadQueue.h"
#include<utility>

namespace nTool
{
	template<class T>
	void CThreadQueue<T>::push(const T &val)
	{
		std::lock_guard<std::mutex> lock{pushMut_};
		queue_.push(val);
		push_.notify_all();
	}

	template<class T>
	void CThreadQueue<T>::push(T &&rVal)
	{
		std::lock_guard<std::mutex> lock{pushMut_};
		queue_.push(std::move(rVal));
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