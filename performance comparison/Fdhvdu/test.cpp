#include<fstream>
#include<string>
#include"../header/Fdhvdu.hpp"

int main(int argc,char **argv)
{
	using namespace std;
	const auto cnt(stoul(argv[1]));
	ofstream ofs("Fdhvdu");

	ofs<<"Fdhvdu's CThreadPool"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_join_specific_N(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_join_all_N(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_join_all_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_detach_all_N(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_detach_job(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_detach_job"<<endl;
		
	ofs<<"Fdhvdu's CThreadPool_Ret"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor"<<endl<<"\teach spends "<<
		test_Fdhvdu_CThreadPool_Ret_specific_N(cnt)/cnt
		<<" nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N";
}