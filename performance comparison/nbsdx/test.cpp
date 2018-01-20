#include<fstream>
#include<string>
#include"../header/nbsdx.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("nbsdx");

	ofs<<"nbsdx"<<endl<<"\teach spends "<<
		test_nbsdx_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_nbsdx_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_nbsdx_all_N(cnt)/cnt
		<<" nanoseconds on test_nbsdx_all_N"<<endl<<"\teach spends "<<
		test_nbsdx_job(cnt)/cnt
		<<" nanoseconds on test_nbsdx_job";
}