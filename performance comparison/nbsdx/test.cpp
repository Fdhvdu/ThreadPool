#include<fstream>
#include"../header/nbsdx.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"nbsdx.txt"};

	ofs<<"nbsdx"<<endl<<"\teach spends "<<
		test_nbsdx_ctor_and_dtor()/iteration
		<<" nanoseconds on test_nbsdx_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_nbsdx_all_N()/iteration
		<<" nanoseconds on test_nbsdx_all_N"<<endl<<"\teach spends "<<
		test_nbsdx_10_million()/iteration
		<<" nanoseconds on test_nbsdx_10_million";
}