#include <bits/stdc++.h>
#include "sequence.h"
using namespace std;

//Из дополнений - проверка на пустоту деки, циклический сегментированный (ринг) буффер, PopBack и PopFront



template<typename T>
class SegmentedDeque: public Sequence<T> {
    
private:
    T* resourse = nullptr;
    int size_, capacity_, start_, end_;

    void NewCapacity(int newCapacity){
        T* newDeque = new T[newCapacity];
        for (int i = 0; i < size_; i++){
            newDeque[i] = resourse[(start_ + i) % capacity_];
        }
        delete[] resourse;
        resourse = newDeque;
        start_ = 0;
        end_ = size_;
        capacity_ = newCapacity;
    }
    
    
public:
    SegmentedDeque(): resourse(new T[2]) , size_(0), capacity_(2) , start_(0), end_(0){}

    SegmentedDeque(int size, const T& value): resourse(new T[size * 2]) , size_(size), capacity_(size * 2) , start_(0), end_(size){
        for (int i = 0; i < size; i++){
            resourse[i] = value;
        }
    }

    SegmentedDeque(const SegmentedDeque& other): resourse(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_), start_(other.start_), end_(other.size_){
        for (int i = 0; i < size_; i++){
            resourse[i] = other.resourse[i];
        }
    }

    ~SegmentedDeque() override{
        delete[] resourse;
    }
        
    T& GetFirst() override {
        return resourse[start_];
    }
    
    T& GetLast() override {
        return resourse[(end_ + capacity_ - 1) % capacity_];
    }

    int GetLength() override {
        return size_;
    }

    bool Empty() {
        return !size_;
    }

    T& Get(int index) override {
        if (index < 0 or index > capacity_){
            throw out_of_range("Некорректный индекс");
        }
        return resourse[(start_ + index ) % capacity_];
    }
        
    T& operator [](int index) override {
        return resourse[(start_ + index ) % capacity_];
    }

    void Append(T value) override {
        if (size_ == capacity_){
            NewCapacity(capacity_ * 2);
        }
        resourse[end_] = value;
        end_++;
        size_++;
        end_ %= capacity_;
    }

    void Prepend(T value) override{
        if (size_ == capacity_){
            NewCapacity(capacity_ * 2);}
        start_ = (start_ + capacity_ - 1) % capacity_;
        resourse[start_] = value;
        size_++;
    }

    void InsertAt(T value, int index) override{
        if (index < 0){
            index += size_;
        }
        
        if (index > size_ or index < 0) {
            throw out_of_range("Некорректный индекс");
        }
        if (size_ == capacity_) {
            NewCapacity(capacity_ * 2);
        }
        
        if (index == 0) {
            Prepend(value);
        }
        else if (index == size_) {
            Append(value);
        } 
        else {
            for (int i = size_; i > index; --i) {
                resourse[(start_ + i) % capacity_] = resourse[(start_ + i - 1) % capacity_];
            }
            resourse[(start_ + index) % capacity_] = value;
            start_ = (start_ + capacity_ - 1) % capacity_;
            end_ = (end_ + 1) % capacity_;
            ++size_;
        }
}

    void PopBack(){
        size_--;
        end_ = (end_ + capacity_ - 1) % capacity_;
    }
        
    void PopFront(){
        size_--;
        start_ = (start_ + 1) % capacity_;
    }

    void Clear(){
        size_ = 0;
        start_ = 0;
        end_ = 0;
    }
};

int main() {
    SegmentedDeque<int> test_deque;

    assert(test_deque.GetLength() == 0);
    assert(test_deque.Empty());

    test_deque.Append(1);
    assert(test_deque.GetLength() == 1);
    assert(!test_deque.Empty());
    assert(test_deque[0] == 1);
    assert(test_deque.GetFirst() == 1);
    assert(test_deque.GetLast() == 1);

    test_deque.PopFront();
    assert(test_deque.Empty());

    for (int i = 0; i < 20; ++i) {
        if (i % 2) {
            test_deque.Append(i);
        } 
        else {
            test_deque.Prepend(i);
        }
    }

    assert(test_deque.GetLength() == 20);

    const int beforeBack = test_deque[test_deque.GetLength() - 2];
    const int afterFront = test_deque[1];
    for (int i = 0; i < test_deque.GetLength(); ++i) {
        cout << test_deque[i] << " ";
    }
    cout << endl;

    test_deque.PopBack();
    test_deque.PopFront();

    assert(test_deque.GetLast() == beforeBack);
    assert(test_deque.GetFirst() == afterFront);

    string s;
    for (int i = 0; i < test_deque.GetLength(); ++i) {
        s += to_string(test_deque[i]) + " ";
    }

    for (int i = 0; i < test_deque.GetLength(); ++i) {
        test_deque.Append(test_deque.GetFirst());
        test_deque.PopFront();
    }

    string s2;
    for (int i = 0; i < test_deque.GetLength(); ++i) {
        s2 += to_string(test_deque[i]) + " ";
    }

    assert(s == s2);
    assert(test_deque.GetLength() == 18);
    test_deque.Clear();
    assert(test_deque.GetLength() == 0);
    assert(test_deque.Empty());
    return 0;
}


