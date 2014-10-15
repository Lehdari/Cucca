#include <iostream>

#include "../include/Core/Component.hpp"
#include "../include/Core/Node.hpp"
#include "../include/Core/Event.hpp"


//Test app


struct TestComponent1 : public Component {
    int a_;
};

struct TestComponent2 : public Component {
    int b_;
};

VISITOR(TestVisitor1, TestComponent1) {
public:
    void nodeEnter(Node* node, TestComponent1* component) {
        std::cout << "TestVisitor1/TestComponent1 nodeEnter(), component.a_ = " << component->a_ << std::endl;
    }

    void nodeExit(Node* node, TestComponent1* component) {
        std::cout << "TestVisitor1/TestComponent1 nodeExit()" << std::endl;
    }
};

VISITOR(TestVisitor2, TestComponent2) {
public:
    void nodeEnter(Node* node, TestComponent2* component) {
        std::cout << "TestVisitor2/TestComponent2 nodeEnter(), component.b_ = " << component->b_ << std::endl;
    }

    void nodeExit(Node* node, TestComponent2* component) {
        std::cout << "TestVisitor2/TestComponent2 nodeExit()" << std::endl;
    }
};

VISITOR(TestVisitor3, TestComponent2) {
public:
    void nodeEnter(Node* node, TestComponent2* component) {
        std::cout << "TestVisitor3/TestComponent2 nodeEnter(), component.b_*2 = " << component->b_*2 << std::endl;
    }

    void nodeExit(Node* node, TestComponent2* component) {
        std::cout << "TestVisitor3/TestComponent2 nodeExit()" << std::endl;
    }
};


struct TestEvent1 {
    unsigned a_;
};

struct TestEvent2 {
    unsigned b_;
};


int main(void) {
    Node n1;
    TestComponent1 c1;
    c1.a_ = 10;
    TestComponent2 c2;
    c2.b_ = 20;
    n1.addComponent(&c1);
    n1.addComponent(&c2);

    Node n2;
    TestComponent1 c3;
    c3.a_ = 30;
    TestComponent2 c4;
    c4.b_ = 40;
    n2.addComponent(&c3);
    n2.addComponent(&c4);
    n1.addChild(n2);

    Node n3;
    n1.addChild(n3);

    Node n4;
    TestComponent1 c5;
    c5.a_ = 50;
    TestComponent1 c6;
    c6.a_ = 60;
    TestComponent2 c7;
    c7.b_ = 70;
    n4.addComponent(&c5);
    n4.addComponent(&c6);
    n4.addComponent(&c7);
    n3.addChild(n4);

    Node n5;
    TestComponent2 c8;
    c8.b_ = 80;
    n5.addComponent(&c8);

    n3.addChild(n5);

    TestVisitor1 v1;
    TestVisitor2 v2;
    TestVisitor3 v3;

    n1.accept(v1);
    n1.accept(v2);
    n1.accept(v3);

    n2.accept(v1);
    n3.accept(v1);


    Event<TestEvent1> e1();
    Event<TestEvent2> e2();

    return 0;
}
