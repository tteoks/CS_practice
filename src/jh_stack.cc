#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

#define MAX_ELEMENT 128

template <class T>
class jh_stack {

private:
    int top = -1;
    T *stack_ptr = NULL;

public:
    jh_stack () {
        stack_ptr = new T;
    }

    ~jh_stack() {
        top = -1;
        delete stack_ptr;
    }

   void print_stack() {
       int idx;
       cout << "##### Stack Status" << endl;

        for (idx = top; idx >= 0; idx--) {
            cout << right << stack_ptr[idx] << endl;
        }
        cout << endl;

   }
   int push(T data) {
       if (top - 1 > MAX_ELEMENT) {
           cout << "ERROR PUSH: Too many element in Stack!" << endl;
           return -1;
       }

       stack_ptr[++top] = data;
       return 0;
   }
   T pop() {
       if (top < 0) {
           cout << "Stack have no element!" << endl;
           return -1;
       }

       T data = stack_ptr[top];
       stack_ptr[top--] = 0x00;

       return data;
   }
};


int main(int argc, char **argv)
{
    cout << "Hello World" << endl;
    jh_stack<int> int_stack;

    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    int_stack.push(4);

    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;

/*
{
    double test = 332.322;
    cout << "test: " << to_string(test) << endl;
    cout << "length: " << to_string(test).size() << endl;
}
*/
    cout << "Bye!" << endl;
    return 0;
}


