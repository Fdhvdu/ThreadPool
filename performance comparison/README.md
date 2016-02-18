# What is test function?
First, the execution time of function must same (no matter what thread pool you use).<br>
So, the function should be short, and what we need to do is test

	how fast can a thread pool construct and destruct (test iteration times)
	how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
		-test by wait_single (if has)
		-test by wait_all (if has)
	how fast can a thread pool complete iteration jobs
# The version I use
[progschj/ThreadPool](https://github.com/progschj/ThreadPool) 28 commits<br>
[henkel/threadpool](https://github.com/henkel/threadpool) 2 commits<br>
[nbsdx/ThreadPool](https://github.com/nbsdx/ThreadPool) 24 commits<br>
[tghosgor/threadpool11](https://github.com/tghosgor/threadpool11) 177 commits, 11 releases
