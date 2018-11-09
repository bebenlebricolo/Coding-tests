// Simple test to create interaction between two classes (exactly identical in this case, but
// i wanted to have 2 different classes for this test. 
// Class A thows a ping to B, which returns a fixed value, then result is beeing printed on the console.
// Communication is handled via pointers.

#include "stdafx.h"
#include <iostream>

using namespace std;
class B;

class A {
public: 
	short akn(void);
	void pingB(B* b);
	A* getPointer(void);
};

class B {
public: 
	short akn(void);
	void pingA(A *a);
	B* getPointer(void);
};

short A::akn() {
	return 1;
}

void A::pingB(B* b) {
	cout << "Ping b : " << b->akn() << endl;
}

A* A::getPointer(void) {
	return this;
}

short B::akn() {
	return 2;
}

void B::pingA(A *a)
{
	cout << "Ping a : " << a->akn() << endl;
}

B* B::getPointer(void) {
	return this;
}



int main()
{
	A a;
	B b;
	a.pingB(b.getPointer());
	b.pingA(a.getPointer());
	cin.ignore();
	
    return 0;
}

