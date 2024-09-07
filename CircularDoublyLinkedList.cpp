#include <iostream>

template<typename T>
struct CDLLNode {
    T data;
    CDLLNode *next;
    CDLLNode *prev;
};

template<typename T>
class CircularDoublyLinkedList {
    CDLLNode<T> *head = nullptr;
    CDLLNode<T> *tail = nullptr;
public:
    T front() const {
        if (head == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return head->data;
        }
    }

    T &front() {
        if (head == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return head->data;
        }
    }

    T back() const {
        if (tail == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return tail->data;
        }
    }

    T &back() {
        if (tail == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return tail->data;
        }
    }

    void push_front(T value) {
        CDLLNode<T> *nodo = new CDLLNode<T>;
        nodo->data = value;
        if (head == nullptr) {
            head = nodo;
            head->next = head;
            head->prev = head;
            tail = head;
            return;
        }

        nodo->next = head;
        nodo->prev = tail;
        tail->next = nodo;
        head->prev = nodo;
        head = nodo;
    }

    void push_back(T value) {
        CDLLNode<T> *nodo = new CDLLNode<T>;
        nodo->data = value;
        if (tail == nullptr) {
            tail = nodo;
            tail->next = tail;
            tail->prev = tail;
            head = tail;
            return;
        }

        nodo->next = head;
        nodo->prev = tail;
        tail->next = nodo;
        head->prev = nodo;
        tail = nodo;
    }

    T pop_front() {
        if (head == nullptr) {
            throw std::runtime_error("La lista esta vacia.");
        }

        if (head == tail) {
            T value = head->data;
            auto temp = head;
            delete temp;
            head = nullptr;
            tail = nullptr;

            return value;
        }

        auto temp = head;
        tail->next = head->next;
        head->next->prev = tail;
        head = head->next;

        T value = temp->data;
        delete temp;

        return value;
    }

    T pop_back() {
        if (head == nullptr) {
            throw std::runtime_error("La lista esta vacia.");
        }

        if (head == tail) {
            T value = head->data;
            auto temp = head;
            delete temp;
            head = nullptr;
            tail = nullptr;

            return value;
        }

        auto temp = tail;
        head->prev = tail->prev;
        tail->prev->next = head;
        tail = tail->prev;

        T value = temp->data;
        delete temp;

        return value;
    }

    void insert(T value, int pos) {
        if (pos < 0) {
            throw std::out_of_range("La posicion es invalida.");
        }

        if (pos == 0) {
            push_front(value);
            return;
        }

        if (head == nullptr && pos != 0) {
            throw std::out_of_range("La posicion es invalida.");
        }

        auto temp = head;
        int i = 0;
        while (i++ < pos - 1) {
            temp = temp->next;
            if (temp == head) throw std::out_of_range("La posicion es invalida.");
        }

        CDLLNode<T> *new_CDLLNode = new CDLLNode<T>;
        new_CDLLNode->data = value;

        new_CDLLNode->next = temp->next;
        new_CDLLNode->prev = temp;

        temp->next->prev = new_CDLLNode;
        temp->next = new_CDLLNode;

        if (temp == tail) {
            tail = new_CDLLNode;
        }
    }

    void remove(int pos) {
        if (head == nullptr) {
            throw std::out_of_range("La lista está vacía.");
        }

        if (pos < 0) {
            throw std::out_of_range("La posición es inválida.");
        }

        if (head == tail) {
            if (pos == 0) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                throw std::out_of_range("La posición es inválida.");
            }
            return;
        }

        if (pos == 0) {
            CDLLNode<T> *temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
            return;
        }

        CDLLNode<T> *temp = head;
        int i = 0;
        while (i < pos) {
            temp = temp->next;
            i++;
            if (temp == head) {
                throw std::out_of_range("La posición es inválida.");
            }
        }

        if (temp == tail) {
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
    }


    T operator[](int pos) const {
        if (head == nullptr) throw std::out_of_range("La posicion es invalida.");

        auto temp = head;
        int i = 0;
        while (i++ < pos) {
            temp = temp->next;
            if (temp == head) throw std::out_of_range("La posicion es invalida.");
        }
        return temp->data;
    }

    T &operator[](int pos) {
        if (head == nullptr) throw std::out_of_range("La posicion es invalida.");

        auto temp = head;
        int i = 0;
        while (i++ < pos) {
            temp = temp->next;
            if (temp == head) throw std::out_of_range("La posicion es invalida.");
        }
        return temp->data;
    }

    bool empty() const {
        if (tail == nullptr && head == nullptr) {
            return true;
        }
        return false;
    }

    int size() const {
        if (head == nullptr) return 0;
        int s = 1;
        CDLLNode<T> *temp = head->next;
        while (temp != head) {
            temp = temp->next;
            s++;
        }
        return s;
    }

    void clear() {
        if (head == nullptr) return;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        auto temp = head;
        while (temp != tail) {
            auto nodo = temp->next;
            delete temp;
            temp = nodo;
        }
        delete tail;
        head = nullptr;
        tail = nullptr;
    }

    void reverse() {
        if (head == nullptr || head == tail) return;

        /* Ya que la cabeza siempre apunta a la cola y viceversa, entonces primero hacemos el cambio antes del bucle,
         * y luego creamos dos nodos para que hagan los siguientes cambios en el bucle.
         */
        T temp = head->data;
        head->data = tail->data;
        tail->data = temp;

        CDLLNode<T>* first = head->next;
        CDLLNode<T>* last = tail->prev;


        while (first != last && first->prev != last) {
            T temp = first->data;
            first->data = last->data;
            last->data = temp;

            first = first->next;
            last = last->prev;
        }
    }

    void print() {
        auto temp = head;
        while (true) {
            std::cout << temp->data << ' ';
            temp = temp->next;
            if (temp == head) return;
        }
    }

};
