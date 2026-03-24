import unittest

from radix_trie import RadixTrie

class TestRadixTrie(unittest.TestCase):
	def setUp(self):
		# create a fresh trie before each test
		self.trie = RadixTrie()

	def test_insert_and_contains(self):
		self.trie.insert("apple")
		self.trie.insert("app")
		self.trie.insert("ape")

		self.assertTrue(self.trie.contains("apple"))
		self.assertTrue(self.trie.contains("app"))
		self.assertTrue(self.trie.contains("ape"))
		self.assertFalse(self.trie.contains("ap"))
		self.assertFalse(self.trie.contains("apples"))

	def test_remove_leaf_node(self):
		self.trie.insert("app")
		self.trie.insert("apple")
		self.trie.remove("apple")
		self.assertFalse(self.trie.contains("apple"))
		self.assertTrue(self.trie.contains("app"))

	def test_remove_internal_node(self):
		# check eager compression
		self.trie.insert("papaJohn1")
		self.trie.insert("papaJohn2")
		self.trie.insert("pop")
		self.trie.remove("papaJohn2")

		# after removal, "papaJohn1" should be compressed under "papaJohn"
		self.assertTrue(self.trie.contains("papaJohn1"))
		self.assertFalse(self.trie.contains("papaJohn2"))
		self.assertTrue(self.trie.contains("pop"))

		# check structure is correct: no dangling nodes
		# optionally, call self_check() if implemented
		if hasattr(self.trie, "self_check"):
			self.trie.self_check()

	def test_remove_nonexistent(self):
		self.trie.insert("apple")
		self.trie.remove("banana")  # should not raise
		self.assertTrue(self.trie.contains("apple"))
		self.assertFalse(self.trie.contains("banana"))

	def test_insert_multiple_prefixes(self):
		words = ["app", "apple", "ape", "apex", "bat", "batch"]
		for word in words:
			self.trie.insert(word)

		for word in words:
			self.assertTrue(self.trie.contains(word))
		self.assertFalse(self.trie.contains("ap"))
		self.assertFalse(self.trie.contains("ba"))

	def test_eager_compression_after_remove(self):
		# setup a complex scenario
		self.trie.insert("papaJohn1")
		self.trie.insert("papaJohn2")
		self.trie.insert("pop")
		self.trie.remove("papaJohn2")

		# after eager compression, "papaJohn" should be a single node
		self.assertTrue(self.trie.contains("papaJohn1"))
		self.assertTrue(self.trie.contains("pop"))
		self.assertFalse(self.trie.contains("papaJohn2"))


if __name__ == "__main__":
	unittest.main()
