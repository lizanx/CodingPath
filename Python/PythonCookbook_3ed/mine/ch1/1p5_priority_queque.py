import heapq

class PriorityQueue:
    def __init__(self) -> None:
        self._queue = []
        self._index = 0
    
    def push(self, item, priority: int):
        heapq.heappush(self._queue, (-priority, self._index, item))
        self._index += 1
        pass

    def pop(self):
        return heapq.heappop(self._queue)[-1]

class Item:
    def __init__(self, name: str) -> None:
        self.name = name
    def __str__(self) -> str:
        return self.name

q = PriorityQueue()
q.push(Item('foo'), 1)
q.push(Item('bar'), 5)
q.push(Item('spam'), 4)
q.push(Item('grok'), 1)
print(q.pop())
print(q.pop())
print(q.pop())
print(q.pop())
