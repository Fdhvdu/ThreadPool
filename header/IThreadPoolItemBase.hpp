#ifndef ITHREADPOOLITEMBASE
#define ITHREADPOOLITEMBASE
#include<functional>	//function
#include<thread>	//thread::hardware_concurrency
#include<tuple>	//apply, tuple
#include<type_traits>	//conditional_t, is_lvalue_reference_v, invoke_result_t, remove_reference_t
#include<utility>	//forward, move
#include"../../lib/header/tool/CUnique_obj.hpp"

namespace nThread
{
	struct IThreadPoolItemBase
	{
		using id=std::invoke_result_t<decltype(std::thread::hardware_concurrency)>;
		IThreadPoolItemBase();
		IThreadPoolItemBase(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase(IThreadPoolItemBase &&) noexcept;
		id get_id() const noexcept;
		virtual bool is_running() const noexcept=0;
		virtual void wait() const=0;
		IThreadPoolItemBase& operator=(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase& operator=(IThreadPoolItemBase &&) noexcept;
		virtual ~IThreadPoolItemBase();
	protected:
		void exec_(const std::function<void()> &);
		void exec_(std::function<void()> &&);
	private:
		struct Impl;
		nTool::CUnique_obj<Impl> impl_;
	};

	template<class Func,class ... Args>
	inline auto forward_as_lambda(Func &&func,Args &&...args)
	{
		using namespace std;
		return [f=forward<decltype(func)>(func),tup=tuple<conditional_t<is_lvalue_reference_v<Args>,Args,remove_reference_t<Args>>...>(forward<decltype(args)>(args)...)]() mutable{
			return apply(move(f),move(tup));
		};
	}
}

#endif