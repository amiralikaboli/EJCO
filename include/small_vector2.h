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
};
