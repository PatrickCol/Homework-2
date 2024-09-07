#include <iostream>
#include "CircularDoublyLinkedList.cpp"
#include "DoublyLinkedList.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    ListaDoblementeEnlazada<int> C;
    C.push_back(3);
    C.push_back(33);
    C.push_back(2);
    C.push_back(12);
    C.push_back(4);
    C.print(); std::cout<<'\n';

    C.reverse();
    C.print();

    return 0;
}
