#ifndef __CCThreadQueue
#define __CCThreadQueue
#include<condition_variable>
#include<cstddef>
#include<queue>
#include<mutex>

namespace nTool
{
	template<class T>
	class CThreadQueue
	{
		std::condition_variable push_;
		std::mutex pushMut_;
		std::queue<T> queue_;
	public:
		void push(const T &);
		void push(T &&);
		inline std::size_t size() const noexcept
		{
			return queue_.size();
		}
		T wait_and_pop();
	};
}

#include"CCThreadQueueT.cpp"

#endif