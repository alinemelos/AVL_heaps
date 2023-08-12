#include <iostream>
#include <vector>

using namespace std;

class MyMinHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[parentIndex] > heap[index]) {
                swap(heap[parentIndex], heap[index]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) {
            return -1;
        }

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }

    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    int N;
    while (scanf("%d", &N) && N != 0) {
        MyMinHeap minHeap;

        for (int i = 0; i < N; ++i) {
            int num;
            scanf("%d", &num);
            minHeap.insert(num);
        }

        int totalCost = 0;
        while (!minHeap.isEmpty()) {
            int sum = minHeap.extractMin();
            if (!minHeap.isEmpty()) {
                sum += minHeap.extractMin();
                totalCost += sum;
                minHeap.insert(sum);
            }
        }

        printf("%d\n", totalCost);
    }

    return 0;
}
