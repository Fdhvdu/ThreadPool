#include<fstream>
#include"../../../lib/header/tool/CChrono_timer.hpp"
#include"../header/Fdhvdu.hpp"
#include"../header/progschj.hpp"

int main()
{
	using namespace std;

	ofstream ofs{"Fdhvdu vs progschj.txt"};

	ofs<<"Fdhvdu's CThreadPool_Ret"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_fibonacci_10).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_fibonacci_47).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_iterative_100000).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_iterative_2000000000).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"Fdhvdu's CThreadPool (Detach)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_fibonacci_10).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_fibonacci_47).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_iterative_100000).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_iterative_2000000000).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"Fdhvdu's CThreadPool (Join)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_fibonacci_10).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_fibonacci_47).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_iterative_100000).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_iterative_2000000000).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"progschj"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_progschj_fibonacci_10).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_progschj_fibonacci_47).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_progschj_iterative_100000).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_progschj_iterative_2000000000).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;
}