

# c++对象模型

- [x] 单一的一般继承  single_inheritance.cc  
- [x] 单一的虚拟继承  
- [x] 多重继承  
- [x] 重复多重继承  multiple_inheritance.cc
- [x] 钻石型的虚拟多重继承  diamond_inheritance.cc  
- [x] 虚拟继承多重继承  virtual_inheritance.cc  
 

## 使用gdb 调试virtable   
```
# gdb 查看
bash# gdb --args bazel-bin/codelab/cplusplus/class/single_inheritance --logtostderr

gdb> print ptr
$1 = (GrandChild *) 0x46a890

gdb> info vtbl ptr
vtable for 'GrandChild' @ 0x444150 (subobject @ 0x46a890):
[0]: 0x4055d8 <GrandChild::f()>
[1]: 0x40545a <Parent::g()>
[2]: 0x405490 <Parent::h()>
[3]: 0x40560e <GrandChild::g_child()>
[4]: 0x40556a <Child::h_child()>
[5]: 0x405644 <GrandChild::h_grandchild()>

gdb> print ptr
$1 = (GrandChild *) 0x46a890
gdb> x/16x 0x46a890
0x46a890:   0x00444150  0x00000000  0x0000000a  0x00000064
0x46a8a0:   0x000003e8  0x00000000  0x00000161  0x00000000
0x46a8b0:   0x000000a8  0x00000000  0x00000134  0x00000000
0x46a8c0:   0xffffffff  0x00000000  0x6d6f682f  0x6f6d2f65

gdb> x/16x 0x00444150
0x444150 <_ZTV10GrandChild+16>: 0x004055d8  0x00000000  0x0040545a  0x00000000
0x444160 <_ZTV10GrandChild+32>: 0x00405490  0x00000000  0x0040560e  0x00000000
0x444170 <_ZTV10GrandChild+48>: 0x0040556a  0x00000000  0x00405644  0x00000000
0x444180 <_ZTV5Child>:  0x00000000  0x00000000  0x00444210  0x00000000

gdb> x/16x 0x004055d8
0x4055d8 <GrandChild::f()>: 0xe5894855  0x10ec8348  0xf87d8948  0x70358d48
0x4055e8 <GrandChild::f()+16>:  0x4800029e  0xf116058b  0x89480003  0xef66e8c7
0x4055f8 <GrandChild::f()+32>:  0x8b48ffff  0x03f10f15  0xd6894800  0xe8c78948
0x405608 <GrandChild::f()+48>:  0xffffef64  0x4855c3c9  0x8348e589  0x894810ec
