#pragma once


template<typename T, int n>
class priority_queue{
    const int maxSize = 4*n;
    T data[4*n];
    int last;

    void heapfy() {
        int id = 1;
        while(id*2 + 1 < maxSize){
            int men = id*2;
            if(data[id*2] > data[id*2 + 1]) ++men;
            if(data[id] > data[men]) {
                swap(data[id], data[men]);
                id = men;
            }
            else if(data[id] > data[men^1]){
                swap(data[id], data[men]);
                id = men;
            }
            else break;
        }
    }
    void push(T element) {
        int id = last;
        data[last++] = element;
        while(id>1){
            if(data[id] < data[id/2]){
                swap(data[id],data[id/2]);
                id /= 2;
            }
            else break;
        }
    }
    void pop() {
        swap(data[1], data[last]);
        this->heapfy();
    }
    T front() {return data[1]; }
    T peek(){
        T f = this->front();
        this->pop();
        return f;
    }
    
};
