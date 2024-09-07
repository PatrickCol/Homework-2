
#include <iostream>
using namespace std;

// Definimos la estructura de un nodo
template<typename T>
struct Nodo {
    T data;
    Nodo<T>* next;
    Nodo<T>* prev;
};

template<typename T>
class ListaDoblementeEnlazada {
private:
    Nodo<T>* head; // Puntero al primer nodo de la lista
    Nodo<T>* tail; // Puntero al último nodo de la lista

public:

    ListaDoblementeEnlazada() {
        head = nullptr; // La lista empieza vacia
        tail = nullptr; // La lista empieza vacia
    }

    // para retornar el primer elemento
    T front() const {
        // verificamos si la lista está vacia
        if (head == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return head->data;
        }
    }

    T &front() {
        // verificamos si la lista está vacia
        if (head == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return head->data;
        }
    }

    // para retornar el último elemento
    T back() const {
        // verificamos si la lista está vacia
        if (tail == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return tail->data;
        }
    }

    T &back() {
        // verificamos si la lista está vacia
        if (tail == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        } else {
            return tail->data;
        }
    }

    // metodo para agregar un elemento al frente de la lista
    void push_front(int valor) {
        auto* nodo = new Nodo<T>;
        nodo->data = valor;
        if (head == nullptr) { //Si la lista esta vacia
            head = nodo;
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;
            return;
        }

        nodo->next = head;
        nodo->prev = nullptr;
        head->prev = nodo;
        head = nodo;
    }

    void push_back(T value) {
        Nodo<T> *nodo = new Nodo<T>;
        nodo->data = value;
        if (tail == nullptr) { //Si la lista esta vacia
            tail = nodo;
            tail->next = nullptr;
            tail->prev = nullptr;
            head = tail;
            return;
        }

        nodo->next = nullptr;
        nodo->prev = tail;
        tail->next = nodo;
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
        head->next->prev = nullptr;
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
            T value = tail->data;
            auto temp = tail;
            delete temp;
            head = nullptr;
            tail = nullptr;

            return value;
        }

        auto temp = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;

        T value = temp->data;
        delete temp;

        return value;
    }

    void insert(T value, int pos) {
        if (pos < 0) {
            throw std::out_of_range("La posición es inválida.");
        }

        Nodo<T> *new_node = new Nodo<T>;
        new_node->data = value;

        if (head == nullptr) {
            if (pos != 0) {
                throw std::out_of_range("La posición es inválida.");
            }
            new_node->next = nullptr;
            new_node->prev = nullptr;
            head = new_node;
            tail = new_node;
            return;
        }

        if (pos == 0) {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            return;
        }

        Nodo<T> *temp = head;
        int i = 0;
        while (temp != nullptr && i < pos - 1) {
            temp = temp->next;
            i++;
        }

        if (temp == nullptr && i < pos - 1) {
            throw std::out_of_range("La posición es inválida.");
        }

        if (temp == tail) {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
            return;
        }

        new_node->next = temp->next;
        new_node->prev = temp;
        if (temp->next != nullptr) {
            temp->next->prev = new_node;
        }
        temp->next = new_node;
    }

    void remove(int pos) {
        if (head == nullptr || pos < 0) {
            throw std::out_of_range("La posición es inválida o la lista está vacía.");
        }

        if (pos == 0) {
            Nodo<T> *temp = head;

            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }

            delete temp;  // Liberamos la memoria del nodo removido
            return;
        }

        Nodo<T> *temp = head;
        int i = 0;
        while (temp != nullptr && i < pos) {
            temp = temp->next;
            i++;
        }

        if (temp == nullptr) {
            throw std::out_of_range("La posición es inválida.");
        }

        if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;  // Liberamos la memoria del nodo removido
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;  // Liberamos la memoria del nodo removido
    }

    T operator[](int pos) const {
        if (head == nullptr) throw std::out_of_range("La posicion es invalida.");

        auto temp = head;
        int i = 0;
        while (i++ < pos) {
            temp = temp->next;
            if (temp == nullptr) throw std::out_of_range("La posicion es invalida.");
        }
        return temp->data;
    }

    T &operator[](int pos) {
        if (head == nullptr) throw std::out_of_range("La posicion es invalida.");

        auto temp = head;
        int i = 0;
        while (i++ < pos) {
            temp = temp->next;
            if (temp == nullptr) throw std::out_of_range("La posicion es invalida.");
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
        int s = 0;
        Nodo<T> *temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            s++;
        }
        return s;
    }

    void clear() {
        if (head == nullptr) return;

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        auto temp = head;
        while (temp != nullptr) {
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

        Nodo<T>* first = head;
        Nodo<T>* last = tail;

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
        while (temp != nullptr) {
            std::cout << temp->data << ' ';
            temp = temp->next;
            if (temp == head) return;
        }
    }

};
