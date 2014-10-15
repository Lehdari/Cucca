#ifndef CUCCA_UNITTESTS_UNITTEST1_HPP
#define CUCCA_UNITTESTS_UNITTEST1_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 1


#include "../../include/Core/Component.hpp"
#include "../../include/Core/Node.hpp"
#include "../../include/Core/Visitor.hpp"

#include <iostream>


struct TestComponent1 : public Component {
    int a_;
};

struct TestComponent2 : public Component {
    int b_;
};

VISITOR(TestVisitor1, TestComponent1) {
public:
    void nodeEnter(Node* node, TestComponent1* component);
    void nodeExit(Node* node, TestComponent1* component);
};

VISITOR(TestVisitor2, TestComponent2) {
public:
    void nodeEnter(Node* node, TestComponent2* component);
    void nodeExit(Node* node, TestComponent2* component);
};

VISITOR(TestVisitor3, TestComponent2) {
public:
    void nodeEnter(Node* node, TestComponent2* component);
    void nodeExit(Node* node, TestComponent2* component);
};


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST1_HPP
