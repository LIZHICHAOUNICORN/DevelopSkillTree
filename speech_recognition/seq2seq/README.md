传统Seq2Seq  
=============
字符串倒序建模，使用传统的seq2seq（encoder-decoder）建模
# Develop envronment

# dataset

# model

# optimizer

# decode

# result
```
2022-01-20 09:45:43,631 train.py decode_logits 71 decode: ['@WPSYYSNWXPCNYGLLHROBLHQWJBZEMYM', '@ULYFPJCHDTYVOPZVSCCESJVFFTZGIZU']    
2022-01-20 09:45:43,631 train.py evaluate 127 label:      ['YWPSYYSNWXPCNYGLLHROBLHQWJBZEMYM', 'HULYFPJCHDTYVOPZVSCCESJVFFTZGIZU']    
2022-01-20 09:45:43,631 train.py evaluate 128 input:      ['MYMEZBJWQHLBORHLLGYNCPXWNSYYSPWY', 'UZIGZTFFVJSECCSVZPOVYTDHCJPFYLUH']    
2022-01-20 09:45:43,631 train.py evaluate 136 eval: 8.973617514129728e-05    
```

# problem
首字母建模有问题，导致解码时发现都是首字母错误。

