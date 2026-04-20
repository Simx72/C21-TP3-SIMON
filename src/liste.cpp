#include "./liste.h"
#include <iostream>
#include <stdexcept>

namespace linked_list {

// NODES

Node* new_node(Value value) { return new Node{value, nullptr}; }

void node_destroy(Node* node) { delete node; }

void node_insert_next(Node* node, Node* next) {
    if (node != nullptr && next != nullptr) {
        // If node has already someone
        if (node->next != nullptr) {
            // Move to next
            next->next = node->next;
        }
        node->next = next;
    } else {
        throw std::runtime_error("Can't insert node after node. A param is nullptr.");
    }
}

void node_insert_value_next(Node* node, Value value) {
    auto next = new_node(value);
    node_insert_next(node, next);
}

// LINKED_LISTS

LinkedList* new_linked_list() { return new LinkedList{nullptr, 0}; }

void destroy(LinkedList* list) {
    if (list != nullptr) {
        // 1. delete all nodes
        while (list->head != nullptr) {
            pop_front(list);
        }
        // 2. delete list
        delete list;
    } // else { ignore }
}

void print(LinkedList* list) {
    if (list != nullptr) {
        for (auto current = list->head; current != nullptr; current = current->next) {
            std::cout << "{ ";
            std::cout << current->value.ville;
            std::cout << ", ";
            std::cout << current->value.quantity;
            std::cout << " } -> ";
        }
        std::cout << "nullptr\n";
    }
}

void push_front(LinkedList* list, Value value) {
    // cautions
    if (list == nullptr) {
        std::cerr << "List is nullptr";
    }
    // push
    if (list->size == 0) {
        list->head = new_node(value);
    } else {
        node_insert_value_next(list->head, value);
    }
    list->size++;
}

bool pop_front(LinkedList* list) {
    if (list != nullptr) {
        if (list->head != nullptr) {
            Node* next = list->head->next;
            node_destroy(list->head);
            list->head = next;
            return true;
        }
    }
    return false;
}

Node* get_node_by_ville(LinkedList* list, std::string ville) {
    Node* current_node = list->head;
    while (current_node != nullptr) {
        if (current_node->value.ville == ville)
            return current_node;
        current_node = current_node->next;
    }
    return nullptr;
}

} // namespace linked_list
