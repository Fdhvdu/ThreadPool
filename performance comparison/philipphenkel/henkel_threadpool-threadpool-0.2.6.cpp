#include<fstream>
#include"../header/henkel.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"henkel.txt"};

	ofs<<"henkel"<<endl<<"\teach spends "<<
		test_henkel_ctor_and_dtor()/iteration
		<<" nanoseconds on test_henkel_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_henkel_all_N()/iteration
		<<" nanoseconds on test_henkel_all_N"<<endl<<"\teach spends "<<
		test_henkel_billion()/iteration
		<<" nanoseconds on test_henkel_billion";
}