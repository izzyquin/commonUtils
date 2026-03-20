import unittest

from lfu_cache import LFU

# -----------------------------
# Tests (append-only)
# -----------------------------
import unittest


class TestLFU(unittest.TestCase):
	def test_get_missing_returns_minus_one(self):
		c = LFU(2)
		self.assertEqual(c.get(123), None)

	def test_put_then_get(self):
		c = LFU(2)
		c.put(1, 10)
		self.assertEqual(c.get(1), 10)

	def test_leetcode_460_example(self):
		# Standard LFU behavior:
		# - evict least frequently used
		# - if tie, evict least recently used among min freq
		c = LFU(2)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), 1)   # freq(1)=2, freq(2)=1
		c.put(3, 3)                     # evicts key 2
		self.assertEqual(c.get(2), None)
		self.assertEqual(c.get(3), 3)   # freq(3)=2
		c.put(4, 4)                     # tie freq=2 between 1 and 3; evict LRU => key 1
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(3), 3)
		self.assertEqual(c.get(4), 4)

	def test_capacity_one_eviction(self):
		c = LFU(1)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(2), 2)

	def test_update_existing_key_counts_as_use(self):
		# Updating an existing key should behave like an access:
		# key's value updated and its frequency increases.
		c = LFU(2)
		c.put(1, 1)
		c.put(2, 2)
		c.put(1, 10)        # update key 1 => freq(1) should increase
		c.put(3, 3)         # should evict key 2 (lower freq)
		self.assertEqual(c.get(2), None)
		self.assertEqual(c.get(1), 10)
		self.assertEqual(c.get(3), 3)

	def test_lru_tie_break_within_same_frequency(self):
		# Both keys end up with same frequency; eviction should drop the least recently used.
		c = LFU(2)
		c.put(1, 1)
		c.put(2, 2)
		self.assertEqual(c.get(1), 1)  # now freq(1)=2, freq(2)=1
		self.assertEqual(c.get(2), 2)  # now freq(1)=2, freq(2)=2; key 2 is most recently used among freq=2
		c.put(3, 3)                    # min freq is 2; evict LRU among {1,2} => key 1
		self.assertEqual(c.get(1), None)
		self.assertEqual(c.get(2), 2)
		self.assertEqual(c.get(3), 3)

	def test_capacity_zero_noops(self):
		# Many LFU specs define capacity=0 as "store nothing".
		c = LFU(0)
		c.put(1, 1)
		self.assertEqual(c.get(1), None)


if __name__ == "__main__":
	unittest.main()
