from queue import Queue
from typing import Dict


class Node:

    def __init__(self) -> None:
        # 失败指针
        self.fail: Node = None
        # 哈希表存放所有子节点, key是字符， value是对应的Node节点
        self.next: Dict[str, Node] = {}
        # 如果该节点是单词结尾， 用set结合存放其单词长度
        self.wordLenSet = set()


class AcTree:

    def __init__(self, patternList) -> None:
        self.root = Node()
        
        # 将所有单词插入字典树
        for e in patternList:
            self.insert(e)
        
        # 对字典树构建失败指针
        self.buildFial()

    def insert(self, pattern):
        # 从根节点开始, 从cur指针遍历字典树
        cur = self.root
                # 遍历每一个字符
        for c in pattern:
                # 如果该节点的孩子节点中不存在该字符, 则新建并插入
            if not cur.next.get(c):
                cur.next[c] = Node()
            # 指向下一个字符节点
            cur = cur.next.get(c)
                # 最后cur指向最后一个字符节点, 将其标记为单词结尾
        cur.wordLenSet.add(len(pattern))

    def buildFial(self):
        queue = Queue()
        queue.put(self.root)

        
        # 对字典树进行BFS遍历对每个节点的所有孩子节点构建失败指针
        while not queue.empty():
            parentNode: Node = queue.get()
                        
                        # 对每个孩子节点构建失败指针
            for c, node in parentNode.next.items():
                # 孩子节点node的父节点的失败指针
                pFail = parentNode.fail

                # 循环判断其父节点的失败指针下是否存在该字符，如果有指向它并退出， 否则最终回退到指向根节点
                while pFail is not None and not pFail.next.get(c):
                    pFail = pFail.fail
                                
                                # 如果pFail为null说明回退到了根节点说明在树上不存在最长后缀,直接指向root
                if pFail is None:
                    node.fail = self.root
                else:
                    node.fail = pFail.next.get(c)
                    
                    # 把失败指针存放的单词长度也添加进来这个失配的节点，方便后面快速获取到所有匹配的模式串
                    if len(node.fail.wordLenSet) > 0:
                        node.wordLenSet.update(node.fail.wordLenSet)

                #
                queue.put(node)
    
    # 搜索主串， 找出其中所有包含的模式串
    def search(self, text):
        cur = self.root

        for i in range(len(text)):   
            # 如果该节点不存在该字符， 则从失败指针继续判断， 不断回退直到找到或者回退到根节点
            while cur.fail and cur.next.get(text[i]) is None:
                cur = cur.fail

            if cur.next.get(text[i]):
                cur = cur.next.get(text[i])
                
                # 如果匹配成功并且该节点是单词结尾， 用 i - 单词长度即可获得模式串在主串的位置
                if len(cur.wordLenSet) > 0:
                    for wordLen in cur.wordLenSet:
                        index = i - wordLen + 1
                        match = text[index:i+1]
                        print(f"匹配到了模式串: {match}, 其实索引为: {index}")



if __name__ == '__main__':
    # 测试
    ac = AcTree(["he", "she", "hers", "his", "shy"])
    ac.search("ahishers")

