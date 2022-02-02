cpp 并发编程
=============

1. 创建线程  
  1.1. 线程支持移动，但不支持拷贝。  

2. 线程管理(join, detach)
  2.1. join: 阻塞等待线程执行结束，回收资源。
  2.2. detach: 转化为后台线程(daemon thread), 有c++运行时库在线程退出后正确回收线程资源.

3. 执行一次(once_flag)



并发编程练习
=============
- [x] 01_hello_thread
- [x] 01_lambda_thread
- [x] 01_thread: 并发计算[0-100] 之间的开方和。
- [x] 02_thread_self_manage: 线程管理
- [x] 03_执行一次的flag
- [x] 



leetcode 习题
=============
- [ ]  
