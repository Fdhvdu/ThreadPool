# Compile command
	g++ -std=c++14 -O3 \
		-I../../../../tghosgor/threadpool11/threadpool11/include/ \
		-I../../../../tghosgor/threadpool11/ext/include/ \
		test.cpp ../src/tghosgor.cpp \
		../../../../tghosgor/threadpool11/threadpool11/src/* \
		-lpthread
# Warning
Do not use this.<br>
It gets stuck every time.