from dataclasses import dataclass
import random
from typing import cast, Dict, TypeVar, Optional, Generic
from collections import defaultdict, OrderedDict

K = TypeVar("K")
V = TypeVar("V")

class LRU(Generic[K, V]):
    """
    Production-grade LRU (Least Recently Used) cache with O(1) get/put.

    - Uses a hashmap + doubly linked list.
    - Most recently used item is directly after the head sentinel.
    - Least recently used item is directly before the tail sentinel.
    """

    @dataclass
    class Node(Generic[K, V]):
        key: K
        value: V
        prev: Optional["LRU.Node[K, V]"] = None
        next: Optional["LRU.Node[K, V]"] = None

    def __init__(self, capacity: int) -> None:
        self.capacity: int = capacity
        # Sentinel nodes to avoid empty-list edge cases
        self._head: LRU.Node[K, V] = LRU.Node(cast(K, None), cast(V, None))
        self._tail: LRU.Node[K, V] = LRU.Node(cast(K, None), cast(V, None))
        self._head.next = self._tail
        self._tail.prev = self._head

        self._nodes: Dict[K, LRU.Node[K, V]] = {}
        self._size: int = 0

    # Internal linked-list helpers
    def _add_to_front(self, node: Node[K, V]) -> None:
        """Insert node right after head (most recently used position)."""
        node.next = self._head.next
        node.prev = self._head

        self._head.next.prev = node
        self._head.next = node

    def _remove_node(self, node: Node[K, V]) -> None:
        """Detach node from the linked list."""
        prev_node = node.prev
        next_node = node.next
        if prev_node is not None:
            prev_node.next = next_node
        if next_node is not None:
            next_node.prev = prev_node
        node.prev = None
        node.next = None

    def _move_to_front(self, node: Node[K, V]) -> None:
        """Move an existing node to the most recently used position."""
        self._remove_node(node)
        self._add_to_front(node)

    def _evict_lru(self) -> None:
        """Remove the least recently used item from the cache."""
        lru = self._tail.prev
        if lru is None or lru is self._head:
            return  # Shouldn't happen with correct size/capacity, but be defensive.
        self._remove_node(lru)
        del self._nodes[lru.key]
        self._size -= 1

    def get(self, key: K) -> Optional[V]:
        """
        Return the value of the key if present, otherwise None.
        Access marks the entry as most recently used.
        """
        node = self._nodes.get(key)
        if node is None:
            return None

        self._move_to_front(node)
        return node.value

    def put(self, key: K, value: V) -> None:
        """
        Insert or update the value for key.
        If the cache exceeds capacity, evicts the least recently used item.
        """
        if self.capacity == 0:
            return        
        node = self._nodes.get(key)

        if node is not None:
            # Update existing node and move to front
            node.value = value
            self._move_to_front(node)
            return

        # Insert new node
        if self._size == self.capacity:
            self._evict_lru()

        new_node = LRU.Node(key, value)
        self._add_to_front(new_node)
        self._nodes[key] = new_node
        self._size += 1

    def __len__(self) -> int:  # pragma: no cover - trivial
        return self._size

    def __contains__(self, key: K) -> bool:  # pragma: no cover - trivial
        return key in self._nodes

    def __repr__(self) -> str:  # pragma: no cover - trivial
        items = []
        node = self._head.next
        while node is not None and node is not self._tail:
            items.append(f"{node.key}={node.value}")
            node = node.next
        return f"LRU(capacity={self.capacity}, items=[{', '.join(items)}])"


# -----------------------------
# Demo
# -----------------------------
def _demo():
    print("=== LRU Demo ===")
    c = LRU(2)

    c.put(1, 1)
    print(c)

    c.put(2, 2)
    print(c)

    print("get(1) ->", c.get(1))
    print(c)

    c.put(3, 3)  # evicts key 2
    print("after put(3,3)")
    print(c)

    print("get(2) ->", c.get(2))
    print("get(3) ->", c.get(3))
    print(c)

    c.put(4, 4)  # evicts key 1
    print("after put(4,4)")
    print(c)

    print("get(1) ->", c.get(1))
    print("get(3) ->", c.get(3))
    print("get(4) ->", c.get(4))
    print(c)

# -----------------------------
# Self-check (randomized test)
# -----------------------------
def _self_check():
    print("=== Running self-check ===")
    class ReferenceLRU:
        def __init__(self, capacity):
            self.cap = capacity
            self.cache = OrderedDict()

        def get(self, key):
            if key not in self.cache:
                return None

            # move to most recent
            self.cache.move_to_end(key)
            return self.cache[key]

        def put(self, key, value):
            if self.cap == 0:
                return

            if key in self.cache:
                # update + move to most recent
                self.cache[key] = value
                self.cache.move_to_end(key)
                return

            if len(self.cache) == self.cap:
                # evict LRU (first item)
                self.cache.popitem(last=False)

            self.cache[key] = value

    for _ in range(200):
        cap = random.randint(0, 5)
        lru = LRU[int, int](cap)
        ref = ReferenceLRU(cap)

        for _ in range(500):
            op = random.choice(["get", "put"])
            k = random.randint(1, 5)

            if op == "get":
                if lru.get(k) != ref.get(k):
                    print("Mismatch on get", k)
                    print(lru)
                    return
            else:
                v = random.randint(1, 100)
                lru.put(k, v)
                ref.put(k, v)

    print("Self-check passed!")

if __name__ == "__main__":
    _self_check()
    _demo()
