语音识别论文
=============
- [ ] 传统
  - [ ] 特征处理
  - [ ] 声学模型
    - [x] HMM
    - [x] GMM
  - [x] 语言模型
    - [x] FINITE-STATE GRAMMAR
    - [x] N-GRAM model
      - [ ] n-gram model
      - [ ] back-off smoothing
  - [ ] 解码
    - [ ] decoder
      - [x] The one-pass viterbi algorithm(time-synchronus viterbi search)
      - [x] Time-synchronous viterbi beam search 
      - [ ] Prefix-tree-based search 
      - [ ] Look-head
      - [ ] Multi-pass decoding
      - [ ] discriminative training
      - [ ] unsupervised adaptation
      - [ ] confidence estimation
      - [ ] word-lattice
      - [ ] n-best list
      - [ ] confidence estimation
      - [ ] word-pair approximation
      - [x] WFST
  - [ ] 工具
- [ ] End-to-End
  - [x] [Hybrid CTC/Attention Architecture for End-to-End Speech Recognition]
  - [ ] 



## 传统
### 语言模型
#### FINITE-STATE GRAMMAR
FSGs are usefule for building speech recognizers for small tasks.
#### N-GRAM model

### 解码 
#### decoder
##### the one-pass viterbi algorithm(time-synchronus viterbi search)
##### time-synchronous viterbi beam search 
