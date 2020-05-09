#ifndef SUDOKU_SOLVER_STACK_H
#define SUDOKU_SOLVER_STACK_H

#include <mutex>
#include <condition_variable>
#include <stack>
#include <thread>


template <class T>
class Stack {
public:
    void push(const T& value);
    T pop();

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::stack<T> stk;
};


template<class T>
void Stack<T>::push(const T& value) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.notify_all();
    stk.push(value);
}

template<class T>
T Stack<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    while(stk.empty()) {
        cv.wait(lock);
    }
    T result = stk.top();
    stk.pop();
    return result;
}


#endif //SUDOKU_SOLVER_STACK_H
