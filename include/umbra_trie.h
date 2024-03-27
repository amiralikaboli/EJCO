#include <tuple>
#include <cmath>
#include <atomic>

template<typename T>
class Node {
public:
	T data;
	Node *next;

	Node(T data) {
		this->data = data;
		next = nullptr;
	}
};

template<typename T>
class LinkedList {
public:
	Node<T> *head;
	Node<T> *tail;
	size_t size;
	void *up;  // Bucket

	LinkedList() {
		head = tail = nullptr;
		size = 0;
		up = nullptr;
	}

	~LinkedList() {
		while (head != nullptr) {
			Node<T> *node = head;
			head = head->next;
			delete node;
		}
	}

	inline void insert(T data) {
		Node<T> *node = new Node<T>(data);
		if (head == nullptr)
			head = tail = node;
		else {
			tail->next = node;
			tail = node;
		}
		++size;
	}

	inline T pop() {
		Node<T> *node = head;
		head = head->next;
		T data = node->data;
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

	inline bool is_empty() {
		return hash == -1;
	}
};

class HashTable {
public:
	size_t length;
	uint64_t hash_factor;
	uint8_t shift;
	Bucket **buckets;
	Bucket *up;
	LinkedList<size_t> *occupied;

	HashTable(size_t length) {
		this->length = 1 << size_t(ceil(log2(length)));
		hash_factor = (rand() << 1) | 1;
		shift = 64 - log2(this->length);
		buckets = new Bucket *[this->length];
		for (size_t i = 0; i < this->length; ++i)
			buckets[i] = new Bucket();
		up = nullptr;
		occupied = new LinkedList<size_t>();
	}

	~HashTable() {
		for (size_t i = 0; i < length; ++i)
			delete buckets[i];
		delete[] buckets;
	}

	inline size_t hash(size_t key) {
		return (key * hash_factor) >> shift;
	}

	inline void insert(size_t key) {
		size_t h = hash(key);
		Bucket *b = buckets[h];
		if (b->is_empty()) {
			b->hash = h;
			occupied->insert(h);
		}
	}

	inline Bucket *find(size_t key) {
		size_t h = hash(key);
		Bucket *b = buckets[h];
		return b;
	}

	inline size_t size() {
		return occupied->size;
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
		auto it = M->occupied->head;
		while (it != nullptr) {
			auto B = M->buckets[it->data];
			if (B->hash != -1) {
				LinkedList<TUPLE_TYPE> *L_next = B->down;
				HashTable *M_next = build(idx_next, L_next);
				B->down = M_next;
				M_next->up = B;
			}

			it = it->next;
		}

		return M;
	}
};