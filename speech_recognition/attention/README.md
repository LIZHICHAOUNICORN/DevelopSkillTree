Seq2Seq  with attention
=============
使用attention机制建模，使用传统的seq2seq（encoder-decoder）建模
# Develop envronment

# dataset

# model

# optimizer

# decode

# result
```

```

1. 不应该将初始化放在每个layer中，这样造成代码重复。  
2. 使用yaml 减少变量满天飞, 进一步可以使用speechbrain的扩展yaml解析  

# problem
权重初始化需要根据torch.nn.Module的类型分别初始化

# TODO
- [x] 参数设置使用yaml 替换  
- [x] 分别支持cpu 和 gpu 调试及训练  
- [x] 支持真实数据训练以及模拟数据调试  
- [x] 支持翻译任务及其他任务   
- [ ] 支持自建模单元粒度  
- [ ] 根据不同layer做权重初始化  
- [ ] 支持tensorboard  
- [ ] 支持DDP   
- [ ] 将logging统一配置管理  
- [ ] 将模块内部的main函数移到单元测试  
