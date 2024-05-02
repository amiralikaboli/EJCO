from typing import Tuple


class VariableManager:
	def __init__(self):
		self._trie_vars = dict()
		self._last_x_var = 0

	def trie_type(self, level_types: Tuple[str]):
		return f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}vector<int>{'>' * len(level_types)}"

	def trie_var(self, rel: str):
		if rel not in self._trie_vars.keys():
			self._trie_vars[rel] = f"{rel}_trie0"
		return self._trie_vars[rel]

	def next_trie_var(self, rel: str, inplace: bool = False):
		trie_var = self._trie_vars[rel]
		trie_level = int(trie_var[-1]) + 1
		next_level_trie = f"{rel}_trie{trie_level}"
		if inplace:
			self._trie_vars[rel] = next_level_trie
		return next_level_trie

	def x_var(self, idx: int):
		return f"x{idx}"

	def rel_col_var(self, rel: str, col: str):
		return f"{rel}_{col}"

	def offset_var(self, rel: str):
		return f"{rel}_off"

	def res_var(self):
		return "res"

	def attr_var(self, idx: int):
		return f"attr{idx}"
