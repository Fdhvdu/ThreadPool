#include<fstream>
#include"../header/tghosgor.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"tghosgor.txt"};

	ofs<<"tghosgor"<<endl<<"\teach spends "<<
		test_tghosgor_ctor_and_dtor()/iteration
		<<" nanoseconds on test_tghosgor_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_tghosgor_specific_N()/iteration
		<<" nanoseconds on test_tghosgor_specific_N"<<endl<<"\teach spends "<<
		test_tghosgor_all_N()/iteration
		<<" nanoseconds on test_tghosgor_all_N"<<endl<<"\teach spends "<<
		test_tghosgor_billion()/iteration
		<<" nanoseconds on test_tghosgor_billion";
}