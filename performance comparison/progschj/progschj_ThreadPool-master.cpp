#include<fstream>
#include"../header/progschj.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"progschj.txt"};

	ofs<<"progschj"<<endl<<"\teach spends "<<
		test_progschj_ctor_and_dtor()/iteration
		<<" nanoseconds on test_progschj_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_progschj_specific_N()/iteration
		<<" nanoseconds on test_progschj_specific_N"<<endl<<"\teach spends "<<
		test_progschj_billion()/iteration
		<<" nanoseconds on test_progschj_billion";
}