#pragma once

#include <array>
#include <iostream>
#include <vector>

template<typename T, size_t N>
class smallvec {
	std::array<T, N> stack_;
	std::vector<T> *heap_;
	std::size_t size_{0};

public:
	size_t size() const { return size_; }

	void push_back(const T &value) {
		if (size_ < N) {
			stack_[size_] = value;
		} else {
			if (size_ == N) {
				heap_ = new std::vector<T>(stack_.begin(), stack_.end());
			}
			heap_->push_back(value);
		}
		++size_;
	}

	T &operator[](size_t pos) {
		if (size_ <= N) {
			return stack_[pos];
		} else {
			return heap_->at(pos);
		}
	}

	class iterator {
		T *ptr_;

	public:
		iterator(T *ptr) : ptr_(ptr) {}

		iterator &operator++() {
			++ptr_;
			return *this;
		}

		T &operator*() { return *ptr_; }

		bool operator==(const iterator &rhs) { return ptr_ == rhs.ptr_; }

		bool operator!=(const iterator &rhs) { return ptr_ != rhs.ptr_; }
	};

	class const_iterator {
		T *ptr_;

	public:
		const_iterator(T *ptr) : ptr_(ptr) {}

		const_iterator &operator++() {
			++ptr_;
			return *this;
		}

		const T &operator*() { return *ptr_; }

		bool operator==(const const_iterator &rhs) { return ptr_ == rhs.ptr_; }

		bool operator!=(const const_iterator &rhs) { return ptr_ != rhs.ptr_; }
	};

	iterator begin() {
		if (size_ <= N) {
			return iterator(stack_.data());
		} else {
			return iterator(heap_->data());
		}
	}

	iterator end() {
		if (size_ <= N) {
			return iterator(stack_.data() + size_);
		} else {
			return iterator(heap_->data() + size_);
		}
	}

	const_iterator begin() const {
		if (size_ <= N) {
			return const_iterator(stack_.data());
		} else {
			return const_iterator(heap_->data());
		}
	}

	const_iterator end() const {
		if (size_ <= N) {
			return const_iterator(stack_.data() + size_);
		} else {
			return const_iterator(heap_->data() + size_);
		}
	}
};
