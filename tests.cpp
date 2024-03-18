#include <bits/stdc++.h>
#include "SegmentedDeque.h"

void tests() {
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

    SegmentedDeque<int> addition;
    addition.Append(1);
    test_deque = test_deque + addition;
    assert(test_deque.GetLength() == 19);

    test_deque.Append(-1);
    test_deque.Sort();
    assert(test_deque[0] == -1);

    test_deque.Clear();
    assert(test_deque.GetLength() == 0);
    assert(test_deque.Empty());
    
    cout << "Очередной успех" << endl;
}

int main(){
    tests();
    return 0;
}