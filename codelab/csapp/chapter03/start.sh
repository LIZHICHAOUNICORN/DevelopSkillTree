# rm mstore.s mstore.o
# 以Og优化方式编译成汇编指令
gcc -Og -S  mstore.c
#  以Og优化方式编译成机器指令
gcc -Og -c mstore.c
# 使用objdump 反汇编器 查看机器码
objdump -d mstore.o

# 编译可执行文件
gcc -Og  -o prog  main.c mstore.c

rm mstore.s mstore.o prog
