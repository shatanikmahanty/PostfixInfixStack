#include<iostream>
#include<fstream>
#include <string>
#include <list>

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
T MyStack<T>::getTop() {
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
        return " ";
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

int calculatePrecedence(const string &c) {
    if (c == "^")
        return 5;
    else if (c == "*" || c == "/")
        return 4;
    else if (c == "+" || c == "-")
        return 3;
    else if (c == "&" || c == "|")
        return 2;
    else if (c == "&&" || c == "||" || c=="!")
        return 1;
    else if (c == "<" || c == ">" || c == "<=" || c == ">=")
        return 0;
    else
        return -1;
}

list<string> infixToPostfix(list<string> s) {
    MyStack<string> st(100);
    st.push("?");
    list<string> ns;

    list<string>::iterator it;
    for (it = s.begin(); it != s.end(); ++it) {

        if ((*it).size() == 1) {
            //// If the scanned character is
            //// an operand, add it to output string.
            if (isalnum((*it)[0])) {
                ns.push_back(*it);
            }
                //// If the scanned character is
                //// ‘(‘, push it to the stack.
            else if ((*it)[0] == '(') {
                st.push("(");
            }
                //// If the scanned character is ‘)’,
                //// pop and to output string from the stack
                //// until an ‘(‘ is encountered.
            else if ((*it)[0] == ')') {
                while (st.getTop() != "?" && st.getTop() != "(") {
                    string c = st.getTop();
                    st.pop();
                    string toPush;
                    toPush += c;
                    ns.push_back(toPush);
                }

                if (st.getTop() == "(") {
                    st.pop();
                }
            }
                ///If an operator is scanned
            else {
                while (st.getTop() != "?" && calculatePrecedence((*it)) <=
                                             calculatePrecedence(st.getTop())) {
                    string c = st.getTop();
                    st.pop();
                    string toPush;
                    toPush += c;
                    ns.push_back(toPush);
                }
                st.push(*it);
            }
        } else {
            if (isdigit((*it)[0])) {
                ns.push_back(*it);
            } else {
                while (st.getTop() != "?" && calculatePrecedence((*it)) <=
                                             calculatePrecedence(st.getTop())) {
                    string c = st.getTop();
                    st.pop();
                    string toPush;
                    toPush += c;
                    ns.push_back(toPush);
                }
                st.push(*it);
            }
        }


    }

    // Pop all the remaining elements from the stack
    while (st.getTop() != "?") {
        string c = st.getTop();
        st.pop();
        string toPush;
        toPush += c;
        ns.push_back(toPush);
    }

    return ns;

}

void showList(list<string> g, bool isResult) {
    list<string>::iterator it;

    ofstream myfile;
    myfile.open("output.txt",ios::app);

    for (it = g.begin(); it != g.end(); ++it) {
        if (isResult) {
            cout << *it << " ";
            myfile << *it << " ";
        }
        else
            cout << *it;
    }
    cout << '\n';
    myfile << "\n";
    myfile.close();}

list<string> parseOperatorsOperands(string infix) {
    list<string> infix_list;

    string number;
    for (int i = 0; i < infix.length();) {
        if (isalpha(infix[i])) {
            string letter;
            letter += infix[i];
            infix_list.push_back(letter);
            i++;
            continue;
        } else if (isdigit(infix[i])) {
            number += infix[i];
            i++;
            while (isdigit(infix[i]) || infix[i] == '.') {
                number += infix[i];
                i++;
            }
            infix_list.push_back(number);
            number = "";
            continue;
        } else if (infix[i] == '&') {
            infix_list.emplace_back("&&");
            i += 2;
            continue;
        } else if (infix[i] == '|') {
            infix_list.emplace_back("||");
            i += 2;
            continue;
        } else {

            string op;
            op += infix[i];
            infix_list.push_back(op);
            i++;
            continue;
        }
    }

    cout << "\nGiven infix : ";
    showList(infix_list, false);
    return infix_list;
}

int main() {
    ifstream fin;

    string line;
    ofstream myfile;
    myfile.open("output.txt");
    myfile << "";
    myfile.close();

    fin.open("infix.txt");

    if (fin.is_open()) {
        while (fin) {
            getline(fin, line);
            if (!line.empty()) {
                list<string> exp = parseOperatorsOperands(line);
                list<string> converted = infixToPostfix(exp);
                cout << "Result : ";
                showList(converted, true);
                cout << endl;
            }
        }

        fin.close();

    } else {
        cout << "Error reading from file";
    }
    return 0;
}

