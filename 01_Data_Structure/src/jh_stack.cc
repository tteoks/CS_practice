#include <iostream>
#include <typeinfo>
#include <string>
#include <iomanip>


using namespace std;

#define MAX_ELEMENT 128

template <class T>
class jh_stack {

private:
    int top = -1;
    T *stack_ptr = NULL;

    int search_longest_length() {
        int i = 0;
        int max = 0;
        string str_var;

        for (; i < top; i++) {
            str_var = to_string(stack_ptr[i]);
            if (max < str_var.size()) {
                max = str_var.size();
            }
        }

        return max;
    }

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
       int max_width = search_longest_length();

       cout << "### Stack Status" << endl;

        cout << left << setw(3) << "idx"  << "|"
             << setw(max_width) << "element" << endl;
        for (idx = top; idx >= 0; idx--) {
            cout << left << setw(3) << idx  << "|"
                 << setw(max_width) << to_string(stack_ptr[idx]) << endl;
        }
        cout << endl;
   }

   bool isEmpty() {
     if (top == -1) 
       return true;
     else
       return false;
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
       if (isEmpty() == true) {
           cout << "Stack have no element!" << endl;
           return -1;
       }

       T data = stack_ptr[top];
       stack_ptr[top--] = 0x00;

       return data;
   }

   T peek() {
     if (isEmpty() == true) {
       cout << "Stack have no element!" << endl;
       return -1;
     }

     T data = stack_ptr[top];

     return data;
   }

};

void check_INT() {
    jh_stack<int> int_stack;

    cout << "PUSH INT: 1" << endl;
    int_stack.push(1);
    cout << "PUSH INT: 2" << endl;
    int_stack.push(2);
    cout << "PUSH INT: -1" << endl;
    int_stack.push(-1);
    cout << "PUSH INT: 4" << endl;
    int_stack.push(4);

    int_stack.print_stack();

    cout << "isEmpty: " << int_stack.isEmpty() << endl;
    cout << "TOP: " << int_stack.peek() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "isEmpty: " << int_stack.isEmpty() << endl;
}

void check_DOUBLE() {
    jh_stack<double> double_stack;

    cout << "PUSH DOUBLE: 1" << endl;
    double_stack.push(1);
    cout << "PUSH DOUBLE: 1.00" << endl;
    double_stack.push(1.00);
    cout << "PUSH DOUBLE: -1.93" << endl;
    double_stack.push(-1.93);
    cout << "PUSH DOUBLE: 10.93000009" << endl;
    double_stack.push(10.93000009);

    double_stack.print_stack();
    cout << "isEmpty: " <<double_stack.isEmpty() << endl;
    cout << "TOP: " << double_stack.peek() << endl;
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;

    cout << "isEmpty: " <<double_stack.isEmpty() << endl;
}

int main(int argc, char **argv)
{
    cout << "###### Hello World" << endl;
    check_INT();

    cout << endl  << endl;
    check_DOUBLE();

    cout << "###### Bye!" << endl;
    return 0;
}
