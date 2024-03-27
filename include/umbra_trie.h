#include <tuple>
#include <cmath>
#include <atomic>

template<typename TUPLE_TYPE>
class Node {
public:
	TUPLE_TYPE data;
	Node *next;

	Node(TUPLE_TYPE data) {
		this->data = data;
		next = nullptr;
	}
};

template<typename TUPLE_TYPE>
class LinkedList {
public:
	Node<TUPLE_TYPE> *head;
	Node<TUPLE_TYPE> *tail;
	size_t size;
	void *up;  // Bucket

	LinkedList() {
		head = tail = nullptr;
		size = 0;
		up = nullptr;
	}

	~LinkedList() {
		while (head != nullptr) {
			Node<TUPLE_TYPE> *node = head;
			head = head->next;
			delete node;
		}
	}

	inline void insert(TUPLE_TYPE data) {
		Node<TUPLE_TYPE> *node = new Node<TUPLE_TYPE>(data);
		if (head == nullptr)
			head = tail = node;
		else {
			tail->next = node;
			tail = node;
		}
		++size;
	}

	inline TUPLE_TYPE pop() {
		Node<TUPLE_TYPE> *node = head;
		head = head->next;
		TUPLE_TYPE data = node->data;
		delete node;
		--size;
		return data;
	}
};

class Bucket {
public:
	size_t hash;
	void *down;  // HashTable* or LinkedList*

	Bucket() {
		hash = -1;
		down = nullptr;
	}
};

class HashTable {
public:
	size_t size;
	Bucket **buckets;
	uint32_t hash_factor;
	uint8_t shift;
	Bucket *up;

	HashTable(size_t size) {
		this->size = 1 << size_t(ceil(log2(size)));
		buckets = new Bucket *[this->size];
		for (size_t i = 0; i < this->size; ++i)
			buckets[i] = new Bucket();
		hash_factor = (rand() << 1) | 1;
		shift = 64 - log2(this->size);
		up = nullptr;
	}

	~HashTable() {
		for (size_t i = 0; i < size; ++i)
			delete buckets[i];
		delete[] buckets;
	}

	inline size_t hash(size_t key) {
		return (key * hash_factor) >> shift;
	}

	inline void insert(size_t key) {
		size_t h = hash(key);
		Bucket *b = buckets[h];
		b->hash = h;
	}

	inline Bucket *find(size_t key) {
		size_t h = hash(key);
		Bucket *b = buckets[h];
		return b;
	}
};

template<typename TUPLE_TYPE>
class Trie {
public:
	HashTable *table;

	Trie() {
		table = nullptr;
	}

	~Trie() {
		delete table;
	}

	HashTable *build(size_t idx, LinkedList<TUPLE_TYPE> *L) {
		HashTable *M = new HashTable(L->size * 1.25);

		while (L->head != nullptr) {
			auto t = L->pop();
			auto B = M->find(get<idx>(t));
			if (B->down == nullptr)
				B->down = new LinkedList<TUPLE_TYPE>();
			((LinkedList<TUPLE_TYPE> *) B->down)->insert(t);
			((LinkedList<TUPLE_TYPE> *) B->down)->up = B;
		}

		if (idx == std::tuple_size<TUPLE_TYPE>{} - 1) {
			table = M;
			return M;
		}

		auto idx_next = idx + 1;
		for (size_t i = 0; i < M->size; ++i) {  // TODO: iterator over only occupied buckets
			auto B = M->buckets[i];
			if (B->hash != -1) {
				LinkedList<TUPLE_TYPE> *L_next = B->down;
				HashTable *M_next = build(idx_next, L_next);
				B->down = M_next;
				M_next->up = B;
			}
		}

		return M;
	}
};