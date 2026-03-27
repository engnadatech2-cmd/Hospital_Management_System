#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                break;
            }
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[largest] < heap[left]) {
                largest = left;
            }
            if (right < size && heap[largest] < heap[right]) {
                largest = right;
            }

            if (largest == index) {
                break;
            }
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Priority queue is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!empty()) {
            heapifyDown(0);
        }
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Priority queue is empty");
        }
        return heap[0];
    }
    
    // Extracted directly for saving to file purposes without destruction
    const std::vector<T>& getSequence() const {
        return heap;
    }
    
    // Reconstruct heap from a populated vector (used during loading)
    void buildHeap(const std::vector<T>& elements) {
        heap = elements;
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }
};

#endif
