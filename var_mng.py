from typing import Tuple


class VariableManager:
	def __init__(self):
		self._trie_vars = dict()
		self._last_x_var = 0

	@staticmethod
	def trie_type(level_types: Tuple[str]):
		return f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}vector<int>{'>' * len(level_types)}"

	@staticmethod
	def trie_bool_type(level_types: Tuple[str]):
		return f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}bool{'>' * len(level_types)}"

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

	@staticmethod
	def x_var(idx: int):
		return f"x{idx}"

	@staticmethod
	def rel_col_var(rel: str, col: str):
		return f"{rel}_{col}"

	@staticmethod
	def offset_var(rel: str):
		return f"{rel}_off"

	@staticmethod
	def attr_var(idx: int):
		return f"attr{idx}"

	def mn_var(self, rel: str, col: str):
		return f"mn_{self.rel_col_var(rel, col)}"

	@staticmethod
	def load_func(rel: str):
		return f"load_{rel}"

	@staticmethod
	def build_func():
		return "build_trie"

	@staticmethod
	def build_bool_func():
		return "build_trie_bool"

	@staticmethod
	def build_ordered_func():
		return "build_trie_ordered"
