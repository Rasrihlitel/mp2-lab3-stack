#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

template<typename T>
class Container {
private:
	int size;
	int capacity;
	T* pMem;
public:
	Container(int _capacity = 3) {
		if (_capacity <= 0) throw "Нельзя создать контейнер нулевого и отрицательного размеров";
		capacity = _capacity;
		size = 0;
		pMem = new T[capacity];
	}
	Container(const Container<T>& obj) {
		capacity = obj.capacity;
		size = obj.size;
		pMem = new T[capacity];
		for (int i = 0; i < size; i++) {
			pMem[i] = obj.pMem[i];
		}
	}
	Container(Container<T>&& obj) {
		capacity = obj.capacity;
		size = obj.size;
		pMem = obj.pMem;
		obj.size = 0;
		obj.capacity = 0;
		obj.pMem = nullptr;
	}
	~Container() { if (pMem != nullptr) delete[] pMem; }
	Container<T>& operator=(const Container<T>& obj) {
		if (this != &obj) {
			if (capacity != obj.capacity) {
				delete[] pMem;
				capacity = obj.capacity;
				pMem = new T[capacity];
			}
			size = obj.size;
			for (int i = 0; i < size; i++) {
				pMem[i] = obj.pMem[i];
			}
		}
		return *this;
	}
	Container<T>& operator=(Container<T>&& obj) {
		if (this != &obj) {
			delete[] pMem;
			capacity = obj.capacity;
			size = obj.size;
			pMem = obj.pMem;
			obj.capacity = 0;
			obj.size = 0;
			obj.pMem = nullptr;
		}
		return *this;
	}
	bool operator==(const Container<T>& obj) const {
		if (size != obj.size || capacity != obj.capacity) return false;
		for (int i = 0; i < size; i++) {
			if (pMem[i] != obj.pMem[i]) return false;
		}
		return true;
	}
	bool operator!=(const Container<T>& obj) const { return !(*this == obj); }
	void push_back(const T& val) {
		if (size == capacity) {
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++) { temp[i] = pMem[i]; }
			capacity *= 2;
			delete[] pMem;
			pMem = new T[capacity];
			for (int i = 0; i < size; i++) { pMem[i] = temp[i]; }
			delete[] temp;
		}
		pMem[size] = val;
		++size;
	}
	void clear() {
		delete[] pMem;
		pMem = new T[capacity];
		size = 0;
	}
};

#endif //CONTAINER_H