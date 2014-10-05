#include <iostream>

#include "../include/core/Node.hpp"
#include "../include/core/Component.hpp"


//Test app


struct TestComponent1 : public ComponentBase {
    int a_;
};

struct TestComponent2 : public ComponentBase {
    int b_;
};

VISIT(TestComponent1) {
    std::cout << "TestComponent1 visitor visit, component.a_ = " << component->a_ << std::endl;
}

VISIT(TestComponent2) {
    std::cout << "TestComponent2 visitor visit, component.b_ = " << component->b_ << std::endl;
}

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

    n.visitAll<TestComponent1>();
    n.visitAll<TestComponent2>();
    n2.visitAll<TestComponent1>();
    n2.visitAll<TestComponent2>();

    return 0;
}
