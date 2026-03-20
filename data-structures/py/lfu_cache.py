from dataclasses import dataclass
from collections.abc import Iterator as AbcIterator
import random
from typing import Dict, TypeVar, Optional, Generic
from collections import defaultdict, OrderedDict

K = TypeVar("K")
V = TypeVar("V")

class LFU(Generic[K, V]):

	@dataclass
	class Node(Generic[K, V]):
		key: K
		value: V
		freq: int = 1
		next: Optional["LFU.Node[K, V]"] = None
		prev: Optional["LFU.Node[K, V]"] = None

	class DLinkedList(Generic[K, V]):
		def __init__(self):
			self.head = LFU.Node(None, None)
			self.tail = LFU.Node(None, None)
			self.head.next = self.tail
			self.tail.prev = self.head
			self.size = 0

		def append(self, node):
			node.prev = self.tail.prev
			node.next = self.tail
			self.tail.prev.next = node
			self.tail.prev = node
			self.size += 1

		def pop(self, node: Optional["LFU.Node[K, V]"] = None) -> Optional["LFU.Node[K, V]"]:
			if self.is_empty():
				return None

			if node is None: # poping LRU in this freq
				node = self.head.next

			node.next.prev = node.prev
			node.prev.next = node.next
			node.next = node.prev = None
			self.size -= 1
			return node

		def is_empty(self) -> bool:
			return self.size == 0

		def __iter__(self) -> AbcIterator["LFU.Node[K, V]"]:
			curr = self.head.next
			while curr != self.tail:
				yield curr
				curr = curr.next

	def __init__(self, capacity: int):
		self.capacity = capacity
		self.size = 0
		
		self.min_freq = 0
		self.key_map : Dict[K, LFU.Node[K, V]] = {}
		self.freq_map : Dict[int, LFU.DLinkedList[K, V]]= {}

	def _update(self, node: "LFU.Node[K, V]") -> None:
		freq = node.freq
		dll = self.freq_map[freq]
		dll.pop(node)

		if dll.is_empty():
			del self.freq_map[freq]
			if self.min_freq == freq:
				# safe because freq increases by exactly +1 and no gaps exist
				self.min_freq += 1
		
		node.freq += 1
		self.freq_map.setdefault(node.freq, LFU.DLinkedList()).append(node)
		
	def get(self, key:K) -> Optional[V]:
		if key not in self.key_map:
			return None

		node = self.key_map[key]
		self._update(node)
		return node.value

	def put(self, key: K, value: V) -> None:
		if self.capacity == 0:
			return

		if key in self.key_map:
			node = self.key_map[key]
			node.value = value
			self._update(node)
			return

		if self.size == self.capacity:
			dll = self.freq_map[self.min_freq]
			evicted = dll.pop()
			if evicted:
				del self.key_map[evicted.key]
				self.size -= 1
			if dll.is_empty():
				del self.freq_map[self.min_freq]

		node = LFU.Node(key, value)
		self.key_map[key] = node
		self.freq_map.setdefault(1, LFU.DLinkedList()).append(node)
		self.min_freq = 1
		self.size += 1

	def __repr__(self) -> str:
		parts = []
		for freq in sorted(self.freq_map):
			nodes = list(self.freq_map[freq])
			items = [(n.key, n.value) for n in nodes]
			parts.append(f"{freq}:{items}")
		return f"LFU(cap={self.capacity}, size={self.size}, min_freq={self.min_freq}) | " + " | ".join(parts)


# -----------------------------
# Demo
# -----------------------------
def _demo():
	print("=== LFU Demo ===")
	c = LFU(2)

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
	class ReferenceLFU:
		def __init__(self, capacity):
			self.cap = capacity
			self.kv = {}
			self.freq = {}
			self.groups = defaultdict(OrderedDict)
			self.min_freq = 0

		def _touch(self, key):
			f = self.freq[key]
			del self.groups[f][key]

			if not self.groups[f]:
				del self.groups[f]
				if self.min_freq == f:
					self.min_freq += 1

			self.freq[key] = f + 1
			self.groups[f + 1][key] = None

		def get(self, key):
			if key not in self.kv:
				return None
			self._touch(key)
			return self.kv[key]

		def put(self, key, value):
			if self.cap == 0:
				return

			if key in self.kv:
				self.kv[key] = value
				self._touch(key)
				return

			if len(self.kv) == self.cap:
				k, _ = self.groups[self.min_freq].popitem(last=False)
				if not self.groups[self.min_freq]:
					del self.groups[self.min_freq]
				del self.kv[k]
				del self.freq[k]

			self.kv[key] = value
			self.freq[key] = 1
			self.groups[1][key] = None
			self.min_freq = 1

	for _ in range(200):
		cap = random.randint(0, 5)
		lfu = LFU[int, int](cap)
		ref = ReferenceLFU(cap)

		for _ in range(500):
			op = random.choice(["get", "put"])
			k = random.randint(1, 5)

			if op == "get":
				if lfu.get(k) != ref.get(k):
					print("Mismatch on get", k)
					print(lfu)
					return
			else:
				v = random.randint(1, 100)
				lfu.put(k, v)
				ref.put(k, v)

	print("Self-check passed!")

if __name__ == "__main__":
	_self_check()
	_demo()

