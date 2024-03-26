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

	LinkedList() {
		head = tail = nullptr;
		size = 0;
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
		table = new Bucket *[this->size];
		for (size_t i = 0; i < this->size; ++i)
			buckets[i] = new Bucket();
		hash_factor = (rand() << 1) | 1;
		shift = 64 - log2(this->size);
		up = nullptr;
	}

	inline void set_up(Bucket *up) {
		this->up = up;
		up->down = this;
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

class Trie {
public:
	HashTable *table;

	Trie(size_t size) {
		table = new HashTable(size);
	}

	template<typename T>
	HashTable *build(size_t idx, LinkedList<T> *L) {
		// TODO: IF idx < # of attributes
		HashTable *M = new HashTable(L->size * 1.25);

		while (L->head != nullptr) {
			auto t = L->pop();
			auto B = M->find(t);  // TODO: t needs a pi function on it
			if (B->down == nullptr)
				B->down = new LinkedList<T>();
			((LinkedList<T> *) B->down)->insert(t);
		}

		auto i_next = ...;  // TODO: achieve i_next from somewhere
		for (size_t i = 0; i < M->size; ++i) {
			auto B = M->buckets[i];
			if (B->hash != -1) {
				LinkedList<T> *L_next = B->down;
				HashTable *M_next = build(i_next, L_next);
				B->down = M_next;  // TODO: can be set_up function
			}
		}

		return M;
	}
};