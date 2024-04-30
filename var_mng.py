from typing import Tuple


class VariableManager:
	def __init__(self):
		self._trie_vars = dict()
		self._last_x_var = 0

	def trie_type(self, level_types: Tuple[str]):
		return f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}vector<int>{'>' * len(level_types)}"

	def trie_var(self, rel_name: str):
		if rel_name not in self._trie_vars.keys():
			self._trie_vars[rel_name] = f"{rel_name}_trie0"
		return self._trie_vars[rel_name]

	def next_trie_var(self, rel_name: str, inplace: bool = False):
		trie_var = self._trie_vars[rel_name]
		trie_level = int(trie_var[-1]) + 1
		next_level_trie = f"{rel_name}_trie{trie_level}"
		if inplace:
			self._trie_vars[rel_name] = next_level_trie
		return next_level_trie

	def x_var(self, idx: int):
		return f"x{idx}"

	def rel_col_var(self, rel_name: str, col: str):
		return f"{rel_name}_{col}"

	def offset_var(self, rel_name: str):
		return f"{rel_name}_off"

	def res_var(self):
		return "res"

	def attr_var(self, idx: int):
		return f"attr{idx}"
