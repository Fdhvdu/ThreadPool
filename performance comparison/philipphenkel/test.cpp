#include<fstream>
#include<string>
#include"../header/philipphenkel.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("out_"+string(argv[1]));

	ofs<<"philipphenkel"<<endl<<"\teach spends "<<
		test_philipphenkel_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_philipphenkel_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_philipphenkel_all_N(cnt)/cnt
		<<" nanoseconds on test_philipphenkel_all_N"<<endl<<"\teach spends "<<
		test_philipphenkel_job(cnt)/cnt
		<<" nanoseconds on test_philipphenkel_job";
}