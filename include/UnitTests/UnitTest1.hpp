#ifndef CUCCA_UNITTESTS_UNITTEST1_HPP
#define CUCCA_UNITTESTS_UNITTEST1_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 1


#include <Cucca/Core/Component.hpp>
#include <Cucca/Core/Node.hpp>
#include <Cucca/Core/Visitor.hpp>

#include <iostream>


struct TestComponent1 : public Cucca::Component {
    int a_;
};

struct TestComponent2 : public Cucca::Component {
    int b_;
};

struct TestComponent3 : public Cucca::Component {
    double c_;
};

CUCCA_VISITOR(TestVisitor1, TestComponent1) {
public:
    void nodeEnter(Cucca::Node* node, TestComponent1* component);
    void nodeExit(Cucca::Node* node, TestComponent1* component);
};

CUCCA_VISITOR(TestVisitor2, TestComponent2) {
public:
    void nodeEnter(Cucca::Node* node, TestComponent2* component);
    void nodeExit(Cucca::Node* node, TestComponent2* component);
};

CUCCA_VISITOR(TestVisitor3, TestComponent2) {
public:
    void nodeEnter(Cucca::Node* node, TestComponent2* component);
    void nodeExit(Cucca::Node* node, TestComponent2* component);
};

CUCCA_VISITOR(TestVisitor4, TestComponent1, TestComponent3, TestComponent2) {
public:
    void nodeEnter(Cucca::Node* node, TestComponent1* component);
    void nodeExit(Cucca::Node* node, TestComponent1* component);

    void nodeEnter(Cucca::Node* node, TestComponent2* component);
    void nodeExit(Cucca::Node* node, TestComponent2* component);

    void nodeEnter(Cucca::Node* node, TestComponent3* component);
    void nodeExit(Cucca::Node* node, TestComponent3* component);
};


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST1_HPP
