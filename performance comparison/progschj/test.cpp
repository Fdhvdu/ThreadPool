#include<fstream>
#include<string>
#include"../header/progschj.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("out_"+string(argv[1]));

	ofs<<"progschj"<<endl<<"\teach spends "<<
		test_progschj_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_progschj_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_progschj_specific_N(cnt)/cnt
		<<" nanoseconds on test_progschj_specific_N"<<endl<<"\teach spends "<<
		test_progschj_job(cnt)/cnt
		<<" nanoseconds on test_progschj_job";
}