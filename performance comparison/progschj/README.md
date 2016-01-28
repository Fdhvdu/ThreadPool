# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization
# Timing
Fdhvdu's CThreadPool_Ret<br>
	spends 1598 milliseconds on fibonacci_10 (execute 100000 times)<br>
	spends 25857 milliseconds on fibonacci_47<br>
	spends 34755 milliseconds on iterative_100000 (execute 100000 times)<br>
	spends 3556 milliseconds on iterative_2000000000<br>
Fdhvdu's CThreadPool (Detach)<br>
	spends 1934 milliseconds on fibonacci_10 (execute 100000 times)<br>
	spends 25847 milliseconds on fibonacci_47<br>
	spends 18448 milliseconds on iterative_100000 (execute 100000 times)<br>
	spends 3370 milliseconds on iterative_2000000000<br>
Fdhvdu's CThreadPool (Join)<br>
	spends 2347 milliseconds on fibonacci_10 (execute 100000 times)<br>
	spends 25854 milliseconds on fibonacci_47<br>
	spends 34927 milliseconds on iterative_100000 (execute 100000 times)<br>
	spends 3439 milliseconds on iterative_2000000000<br>
progschj<br>
	spends 2343 milliseconds on fibonacci_10 (execute 100000 times)<br>
	spends 25875 milliseconds on fibonacci_47<br>
	spends 34310 milliseconds on iterative_100000 (execute 100000 times)<br>
	spends 3460 milliseconds on iterative_2000000000<br>
# Result
Fdhvdu's CThreadPool_Ret is faster than progschj's threadpool<br>
Fdhvdu's CThreadPool with add_and_detach is faster than progschj's threadpool<br>
Fdhvdu's CThreadPool with add is as same as progschj's threadpool