#!/usr/bin/env python3

from __future__ import annotations

from dataclasses import dataclass
from collections.abc import Iterable as AbcIterable
from collections.abc import Iterator as AbcIterator
from collections.abc import MutableMapping
from typing import Generic, List, Optional, Tuple, TypeVar, overload

K = TypeVar("K")
V = TypeVar("V")


@dataclass(frozen=True)
class _Entry(Generic[K, V]):
    key: K
    value: V


class _Missing:
    __slots__ = ()

    def __repr__(self) -> str:
        return "MISSING"


_MISSING = _Missing()


class HashMap(MutableMapping[K, V], Generic[K, V]):
    """
    A small, hash map implementation using separate chaining.

    Notes:
    - Amortized O(1) inserts/gets/deletes with resizing.
    - Supports any hashable key type.
    - Keeps only one value per key (dict-like semantics).
    """

    __slots__ = ("_buckets", "_size", "_capacity")

    def __init__(self, *, initial_capacity: int = 16) -> None:
        if initial_capacity <= 0:
            raise ValueError("initial_capacity must be > 0")

        capacity = self._next_power_of_two(initial_capacity)
        self._buckets: List[List[_Entry[K, V]]] = [[] for _ in range(capacity)]
        self._size = 0
        self._capacity = capacity

    @staticmethod
    def _next_power_of_two(n: int) -> int:
        # Ensures good bucket distribution with bit masking.
        p = 1
        while p < n:
            p <<= 1
        return p

    def __len__(self) -> int:
        return self._size

    def __bool__(self) -> bool:
        return self._size != 0

    def __contains__(self, key: K) -> bool:
        return self.get(key, default=_MISSING) is not _MISSING

    def __iter__(self) -> AbcIterator[K]:
        # Required by Mapping / MutableMapping; enables `dict(hash_map)`.
        for bucket in self._buckets:
            for entry in bucket:
                yield entry.key

    def _bucket_index(self, key: K) -> int:
        return hash(key) & (len(self._buckets) - 1)

    def _maybe_resize_for_insert(self) -> None:
        if (self._size + 1) > self._capacity:
            self._rehash(len(self._buckets) * 2)
        if self._size < self._capacity * 0.25:
            self._rehash(self._capacity // 2)

    def _rehash(self, new_capacity: int) -> None:
        new_capacity = self._next_power_of_two(new_capacity)
        new_buckets: List[List[_Entry[K, V]]] = [[] for _ in range(new_capacity)]

        for bucket in self._buckets:
            for entry in bucket:
                idx = hash(entry.key) & (new_capacity - 1)
                new_buckets[idx].append(entry)

        self._buckets = new_buckets
        self._capacity = new_capacity

    def set(self, key: K, value: V) -> None:
        """Insert/update a key with a value."""
        self._maybe_resize_for_insert()
        idx = self._bucket_index(key)
        bucket = self._buckets[idx]

        for i, entry in enumerate(bucket):
            if entry.key == key:
                bucket[i] = _Entry(key, value)
                return

        bucket.append(_Entry(key, value))
        self._size += 1

    @overload
    def get(self, key: K, default: None = None) -> V | None: ...

    @overload
    def get(self, key: K, default: V) -> V: ...

    @overload
    def get(self, key: K, default: object) -> V | object: ...

    def get(self, key: K, default: object = None) -> V | object:
        """Get value for key; return default if missing (like dict.get)."""
        idx = self._bucket_index(key)
        for entry in self._buckets[idx]:
            if entry.key == key:
                return entry.value
        return default

    def pop(self, key: K, default: V | object = _MISSING) -> V:
        """Remove key and return its value. If missing, return default or raise KeyError."""
        idx = self._bucket_index(key)
        bucket = self._buckets[idx]

        for i, entry in enumerate(bucket):
            if entry.key == key:
                bucket.pop(i)
                self._size -= 1
                return entry.value

        if default is _MISSING:
            raise KeyError(key)
        return default  # type: ignore[return-value]

    def delete(self, key: K) -> bool:
        """Delete key if present. Returns True if deleted, False if missing."""
        try:
            self.pop(key)
            return True
        except KeyError:
            return False

    def __getitem__(self, key: K) -> V:
        value = self.get(key, default=_MISSING)
        if value is _MISSING:
            raise KeyError(key)
        return value  # type: ignore[return-value]

    def __setitem__(self, key: K, value: V) -> None:
        self.set(key, value)

    def __delitem__(self, key: K) -> None:
        self.pop(key)

    def items(self) -> AbcIterator[Tuple[K, V]]:
        for bucket in self._buckets:
            for entry in bucket:
                yield (entry.key, entry.value)

    def keys(self) -> AbcIterator[K]:
        for k, _ in self.items():
            yield k

    def values(self) -> AbcIterator[V]:
        for _, v in self.items():
            yield v

    def update(self, pairs: AbcIterable[Tuple[K, V]]) -> None:
        for k, v in pairs:
            self.set(k, v)

    def __repr__(self) -> str:
        pairs = ", ".join(f"{k!r}: {v!r}" for k, v in self.items())
        return f"{self.__class__.__name__}({{{pairs}}})"


def _demo() -> None:
    hm: HashMap[str, str] = HashMap(initial_capacity=8)
    hm.set("1", "1.0")
    hm.set("1", "1.1")
    hm.set("1", "1.3")
    hm.set("2", "2.3")

    print(hm)
    print("len:", len(hm))
    print("get('1'):", hm.get("1"))
    print("delete('1'):", hm.delete("1"))
    print(hm)


def _self_check() -> None:
    hm: HashMap[int, int] = HashMap(initial_capacity=2)
    for i in range(1000):
        hm.set(i, i * 2)
    assert len(hm) == 1000
    for i in range(1000):
        assert hm.get(i) == i * 2
    for i in range(0, 1000, 3):
        assert hm.delete(i) is True
    for i in range(0, 1000, 3):
        assert hm.get(i, default=None) is None


if __name__ == "__main__":
    _self_check()
    _demo()


