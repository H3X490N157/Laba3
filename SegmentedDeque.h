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

    void Sort() {
        vector<T> cur(size_);
        for (int i = 0; i < size_; ++i) {
            cur[i] = resourse[(start_ + i) % capacity_];
        }
        sort(cur.begin(), cur.end());
        for (int i = 0; i < size_; ++i) {
            resourse[i] = cur[i];
            start_ = 0;
            end_ = size_;
        }
    }

    SegmentedDeque<T>& operator+(SegmentedDeque<T>& other) {
        other.NewCapacity(other.capacity_);
        int newstart_ = size_;
        int newend_ = size_ + other.size_;
        NewCapacity(capacity_ + other.capacity_);
        for (int i = newstart_; i < newend_; i++){
            resourse[i] = other[i - newstart_];
        }
        size_ += other.size_;
        return *this;
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

    /*&&SegmentedDeque<T> GetSubDeck(int first, int last){
        NewCapacity(capacity_);
        if (first < 0 || last > size_ || first > last){
            throw out_of_range("Некорректный индекс");
        }
        
    }*/
};



