#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
using namespace std;

class Test {
public:
    // دالة بسيطة لطباعة رسالة الترحيب
    void welcomeMessage() {
        cout << "====================================" << endl;
        cout << "   Welcome to the Hospital System!  " << endl;
        cout << "      Start small. Ship something.  " << endl;
        cout << "====================================" << endl;
    }
};

#endif