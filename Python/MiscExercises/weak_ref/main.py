import gc
import sys
import weakref
from typing import Any


class Node:
    def __init__(self, name: str) -> None:
        self.name = name
        self.next: Any = None

    def __del__(self) -> None:
        print(f"Deleting node {self.name} ...")

    def __repr__(self) -> str:
        return f"Node(name={self.name}, next={self.next.name if self.next else ''})"


def print_node_objs():
    obj_cnt = 0
    for obj in gc.get_objects():
        if type(obj) is Node:
            obj_cnt += 1
            print(
                f"Node({obj.name}) exists with referrers: {[n.name for n in gc.get_referrers(obj) if type(n) is Node]}"
            )
    if obj_cnt == 0:
        print("No Node objects found")


def demo_strong_ref() -> None:
    def test1():
        print("----------- Test 1 -----------")
        n1 = Node("n1")
        n2 = Node("n2")
        print(f"n1 ref-count: {sys.getrefcount(n1)}")
        print(f"n2 ref-count: {sys.getrefcount(n2)}")

    def test2():
        print("----------- Test 2 -----------")
        n1 = Node("n1")
        n2 = Node("n2")
        # Strong ref, cyclic references
        n1.next = n2
        n2.next = n1
        print(f"n1 ref-count: {sys.getrefcount(n1)}")
        print(f"n2 ref-count: {sys.getrefcount(n2)}")
        n1 = None
        n2 = None

    print("-------------- demo_strong_ref --------------")
    test1()
    print_node_objs()
    test2()
    print_node_objs()


def demo_weak_ref() -> None:
    print("-------------- demo_weak_ref --------------")
    node = Node("node")
    weak_node_ref = weakref.ref(node)
    print_node_objs()

    if weak_node_ref():
        print(f"weak_node: {weak_node_ref().name}")
    else:
        print("Non-exist node ref")
    del node
    if weak_node_ref():
        print(f"weak_node: {weak_node_ref().name}")
    else:
        print("Non-exist node ref")


def demo_weak_dict() -> None:
    print("-------------- demo_weak_dict --------------")
    node = Node("Node object")
    cache = weakref.WeakValueDictionary()
    cache["node"] = node
    print("Before deleting 'node': ", dict(cache))
    node = None
    print("After deleting 'node': ", dict(cache))


def demo_weak_set() -> None:
    class Publisher:
        def __init__(self):
            self._subs = weakref.WeakSet()

        def subscribe(self, sub):
            self._subs.add(sub)

        def notify(self, payload):
            for s in list(self._subs):
                s.handle(payload)

    class Subscriber:
        def __init__(self, name):
            self.name = name

        def handle(self, payload):
            print(self.name, "got:", payload)

    print("-------------- demo_weak_dict --------------")
    pub = Publisher()
    sub1 = Subscriber("One")
    pub.subscribe(sub1)
    pub.notify({"event": 1})
    sub1 = None
    gc.collect()
    pub.notify({"event": 2})  # no print this time


def demo_weakref_callback() -> None:
    class Resource:
        def __init__(self, name: str) -> None:
            self.name = name

        def __repr__(self) -> str:
            return f"Resource({self.name})"

    def on_finalize(weak_ref):
        print("Resource has been garbage collected:", weak_ref)

    print("-------------- demo_weakref_callback --------------")
    obj = Resource("resource-1")
    wr = weakref.ref(obj, on_finalize)
    print("Created weak reference:", wr)
    # Drop strong ref
    obj = None
    # Force GC for demo purpose
    gc.collect()


if __name__ == "__main__":
    # demo_strong_ref()
    # demo_weak_ref()
    # demo_weak_dict()
    # demo_weak_set()
    # demo_weakref_callback()
    pass
