//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    // Inserts new index into the heap and restores order of the MinHeap by using upheap
    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }
    // Removes the smallest weighted index and returns it
    // Restores the MinHeap order by using downheap
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            return -1;
        }
        int minIndex = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return minIndex;
    }
    // Restores the MinHeap order by moving the element upward until its smaller
    // than the parents weight
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[parent]] > weightArr[data[pos]]) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }
    // Restores the MinHeap order by moving the element downward until
    // it is larger than one of the children's weight
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left = 2 * pos + 1;
            int right = left + 1;

            int smallest = pos;
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
                smallest = left;
            }
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }
            if (smallest != pos) {
                swap(data[pos], data[smallest]);
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif