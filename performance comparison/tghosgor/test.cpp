#include<fstream>
#include<string>
#include"../header/tghosgor.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("tghosgor");

	ofs<<"tghosgor"<<endl<<"\teach spends "<<
		test_tghosgor_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_tghosgor_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_tghosgor_specific_N(cnt)/cnt
		<<" nanoseconds on test_tghosgor_specific_N"<<endl<<"\teach spends "<<
		test_tghosgor_all_N(cnt)/cnt
		<<" nanoseconds on test_tghosgor_all_N"<<endl<<"\teach spends "<<
		test_tghosgor_job(cnt)/cnt
		<<" nanoseconds on test_tghosgor_job";
}