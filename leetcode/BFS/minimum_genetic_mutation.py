from typing import List
import logging

FORMAT = '%(asctime)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.DEBUG, format=FORMAT)

class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        # 广度优先搜索
        bank = set(bank)  # 转换为set, in判断只需O(1)时间
        if end not in bank:  # 目标不可行，直接返回-1
            return -1
        q = [(start, 0)]  # 初始结点以及当前步数
        change = {'A': 'TCG', 'T': 'ACG', 'C': 'ATG', 'G': 'ATC'}  # 每个基因对应的可变换基因
        while q:  # 用队列实现广度优先
            node, step = q.pop(0)
            logging.debug("node: %s, step: %d", node, step)
            if node == end:  # 已经到达目标
                return step
            for i, v in enumerate(node):  # 当前序列的每一个基因
                logging.debug("i %d, v: %s", i, v)
                for j in change[v]:  # 该基因可以改变的方式
                    new = node[:i]+j+node[i+1:]  # 改变后的序列
                    logging.debug("new str: %s", new) 
                    if new in bank:  # 如果该序列可行
                        logging.debug("find: %s", new)
                        q.append((new, step+1))  # 入队，继续广度搜索
                        bank.remove(new)  # 避免重复遍历
        return -1  # 队列空了说明不可达

def main():
    solu = Solution()
    start = "AAAACCCC"
    end = "CCCCCCCC"
    bank = ["AAAACCCA","AAACCCCA","AACCCCCA","AACCCCCC","ACCCCCCC","CCCCCCCC","AAACCCCC","AACCCCCC"]
    ret = solu.minMutation(start, end, bank)
    logging.info("result: %d", ret)

if __name__ == "__main__":
    main()
