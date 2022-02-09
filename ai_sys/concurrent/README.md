cpp 并发编程
=============

1. 创建线程  
  1.1. 线程支持移动，但不支持拷贝.
2. 线程管理(join, detach)  
  2.1. join: 阻塞等待线程执行结束，回收资源。    
  2.2. detach: 转化为后台线程(daemon thread), 有c++运行时库在线程退出后正确回收线程资源.    
3. 执行一次(once_flag)
4. 生产者消费者问题(死锁，以及避免死锁)
5. 互斥量，条件变量, 信号量
  5.1. 读写锁
      5.1.1 考虑读优先，写优先。(cpp目前接口没有发现支持，但linux下支持)        
  5.2. 信号量   
  5.3. 自旋锁   
  5.4. 线程局部变量    
  5.5. 线程池(固定数量的线程池)     
  5.6. 线程池(模板化任务队列)    
  5.7. 线程池(单个线程单个队列)    
  5.8. 线程池(支持worksteal)    
6. 异步执行机制(async, future, promise)
7. 打包任务(packaged_task)
8. 异步取值以及赋值(future, promise)
9. 协程


多线程经典同步问题
=============
- [x] 生产者-消费者问题
- [x] 哲学家就餐问题
- [x] 读写问题

Linux下多线程调试工具
=============
1. pstack 查看进程的线程数量以及每个线程的调用堆栈状况。
  1.1. 使用pstack 和top 查看cpu 使用率过高问题，一般不工作线程应该挂起，而不是空转    
2. ps   

死锁
=============
1. 死锁产生的条件

2. 死锁的解决办法

并发编程练习
=============
- [x] 01_hello_thread
- [x] 01_lambda_thread
- [x] 01_thread: 并发计算[0-100] 之间的开方和。
- [x] 02_thread_self_manage: 线程管理
- [x] 03_call_once: 执行一次的flag 
- [x] 04_dead_lock_transfor: 死锁转账实现
- [x] 04_normal_transfor: 正常转账实现
- [x] 05_transfer_wait_notify: 使用条件变量和互斥锁
- [x] 05_shared_mutex_benchmark: 对读写锁和互斥锁benchmark测试
- [x] 05_producer_consumer: 使用信号量写生产者消费者
- [x] 05_thread_local: 使用信号量写生产者消费者
- [x] 06_async_task: 异步执行任务
- [x] 07_packaged_task: 打包任务
- [x] 08_promise_future: 异步取值以及设置结果
- [x] 09_parallel_algorithm: 并行算法

leetcode 习题
=============
- [ ]  
