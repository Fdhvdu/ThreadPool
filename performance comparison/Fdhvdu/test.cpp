#include<fstream>
#include"../header/Fdhvdu.hpp"

int main()
{
	using namespace std;
	
	ofstream ofs{"Fdhvdu.txt"};

	ofs<<"Fdhvdu's CThreadPool"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_ctor_and_dtor()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_join_specific_N()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_join_all_N()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_join_all_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_detach_all_N()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_detach_10_million()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_detach_10_million"<<endl;
		
	ofs<<"Fdhvdu's CThreadPool_Ret"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_Ret_specific_N()/iteration
		<<" nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N";
}