#GNU make

CXX=g++
CXXFLAGS=-std=c++17
LDLIBS=-lpthread
VPATH=header:src:tutorial

MY_LIB=../lib

obj=CThreadPool.o CThreadPoolItem.o IThreadPoolItemBase.o IThreadPoolItemExecutor.o example.o example_ret.o
obj_for_example=CThreadPool.o CThreadPoolItem.o IThreadPoolItemBase.o IThreadPoolItemExecutor.o example.o $(MY_LIB)/Scope_guard.o
obj_for_example_ret=IThreadPoolItemBase.o example_ret.o $(MY_LIB)/Scope_guard.o

all:example example_ret

example:$(obj_for_example)
	$(CXX) -o $@ $^ $(LDLIBS)

example_ret:$(obj_for_example_ret)
	$(CXX) -o $@ $^ $(LDLIBS)

.PHONY:clean
clean:
	-rm -f example example_ret $(obj)
	$(MAKE) -C $(MY_LIB) clean

CThreadPool.o:CThreadPoolItem.hpp IThreadPoolItemExecutor.hpp \
		$(MY_LIB)/header/thread/CWait_bounded_queue.hpp \
		$(MY_LIB)/header/thread/tag.hpp

CThreadPoolItem.o:IThreadPoolItemExecutor.hpp

IThreadPoolItemBase.o:$(MY_LIB)/header/thread/CSemaphore.hpp

IThreadPoolItemExecutor.o:$(MY_LIB)/header/thread/CSemaphore.hpp \
		$(MY_LIB)/header/thread/CWait_bounded_queue.hpp

$(MY_LIB)/Scope_guard.o:
	$(MAKE) -C $(MY_LIB) Scope_guard.o
