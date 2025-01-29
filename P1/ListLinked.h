#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;  // Puntero al primer nodo
    int n;           // Número de elementos

public:
    // Constructor: inicializa lista vacía
    ListLinked() : first(nullptr), n(0) {}

    // Destructor: libera memoria de todos los nodos
    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    // Inserta elemento en posición pos
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida");
        
        if (pos == 0) {  // Inserción al inicio
            first = new Node<T>(e, first);
        } else {  // Inserción en medio o final
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }

    // Inserta al final (reutiliza insert)
    void append(T e) override {
        insert(n, e);
    }

    // Inserta al inicio (reutiliza insert)
    void prepend(T e) override {
        insert(0, e);
    }

    // Elimina y devuelve elemento en posición pos
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida");
        
        Node<T>* target;
        if (pos == 0) {  // Eliminar primer elemento
            target = first;
            first = first->next;
        } else {  // Eliminar elemento intermedio o final
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            target = prev->next;
            prev->next = target->next;
        }
        T data = target->data;
        delete target;
        --n;
        return data;
    }

    // Devuelve elemento en posición pos
    T get(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida");
        
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Busca elemento y devuelve su posición
    int search(T e) override {
        Node<T>* current = first;
        int index = 0;
        while (current != nullptr) {
            if (current->data == e) return index;
            current = current->next;
            ++index;
        }
        return -1;
    }

    // Verifica si la lista está vacía
    bool empty() override {
        return n == 0;
    }

    // Devuelve número de elementos
    int size() override {
        return n;
    }

    // Sobrecarga del operador [] para acceso directo
    T operator[](int pos) {
        return get(pos);
    }

    // Sobrecarga del operador << para imprimir la lista
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        out << "[";
        Node<T>* current = list.first;
        while (current != nullptr) {
            out << *current;  // Usa la sobrecarga de Node<T>
            if (current->next != nullptr) out << ", ";
            current = current->next;
        }
        out << "]";
        return out;
    }
};

#endif