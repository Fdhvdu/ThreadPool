#include<fstream>
#include<string>
#include"../header/mtrebi.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("out_"+string(argv[1]));

	ofs<<"mtrebi"<<endl<<"\teach spends "<<
		test_mtrebi_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_mtrebi_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_mtrebi_init_and_dtor(cnt)/cnt
		<<" nanoseconds on test_mtrebi_init_and_dtor"<<endl<<"\teach spends "<<
		test_mtrebi_specific_N(cnt)/cnt
		<<" nanoseconds on test_mtrebi_specific_N"<<endl<<"\teach spends "<<
		test_mtrebi_job(cnt)/cnt
		<<" nanoseconds on test_mtrebi_job";
}