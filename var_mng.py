from typing import Tuple

from consts import Templates


class VariableManager:
	def __init__(self):
		self._trie_vars = dict()
		self._last_x_var = 0

	def clear(self):
		self._trie_vars.clear()
		self._last_x_var = 0

	@staticmethod
	def trie_def(level_types: Tuple[str], value_type: str = "smallvecdict<int, 4>"):
		return f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}{value_type}{'>' * len(level_types)}"

	@staticmethod
	def _trie_var(rel: str, idx: int):
		return f"{rel}_{Templates.TrieVar.value}{idx}"

	def trie_var(self, rel: str, idx: int = None):
		if rel not in self._trie_vars.keys():
			self._trie_vars[rel] = self._trie_var(rel, 0)
		return self._trie_vars[rel]

	def next_trie_var(self, rel: str, inplace: bool = False):
		self.trie_var(rel)
		trie_var = self._trie_vars[rel]
		trie_level = int(trie_var[-1]) + 1
		next_level_trie = self._trie_var(rel, trie_level)
		if inplace:
			self._trie_vars[rel] = next_level_trie
		return next_level_trie

	def tuples_var(self, rel: str):
		return self.trie_var(rel) if rel in self._trie_vars.keys() else f"range({rel}.size)"

	@staticmethod
	def x_var(idx: int):
		return f"{Templates.XVar.value}{idx}"

	@staticmethod
	def rel_col_var(rel: str, col: str):
		return f"{rel}_{col}"

	@staticmethod
	def off_var(rel: str):
		return f"{rel}_{Templates.OffVar.value}"

	@staticmethod
	def tuple_var(rel: str):
		return f"{rel}_{Templates.TupleVar.value}"

	@staticmethod
	def attr_var(idx: int):
		return f"{Templates.AttrVar.value}{idx}"

	@staticmethod
	def mn_rel_col_var(rel: str, col: str):
		return f"{Templates.MinVar.value}_{VariableManager.rel_col_var(rel, col)}"

	@staticmethod
	def mn_rel_var(rel: str):
		return f"{Templates.MinVar.value}_{rel}"

	@staticmethod
	def load_func(rel: str):
		return f"{Templates.LoadFunc.value}_{rel}"

	@staticmethod
	def build_func():
		return Templates.BuildFunc.value

	@staticmethod
	def interm_rel(idx: int):
		return f"{Templates.IntermRel.value}{idx}"

	@staticmethod
	def is_interm_rel(rel: str):
		return rel.startswith(Templates.IntermRel.value)

	@staticmethod
	def interm_col(idx: int):
		return f"{Templates.IntermCol.value}{idx}"

	@staticmethod
	def root_rel():
		return Templates.RootRel.value

	@staticmethod
	def is_root_rel(rel: str):
		return rel == Templates.RootRel.value

	@staticmethod
	def cnt_var():
		return Templates.CntVar.value

	def offsets_var(self, rel: str, it=False):
		var = f"{rel}_{Templates.OffsetsVar.value}"
		if it:
			return self.trie_var(rel) if rel in self._trie_vars.keys() else var
		return var
