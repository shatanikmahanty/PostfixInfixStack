#include<iostream>
#include<fstream>
#include <string>

using namespace std;

template<class T>
class MyStack {
private:
    T *d;
    int top, size{};
public:
    bool push(T data);

    T getTop();

    T pop();

    explicit MyStack(int size) {
        d = new T[size];
        top = -1;
        this->size = size;
    }

//    void printStack();
};

template<class T>
T MyStack<T>::getTop(){
    return d[top];
}

template<class T>
bool MyStack<T>::push(T data) {
    if (top == size - 1) {
        cout << "\n Stack overflow! ";
        return false;
    }
    d[++top] = data;
    return true;
}

template<class T>
T MyStack<T>::pop() {
    if (top == -1) {
        cout << "\n Empty Stack!";
        return ' ';
    }
    return d[top--];
}

//template<class T>
//void MyStack<T>::printStack() {
//    if (top == -1) {
//        cout << "\n Empty stack! ";
//        return;
//    }
//    int i = top;
//    for (cout << "\nThe Stack : "; i > -1; i--) {
//        cout << d[i] << " ";
//    }
//    cout << endl;
//}

int calculatePrecedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string s) {
    MyStack<char> st(100);
    st.push('?');
    int l = s.length();
    string ns;
    for (int i = 0; i < l; i++) {

        //// If the scanned character is
        //// an operand, add it to output string.
        if (isalnum(s[i]))
            ns += s[i];

            //// If the scanned character is
            //// ‘(‘, push it to the stack.
        else if (s[i] == '(')

            st.push('(');

            //// If the scanned character is ‘)’,
            //// pop and to output string from the stack
            //// until an ‘(‘ is encountered.
        else if (s[i] == ')') {
            while (st.getTop() != '?' && st.getTop() != '(') {
                char c = st.getTop();
                st.pop();
                ns += c;
            }
            if (st.getTop() == '(') {
                st.pop();
            }
        }

            //If an operator is scanned
        else {
            while (st.getTop() != '?' && calculatePrecedence(s[i]) <=
                                         calculatePrecedence(st.getTop())) {
                char c = st.getTop();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }

    }

    // Pop all the remaining elements from the stack
    while (st.getTop() != '?') {
        char c = st.getTop();
        st.pop();
        ns += c;
    }

    return ns;

}


int main() {
    ifstream fin;

    string line;

    fin.open("infix.txt");

    if(fin.is_open()) {
        while (fin) {
            getline(fin,line);
            cout << infixToPostfix(line) << endl;
        }

        fin.close();

    }else{
        cout << "Error reading from file";
    }
    return 0;
}

