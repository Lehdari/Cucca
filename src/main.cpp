#include <iostream>


template<typename T>
class Visitor {
public:
    friend class Node;

private:
    void visit(T& component) {
        std::cout << "Base visitor visit" << std::endl;
    }
};

class Node {
public:
    template<typename T>
    void acceptVisitor(Visitor<T> visitor) {
        visitor.visit(getComponent<T>());
    }

    template<typename T>
    T& getComponent(void) {
        static T component;
        return component;
    }
};


//Test app


struct TestComponent1 {
    int a_;
};

struct TestComponent2 {
    int b_;
};

template<>
void Visitor<TestComponent1>::visit(TestComponent1& component) {
    std::cout << "TestComponent1 visitor visit, component.a_ = " << component.a_ << std::endl;
}

template<>
void Visitor<TestComponent2>::visit(TestComponent2& component) {
    std::cout << "TestComponent2 visitor visit, component.b_ = " << component.b_ << std::endl;
}

int main(void) {
    Node n;
    Visitor<TestComponent1> v1;
    Visitor<TestComponent2> v2;

    n.getComponent<TestComponent1>().a_ = 10;
    n.acceptVisitor(v1);

    n.getComponent<TestComponent1>().a_ += 10;
    n.acceptVisitor(v1);

    n.getComponent<TestComponent2>().b_ = 100;
    n.acceptVisitor(v2);

    return 0;
}
