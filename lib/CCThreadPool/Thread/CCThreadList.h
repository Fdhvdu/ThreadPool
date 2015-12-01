#ifndef __CCThreadList
#define __CCThreadList
#include<condition_variable>
#include<cstddef>
#include<list>
#include<mutex>

namespace nTool
{
	template<class T>
	class CThreadList
	{
		std::condition_variable insert_;
		std::mutex insertMut_;
		std::list<T> list_;
	public:
		template<class UnaryPred>
		void erase(UnaryPred);
		void push_back(const T &);
		void push_back(T &&);
		inline std::size_t size() const noexcept
		{
			return list_.size();
		}
		T wait_and_pop();
	};
}

#include"CCThreadListT.cpp"

#endif