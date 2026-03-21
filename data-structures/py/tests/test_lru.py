import unittest

from lru_cache import LRU

# -----------------------------
# Tests (append-only)
# -----------------------------
import unittest


class TestLRU(unittest.TestCase):
	def test_get_missing_returns_none(self):
		c = LRU(2)
		self.assertEqual(c.get(123), None)

	def test_put_then_get(self):
		c = LRU(2)
		c.put(1, 10)
		self.assertEqual(c.get(1), 10)

	def test_simple_evictation_example(self):
		# Standard LRU behavior: evict least recently used
		c = LRU(2)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), 1)
		c.put(3, 3)                     # evicts key 2
		self.assertEqual(c.get(2), None)
		self.assertEqual(c.get(3), 3)
		c.put(4, 4)                     # evict LRU => key 1
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(3), 3)
		self.assertEqual(c.get(4), 4)

	def test_capacity_one_eviction(self):
		c = LRU(1)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(2), 2)

	def test_update_existing_key_counts_as_use(self):
		c = LRU(2)
		c.put(1, 1)
		c.put(2, 2)
		c.put(1, 10)        # update key 1 => the value is changed to 10
		c.put(3, 3)         # should evict key 2
		self.assertEqual(c.get(2), None)
		self.assertEqual(c.get(1), 10)
		self.assertEqual(c.get(3), 3)

	def test_lru_recency_change_by_get(self):
		# Both keys end up with same frequency; eviction should drop the least recently used.
		c = LRU(2)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), 1)
		self.assertEqual(c.get(2), 2)
		c.put(3, 3)
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(2), 2)
		self.assertEqual(c.get(3), 3)

	def test_capacity_zero_noops(self):
		# Many LRU specs define capacity=0 as "store nothing".
		c = LRU(0)
		c.put(1, 1)
		self.assertEqual(c.get(1), None)


if __name__ == "__main__":
	unittest.main()
