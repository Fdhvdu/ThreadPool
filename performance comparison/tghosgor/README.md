# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization
# Timing
	Fdhvdu's CThreadPool_Ret
		spends 1615 milliseconds on fibonacci_10 (execute 100000 times)
		spends 25853 milliseconds on fibonacci_47
		spends 34751 milliseconds on iterative_100000 (execute 100000 times)
		spends 3655 milliseconds on iterative_2000000000
	Fdhvdu's CThreadPool (Detach)
		spends 1896 milliseconds on fibonacci_10 (execute 100000 times)
		spends 25815 milliseconds on fibonacci_47
		spends 18274 milliseconds on iterative_100000 (execute 100000 times)
		spends 3374 milliseconds on iterative_2000000000
	Fdhvdu's CThreadPool (Join)
		spends 2196 milliseconds on fibonacci_10 (execute 100000 times)
		spends 25817 milliseconds on fibonacci_47
		spends 34977 milliseconds on iterative_100000 (execute 100000 times)
		spends 3415 milliseconds on iterative_2000000000
	tghosgor
		spends 2369 milliseconds on fibonacci_10 (execute 100000 times)
		spends 25775 milliseconds on fibonacci_47
		spends 34252 milliseconds on iterative_100000 (execute 100000 times)
		spends 3380 milliseconds on iterative_2000000000
# Result
Fdhvdu's CThreadPool_Ret is faster than tghosgor's threadpool<br>
(0.9<(3380/3655), they acts same performance on iterative_2000000000)<br>
Fdhvdu's CThreadPool with add_and_detach is faster than tghosgor's threadpool<br>
Fdhvdu's CThreadPool with add is as same as tghosgor's threadpool