#pragma once

#include <array>
#include <iostream>
#include <vector>

template<typename T, size_t N>
class small_vector_array {
	std::array<T, N> arr_;
	std::size_t size_{0};

public:
	size_t size() const { return size_; }

	void push_back(const T &value) {
		if (size_ < N) {
			arr_[size_] = value;
		} else {
			throw std::runtime_error("small_vector_array: size exceeds capacity");
		}
		++size_;
	}

	T &operator[](size_t pos) {
		if (pos < size_) {
			return arr_[pos];
		} else {
			throw std::runtime_error("small_vector_array: out of bounds");
		}
	}
};

template<typename T>
class small_vector_tuple {
	std::tuple<T, T, T, T> tpl_;
	std::size_t size_{0};

public:
	size_t size() const { return size_; }

	void push_back(const T &value) {
		if (size_ == 0) {
			std::get<0>(tpl_) = value;
		} else if (size_ == 1) {
			std::get<1>(tpl_) = value;
		} else if (size_ == 2) {
			std::get<2>(tpl_) = value;
		} else if (size_ == 3) {
			std::get<3>(tpl_) = value;
		} else {
			throw std::runtime_error("small_vector_array: size exceeds capacity");
		}
		++size_;
	}

	T &operator[](size_t pos) {
		if (pos == 0) {
			return std::get<0>(tpl_);
		} else if (pos == 1) {
			return std::get<1>(tpl_);
		} else if (pos == 2) {
			return std::get<2>(tpl_);
		} else if (pos == 3) {
			return std::get<3>(tpl_);
		} else {
			throw std::runtime_error("small_vector_array: out of bounds");
		}
	}
};

template<typename T>
class small_vector_fields {
	T fld0_;
	T fld1_;
	T fld2_;
	T fld3_;
	std::size_t size_{0};

public:
	size_t size() const { return size_; }

	void push_back(const T &value) {
		if (size_ == 0) {
			fld0_ = value;
		} else if (size_ == 1) {
			fld1_ = value;
		} else if (size_ == 2) {
			fld2_ = value;
		} else if (size_ == 3) {
			fld3_ = value;
		} else {
			throw std::runtime_error("small_vector_array: size exceeds capacity");
		}
		++size_;
	}

	T &operator[](size_t pos) {
		if (pos == 0) {
			return fld0_;
		} else if (pos == 1) {
			return fld1_;
		} else if (pos == 2) {
			return fld2_;
		} else if (pos == 3) {
			return fld3_;
		} else {
			throw std::runtime_error("small_vector_array: out of bounds");
		}
	}
};

template<typename T, size_t N>
class small_vector_vecptr {
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
