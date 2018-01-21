#include<fstream>
#include<string>
#include"../header/Tyler-Hardin.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("out_"+string(argv[1]));

	ofs<<"Tyler-Hardin"<<endl<<"\teach spends "<<
		test_TylerHardin_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_TylerHardin_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_TylerHardin_specific_N(cnt)/cnt
		<<" nanoseconds on test_TylerHardin_specific_N"<<endl<<"\teach spends "<<
		test_TylerHardin_job(cnt)/cnt
		<<" nanoseconds on test_TylerHardin_job";
}