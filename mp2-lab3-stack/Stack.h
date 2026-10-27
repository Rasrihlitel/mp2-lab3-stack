#pragma once
#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack {
private:
	int topId;
	int size;
	T* pMem;
public:
	Stack(int _size = 10) {
		if (_size <= 0) throw "Стек отрицательного размера";
		size = _size;
		topId = -1;
		pMem = new T[size];
	}
	Stack(const Stack<T>& obj) {
		size = obj.size;
		topId = obj.topId;
		pMem = new T[size];
		for (int i = 0; i < topId; i++) {
			pMem[i] = obj.pMem[i];
		}
	}
	Stack(Stack<T>&& obj) noexcept {
		size = obj.size;
		topId = obj.topId;
		pMem = obj.pMem;
		obj.size = 0;
		obj.topId = 0;
		obj.pMem = nullptr;
	}
	~Stack() { delete[] pMem; }
	Stack<T>& operator=(const Stack<T>& obj) {
		if (this != &obj) {
			if (size != obj.size) {
				delete[] pMem;
				size = obj.size;
				topId = obj.topId;
				pMem = new T[size];
			}
			for (int i = 0; i < topId; i++) {
				pMem[i] = obj.pMem[i];
			}
		}
		return *this;
	}
	Stack<T>& operator=(Stack<T>&& obj) {
		if (this != &obj) {
			delete[] pMem;
			size = obj.size;
			topId = obj.topId;
			pMem = obj.pMem;
			obj.size = 0;
			obj.topId = 0;
			obj.pMem = nullptr;
		}
		return *this;
	}
	bool IsFull() { return topId == size - 1; }
	bool IsEmpty() { return topId == -1; }
	void push(const T& el) {
		if (IsFull()) throw "Стек полный";
		pMem[++topId] = el;
	}
	T pop() {
		if (IsEmpty()) throw "Стек пустой";
		return pMem[topId--];
	}

};

#endif //STACK_H