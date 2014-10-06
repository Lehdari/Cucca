#include <iostream>

#include "../include/core/Component.hpp"
#include "../include/core/Node.hpp"


//Test app


struct TestComponent1 : public Component {
    int a_;
};

struct TestComponent2 : public Component {
    int b_;
};

VISITOR(TestVisitor1, TestComponent1) {
public:
    void visit(TestComponent1* component) {
        std::cout << "TestVisitor1/TestComponent1 visitor visit, component.a_ = " << component->a_ << std::endl;
    }
};

VISITOR(TestVisitor2, TestComponent2) {
public:
    void visit(TestComponent2* component) {
        std::cout << "TestVisitor2/TestComponent2 visitor visit, component.b_ = " << component->b_ << std::endl;
    }
};

VISITOR(TestVisitor3, TestComponent2) {
public:
    void visit(TestComponent2* component) {
        std::cout << "TestVisitor3/TestComponent2 visitor visit, component.b_*2 = " << component->b_*2 << std::endl;
    }
};


int main(void) {
    Node n;
    TestComponent1 c1;
    c1.a_ = 10;
    TestComponent2 c2;
    c2.b_ = 20;
    n.addComponent(&c1);
    n.addComponent(&c2);

    Node n2;
    TestComponent1 c3;
    c3.a_ = 40;
    TestComponent1 c4;
    c4.a_ = 80;
    TestComponent2 c5;
    c5.b_ = 160;
    n2.addComponent(&c3);
    n2.addComponent(&c4);
    n2.addComponent(&c5);

    TestVisitor1 v1;
    TestVisitor2 v2;
    TestVisitor3 v3;

    n.visitAll(v1);
    n.visitAll(v2);
    n.visitAll(v3);
    n2.visitAll(v1);
    n2.visitAll(v2);
    n2.visitAll(v3);

    return 0;
}
