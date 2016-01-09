#include"CPimpl.h"
#include<utility>	//std::forward

namespace nTool
{
	template<class T>
	CPimpl<T>::CPimpl()
		:p_{std::make_unique<T>()}{}

	template<class T>
	CPimpl<T>::CPimpl(const CPimpl &val)
		:p_{std::make_unique<T>(val.get())}{}

	template<class T>
	CPimpl<T>::CPimpl(CPimpl &&rVal) noexcept
		:p_{std::move(rVal.p_)}{}

	template<class T>
	template<class ... Args>
	CPimpl<T>::CPimpl(Args &&...args)
		:p_{std::make_unique<T>(std::forward<Args>(args)...)}{}

	template<class T>
	CPimpl<T>& CPimpl<T>::operator=(const CPimpl &val)
	{
		get()=val.get();
		return *this;
	}

	template<class T>
	CPimpl<T>& CPimpl<T>::operator=(CPimpl &&rVal) noexcept
	{
		p_=std::move(rVal.p_);
		return *this;
	}

	template<class T>
	CPimpl<T>::~CPimpl(){}
}