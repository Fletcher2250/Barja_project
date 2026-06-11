#ifndef STACK_H_
#define STACK_H_

#include <stdexcept>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& val, Node* nxt = nullptr) : data(val), next(nxt) {}
};

template <typename T>
class MyStack {
public:
	MyStack() : head_(nullptr), count_(0) {}
	~MyStack() { Clear(); }

	MyStack(const MyStack&) = delete;
	MyStack& operator = (const MyStack&) = delete;

	void Push(const T& val) {
		// Новая бочка становится верхней (head_), а её "next" указывает на старую верхнюю бочку
		head_ = new Node<T>(val, head_);
		count_++;
	}

	void Pop() {
		if (IsEmpty()) {
			throw std::underflow_error("Stack underflow");
		}
		Node<T>* temp = head_;
		head_ = head_->next; // Сдвигаем указатель на бочку ниже
		delete temp;         // Удаляем старую верхнюю бочку из памяти
		count_--;
	}

	const T& Top() const {
		if (IsEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		return head_->data;
	}

	bool IsEmpty() const { return head_ == nullptr; }
	size_t Size() const { return count_; }

	void Clear() {
		while (head_ != nullptr) {
			Node<T>* temp = head_;
			head_ = head_->next;
			delete temp;
			count_--;
		}
	}

private:
	Node<T>* head_;
	size_t count_;
};

#endif