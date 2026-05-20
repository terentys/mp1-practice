#include <iostream>
#include <string>

#include "container.hpp"

int main() {
    Container<int> containerInt1(10, 3);
    for (int i = 0; i < 3; i++) {
       containerInt1.addElement(5);
    }
    containerInt1.addElement(2);
    for (int i = 0; i < 3; i++) {
        containerInt1.addElement(7);
    }

    std::cout << containerInt1.getCount() << std::endl;
    for (int i = 0; i < containerInt1.getCount(); i++) {
        std::cout << containerInt1[i] << " ";
    }
    std::cout << std::endl;

    Container<int> containerInt2 = containerInt1;
    containerInt2.addElement(3, 3);

    for (int i = 0; i < containerInt2.getCount(); i++) {
        std::cout << containerInt2[i] << " ";
    }
    std::cout << std::endl;

    containerInt2.removeAt(4);

    for (int i = 0; i < containerInt2.getCount(); i++) {
        std::cout << containerInt2[i] << " ";
    }
    std::cout << std::endl;

    containerInt2.removeElement(7);

    for (int i = 0; i < containerInt2.getCount(); i++) {
        std::cout << containerInt2[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 5; i++) {
        containerInt2.addElement(9, 1);
    }

    std::cout << "\n" << containerInt2.getSize() << std::endl;
    for (int i = 0; i < containerInt2.getCount(); i++) {
        std::cout << containerInt2[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < containerInt1.getCount(); i++) {
        std::cout << containerInt1[i] << " ";
    }
    std::cout << std::endl;

    containerInt1 = containerInt2;

    for (int i = 0; i < containerInt1.getCount(); i++) {
        std::cout << containerInt1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    Container<std::string*> containerPtrsStr1(5);
    for (int i = 0; i < 2; i++) {
        containerPtrsStr1.addElement(new std::string("meow"));
    }
    std::string* strGav = new std::string("gav");
    containerPtrsStr1.addElement(strGav);
    for (int i = 0; i < 2; i++) {
        containerPtrsStr1.addElement(new std::string("woof"));
    }

    std::cout << containerPtrsStr1.getCount() << std::endl;
    for (int i = 0; i < containerPtrsStr1.getCount(); i++) {
        std::cout << *(containerPtrsStr1[i]) << " ";
    }
    std::cout << std::endl;
    std::cout << containerPtrsStr1.findElement("gav") << std::endl;

    containerPtrsStr1.removeAt(1);
    for (int i = 0; i < containerPtrsStr1.getCount(); i++) {
        std::cout << *containerPtrsStr1[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 2; i++) {
        containerPtrsStr1.addElement(new std::string("quack"));
    }

    std::cout << containerPtrsStr1.getSize() << std::endl;
    for (int i = 0; i < containerPtrsStr1.getCount(); i++) {
        std::cout << *containerPtrsStr1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    Container<std::string*> containerPtrsStr2 = containerPtrsStr1;
    containerPtrsStr2.removeAt(5);

    for (int i = 0; i < containerPtrsStr1.getCount(); i++) {
        std::cout << *containerPtrsStr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < containerPtrsStr2.getCount(); i++) {
        std::cout << *containerPtrsStr2[i] << " ";
    }
    std::cout << std::endl;

    containerPtrsStr1 = containerPtrsStr2;
    containerPtrsStr2.removeAt(0);

    for (int i = 0; i < containerPtrsStr1.getCount(); i++) {
        std::cout << *containerPtrsStr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < containerPtrsStr2.getCount(); i++) {
        std::cout << *containerPtrsStr2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}