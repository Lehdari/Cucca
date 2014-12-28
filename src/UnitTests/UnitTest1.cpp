#include "../../include/UnitTests/UnitTest1.hpp"


#if CURRENT_TEST == 1


using namespace Cucca;


void TestVisitor1::nodeEnter(Node* node, TestComponent1* component) {
    std::cout << "TestVisitor1/TestComponent1 " << component << " nodeEnter(), component.a_ = " << component->a_ << std::endl;
}

void TestVisitor1::nodeExit(Node* node, TestComponent1* component) {
    std::cout << "TestVisitor1/TestComponent1 " << component << " nodeExit()" << std::endl;
}

void TestVisitor2::nodeEnter(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor2/TestComponent2 " << component << " nodeEnter(), component.b_ = " << component->b_ << std::endl;
}

void TestVisitor2::nodeExit(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor2/TestComponent2 " << component << " nodeExit()" << std::endl;
}

void TestVisitor3::nodeEnter(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor3/TestComponent2 " << component << " nodeEnter(), component.b_*2 = " << component->b_*2 << std::endl;
}

void TestVisitor3::nodeExit(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor3/TestComponent2 " << component << " nodeExit()" << std::endl;
}

void TestVisitor4::nodeEnter(Node* node, TestComponent1* component) {
    std::cout << "TestVisitor4/TestComponent1 " << component << " nodeEnter(), component.a_*2 = " << component->a_*2 << std::endl;
}

void TestVisitor4::nodeExit(Node* node, TestComponent1* component) {
    std::cout << "TestVisitor4/TestComponent1 " << component << " nodeExit()" << std::endl;
}

void TestVisitor4::nodeEnter(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor4/TestComponent2 " << component << " nodeEnter(), component.b_*2 = " << component->b_*2 << std::endl;
}

void TestVisitor4::nodeExit(Node* node, TestComponent2* component) {
    std::cout << "TestVisitor4/TestComponent2 " << component << " nodeExit()" << std::endl;
}

void TestVisitor4::nodeEnter(Node* node, TestComponent3* component) {
    std::cout << "TestVisitor4/TestComponent3 " << component << " nodeEnter(), component.c_*2 = " << component->c_*2 << std::endl;
}

void TestVisitor4::nodeExit(Node* node, TestComponent3* component) {
    std::cout << "TestVisitor4/TestComponent3 " << component << " nodeExit()" << std::endl;
}



int unitTest(void) {
    Node n1;
    TestComponent1 c1;
    c1.a_ = 10;
    TestComponent2 c2;
    c2.b_ = 20;
    n1.addComponent(std::move(c1));
    n1.addComponent(std::move(c2));

    Node n2;
    TestComponent1 c3;
    c3.a_ = 30;
    TestComponent2 c4;
    c4.b_ = 40;
    TestComponent3 c9;
    c9.c_ = 3.14;
    n2.addComponent(std::move(c3));
    n2.addComponent(std::move(c4));
    n2.addComponent(std::move(c9));

    Node n3;

    Node n4;
    TestComponent1 c5;
    c5.a_ = 50;
    TestComponent1 c6;
    c6.a_ = 60;
    TestComponent2 c7;
    c7.b_ = 70;
    TestComponent3 c10;
    c10.c_ = 8.6;
    n4.addComponent(std::move(c5));
    n4.addComponent(std::move(c6));
    n4.addComponent(std::move(c7));
    n4.addComponent(std::move(c10));

    Node n5;
    TestComponent2 c8;
    c8.b_ = 80;
    n5.addComponent(std::move(c8));

    n3.addChild(std::move(n5));
    n3.addChild(std::move(n4));
    n1.addChild(std::move(n3));
    n1.addChild(std::move(n2));


    TestVisitor1 v1;
    TestVisitor2 v2;
    TestVisitor3 v3;
    TestVisitor4 v4;

    n1.accept(v1); std::cout << std::endl;
    n1.accept(v2); std::cout << std::endl;
    n1.accept(v3); std::cout << std::endl;
    n1.accept(v4); std::cout << std::endl;

    return 0;
}

#endif
