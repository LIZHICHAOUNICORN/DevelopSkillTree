cpp 并发编程
=============

1. 创建线程  
  1.1. 线程支持移动，但不支持拷贝。  

2. 线程管理(join, detach)    
  2.1. join: 阻塞等待线程执行结束，回收资源。    
  2.2. detach: 转化为后台线程(daemon thread), 有c++运行时库在线程退出后正确回收线程资源.    

3. 执行一次(once_flag)    
4. 生产者消费者问题(死锁，以及避免死锁)    
5. 条件变量    
6. 异步执行机制(async, future, promise)    
7. 打包任务(packaged_task)    
8. 异步取值以及赋值(future, promise)  

9. 协程


多线程经典同步问题
=============
- [ ] 生产者-消费者问题
- [ ] 哲学家就餐问题
- [ ] 读写分离问题

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
- [x] 03_执行一次的flag
- [x] 04_dead_lock_transfor: 死锁转账实现
- [x] 04_normal_transfor: 正常转账实现
- [x] 05_transfer_wait_notify: 使用条件变量和互斥锁
- [x] 06_async_task: 异步执行任务
- [x] 07_packaged_task: 打包任务
- [x] 08_promise_future: 异步取值以及设置结果
- [x] 09_parallel_algorithm: 并行算法

leetcode 习题
=============
- [ ]  
