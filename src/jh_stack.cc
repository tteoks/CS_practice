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

       cout << "##### Stack Status" << endl;

        cout << left << setw(3) << "idx"  << "|"
             << setw(max_width) << "element" << endl;
        for (idx = top; idx >= 0; idx--) {
            cout << left << setw(3) << idx  << "|"
                 << setw(max_width) << to_string(stack_ptr[idx]) << endl;
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


void check_INT() {
    jh_stack<int> int_stack;

    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    int_stack.push(4);

    int_stack.print_stack();

    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
    cout << "POP: " << int_stack.pop() << endl;
}

void check_DOUBLE() {
    jh_stack<double> double_stack;
    double_stack.push(1);
    double_stack.push(1.00);
    double_stack.push(-1.93);
    double_stack.push(10.93000009);

    double_stack.print_stack();
    
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;
    cout << "POP: " << double_stack.pop() << endl;

}

int main(int argc, char **argv)
{
    cout << "Hello World" << endl;
    check_INT();

    cout << endl  << endl;
    check_DOUBLE();

    cout << "Bye!" << endl;
    return 0;
}
