#include"CCThreadList.h"
#include<algorithm>
#include<utility>

namespace nTool
{
	template<class T>
	template<class UnaryPred>
	void CThreadList<T>::erase(UnaryPred pred)
	{
		std::lock_guard<std::mutex> lock{insertMut_};
		const auto iter{std::find_if(list_.begin(),list_.end(),pred)};
		if(iter!=list_.end())
			list_.erase(iter);
	}

	template<class T>
	void CThreadList<T>::push_back(const T &val)
	{
		std::lock_guard<std::mutex> lock{insertMut_};
		list_.push_back(val);
		insert_.notify_all();
	}

	template<class T>
	void CThreadList<T>::push_back(T &&rVal)
	{
		std::lock_guard<std::mutex> lock{insertMut_};
		list_.push_back(std::move(rVal));
		insert_.notify_all();
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