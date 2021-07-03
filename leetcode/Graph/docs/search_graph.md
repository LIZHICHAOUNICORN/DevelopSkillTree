
## 图的基本算法
### 1. 广度优先搜索

```
# recurrent pseudocode
def bfs(graph, start, end):
    queue = []
    queue.append(start)
    visited.append(start)
    while queue:
    	node = queue.pop()
	visited.append(node)
	
	process(node)
	for next_node in  generate_child_node(node):
	    queue.append(nodes)

```


### 2. 深度优先搜索

```
# recurrent pseudocode
visited = set()
def dfs(node, visited):
    visited.add(node)
    process(node)
    for next_node in generate_child_node(node):
    	if not next_node in visited:
	    dfs(next_node, visited)

# for-loop pseudocode
def dfs(self, start):
    if start is None:
    	return
    visited, stack = [], [start]
    while stack:
    	node = stack.pop()
	visited.add(node)
	
	process(node)
	for next_node in generate_child_node(node):
	    stack.push(next_node)

```
