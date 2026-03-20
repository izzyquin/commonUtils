import unittest

from hash_map import HashMap


class BadHash:
    """Forces collisions by returning constant hash."""

    __slots__ = ("value",)

    def __init__(self, value: int) -> None:
        self.value = value

    def __hash__(self) -> int:
        return 0

    def __eq__(self, other: object) -> bool:
        return isinstance(other, BadHash) and self.value == other.value

    def __repr__(self) -> str:
        return f"BadHash({self.value})"


class HashMapTests(unittest.TestCase):
    def test_empty(self) -> None:
        hm: HashMap[str, int] = HashMap()
        self.assertEqual(len(hm), 0)
        self.assertFalse(hm)
        self.assertNotIn("x", hm)
        self.assertEqual(dict(hm), {})
        self.assertEqual(list(hm), [])

    def test_set_get_overwrite(self) -> None:
        hm: HashMap[str, str] = HashMap(initial_capacity=2)
        hm.set("a", "1")
        self.assertEqual(hm.get("a"), "1")
        hm.set("a", "2")
        self.assertEqual(hm.get("a"), "2")
        self.assertEqual(len(hm), 1)
        self.assertEqual(hm["a"], "2")

    def test_get_default_and_contains(self) -> None:
        hm: HashMap[str, int] = HashMap()
        self.assertIsNone(hm.get("missing"))
        self.assertEqual(hm.get("missing", 123), 123)
        hm["k"] = 7
        self.assertIn("k", hm)
        self.assertNotIn("nope", hm)

    def test_delete_and_pop(self) -> None:
        hm: HashMap[str, int] = HashMap()
        hm["a"] = 1
        hm["b"] = 2
        self.assertTrue(hm.delete("a"))
        self.assertFalse(hm.delete("a"))
        self.assertEqual(hm.pop("b"), 2)
        with self.assertRaises(KeyError):
            _ = hm.pop("b")
        self.assertEqual(hm.pop("b", 9), 9)

    def test_delitem(self) -> None:
        hm: HashMap[str, int] = HashMap()
        hm["a"] = 1
        del hm["a"]
        with self.assertRaises(KeyError):
            _ = hm["a"]
        with self.assertRaises(KeyError):
            del hm["a"]

    def test_iteration_and_dict_conversion(self) -> None:
        hm: HashMap[str, int] = HashMap()
        hm["x"] = 1
        hm["y"] = 2

        # Iteration yields keys (like dict).
        keys = set(iter(hm))
        self.assertEqual(keys, {"x", "y"})

        # `dict(hm)` uses keys iteration + __getitem__.
        d = dict(hm)
        self.assertEqual(d, {"x": 1, "y": 2})

        # Items/keys/values all consistent.
        self.assertEqual(set(hm.keys()), {"x", "y"})
        self.assertEqual(set(hm.values()), {1, 2})
        self.assertEqual(set(hm.items()), {("x", 1), ("y", 2)})

    def test_update_pairs(self) -> None:
        hm: HashMap[int, int] = HashMap()
        hm.update([(1, 10), (2, 20)])
        self.assertEqual(dict(hm), {1: 10, 2: 20})

    def test_resizing_preserves_values(self) -> None:
        hm: HashMap[int, int] = HashMap(initial_capacity=2)
        for i in range(200):
            hm[i] = i * 3
        self.assertEqual(len(hm), 200)
        for i in range(200):
            self.assertEqual(hm[i], i * 3)

    def test_heavy_collisions(self) -> None:
        hm: HashMap[BadHash, int] = HashMap(initial_capacity=2)
        keys = [BadHash(i) for i in range(50)]
        for i, k in enumerate(keys):
            hm[k] = i
        self.assertEqual(len(hm), 50)
        for i, k in enumerate(keys):
            self.assertEqual(hm[k], i)

        # Delete a few from the middle and ensure the rest still accessible.
        for k in keys[10:30]:
            del hm[k]
        self.assertEqual(len(hm), 30)
        for i, k in enumerate(keys[:10]):
            self.assertEqual(hm[k], i)
        for i, k in enumerate(keys[30:], start=30):
            self.assertEqual(hm[k], i)

    def test_init_validation(self) -> None:
        with self.assertRaises(ValueError):
            HashMap(initial_capacity=0)


if __name__ == "__main__":
    unittest.main()

