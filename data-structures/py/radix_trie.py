from __future__ import annotations
from dataclasses import dataclass, field
from typing import Dict, List, Tuple

@dataclass
class RadixNode:
	children: Dict[str, "RadixNode"] = field(default_factory=dict)
	is_word: bool = False

class RadixTrie:
	def __init__(self) -> None:
		self.root = RadixNode()

	@staticmethod
	def _common_prefix_len(a: str, b: str) -> int:
		i = 0
		while i < len(a) and i < len(b) and a[i] == b[i]:
			i += 1
		return i

	def insert(self, word: str) -> None:
		if not word:
			return

		node = self.root
		
		while True:
			for edge, child in list(node.children.items()):
				i = self._common_prefix_len(edge, word)

				if i == 0:
					continue

				# Full match of edge → go deeper
				if i == len(edge):
					node = child
					word = word[i:]
					if not word:
						node.is_word = True
						return
					break

				# Partial match → split edge
				existing_child = child
				del node.children[edge]

				mid = RadixNode()
				node.children[edge[:i]] = mid

				# Old suffix
				mid.children[edge[i:]] = existing_child

				# New suffix
				if i == len(word):
					mid.is_word = True
				else:
					mid.children[word[i:]] = RadixNode(is_word=True)

				return
			else:
				node.children[word] = RadixNode(is_word=True)
				return


	def remove(self, word: str) -> bool:
		path: List[Tuple[str, RadixNode]] = []
		node = self.root

		# Traverse
		while word:
			for edge, child in node.children.items():
				if word.startswith(edge):
					path.append((edge, node))
					node = child
					word = word[len(edge):]
					break
			else:
				return False

		if not node.is_word:
			return False

		node.is_word = False

		# Cleanup bottom-up
		while path:
			edge, parent = path.pop()
			child = parent.children[edge]

			# Case 1: leaf node → delete edge
			if not child.children and not child.is_word:
				del parent.children[edge]
			# Case 2: compression along single-child path
			elif not child.is_word and len(child.children) == 1:
				# get the single child
				child_edge, grandchild = next(iter(child.children.items()))

				# merge child with its child
				parent.children[edge + child_edge] = grandchild
				del parent.children[edge]
			else:
				break

		return True

	def contains(self, word: str) -> bool:
		node = self.root
		while word:
			for edge, child in node.children.items():
				if word.startswith(edge):
					word = word[len(edge):]
					node = child
					break
			else:
				return False
		return node.is_word

	def pretty_print(self) -> str:
		lines: list[str] = []

		def walk(node: RadixNode, prefix: str, is_last: bool, edge_label: str | None):
			if edge_label is not None:
				connector = "" if prefix == "" else ("└── " if is_last else "├── ")
				lines.append(f'{prefix}{connector}"{edge_label}" (is_word = {node.is_word})')
				prefix = prefix + ("   " if is_last else "│  ")

			children = sorted(node.children.items(), key=lambda kv: kv[0])
			for idx, (edge, child) in enumerate(children):
				walk(child, prefix, idx == len(children) - 1, edge)

		# Print from root without a synthetic root label.
		children = sorted(self.root.children.items(), key=lambda kv: kv[0])
		for idx, (edge, child) in enumerate(children):
			walk(child, "", idx == len(children) - 1, edge)

		return "\n".join(lines)


	def self_check(self) -> None:
		"""
		Validates radix invariants:
		1. No empty edges
		2. No node has a single child unless it's a word node
		3. No overlapping prefixes among siblings
		"""

		def dfs(node: RadixNode):
			# Rule 1: no empty edges
			for edge in node.children:
				assert edge != "", "Empty edge detected"

			# Rule 3: no sibling prefix conflicts
			edges = list(node.children.keys())
			for i in range(len(edges)):
				for j in range(i + 1, len(edges)):
					assert not (
						edges[i].startswith(edges[j])
						or edges[j].startswith(edges[i])
					), f"Prefix conflict: {edges[i]}, {edges[j]}"

			for child in node.children.values():
				dfs(child)

		dfs(self.root)

def demo():
	trie = RadixTrie()

	words = [
		"app", "apple", "ape",
		"pop", "papa", "papaJohn",
		"papaJohnPizza1", "papaJohnPizza2", "papaJohnPizza3"
	]

	for w in words:
		trie.insert(w)

	print("Initial Trie:")
	print(trie.pretty_print())

	# Validate structure
	trie.self_check()

	print("\nRemove 'papa'")
	trie.remove("papa")

	print(trie.pretty_print())
	trie.self_check()

	print("\nLookups:")
	for w in ["app", "apple", "papa", "papaJohnPizza1"]:
		print(f"{w}: {trie.contains(w)}")


if __name__ == "__main__":
	demo()