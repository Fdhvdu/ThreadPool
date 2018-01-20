#include<fstream>
#include"../header/philipphenkel.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"henkel.txt"};

	ofs<<"philipphenkel"<<endl<<"\teach spends "<<
		test_philipphenkel_ctor_and_dtor()/iteration
		<<" nanoseconds on test_philipphenkel_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_philipphenkel_all_N()/iteration
		<<" nanoseconds on test_philipphenkel_all_N"<<endl<<"\teach spends "<<
		test_philipphenkel_10_million()/iteration
		<<" nanoseconds on test_philipphenkel_10_million";
}