#include "./liste.h"
#include <iostream>

namespace linked_list {

// NODES

Node *new_node(Value value) { return new Node{value, nullptr, nullptr}; }

void destroy_node(Node *node) { delete node; }

void insert_node_after_node(Node *prev, Node *next) {
    if (prev != nullptr && next != nullptr) {
        if (prev->next != nullptr) {
            next->next = prev->next;
        }
        prev->next = next;
        if (next->prev != nullptr) {
            prev->prev = next->prev;
        }
        next->prev = prev;
    } else {
        std::cerr << "Can't insert node after node. Some node is nullptr."
                  << std::endl;
    }
}

void insert_value_after_node(Node *node, Value value) {
    auto next = new_node(value);
    insert_node_after_node(node, next);
}

void insert_value_before_node(Node *node, Value value) {
    auto prev = new_node(value);
    insert_node_after_node(prev, node);
}

// LINKED_LISTS

LinkedList *new_linked_list() { return new LinkedList{nullptr, nullptr, 0}; }

void destroy(LinkedList *list) {
    if (list != nullptr) {
        // delete all nodes
        auto node = list->head;
        while (node != nullptr) {
            Node *next = node->next;
            destroy_node(node);
            node = next;
        }
        // delete list
        delete list;
    }
}

void print(LinkedList *list) {
    if (list != nullptr) {
        auto current = list->head;
        while (current != nullptr) {
            std::cout << "{ ";
            std::cout << current->value.ville;
            std::cout << ", ";
            std::cout << current->value.quantity;
            std::cout << " } -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }
}

void push_front(LinkedList *list, Value value) {
    // cautions
    if (list == nullptr) {
        std::cerr << "List is nullptr";
    }
    // push
    if (list->size == 0) {
        // if empty
        list->head = new_node(value);
        list->tail = list->head;
    } else {
        insert_value_before_node(list->head, value);
        list->head = list->head->prev;
    }
    list->size++;
}

void push_back(LinkedList *list, Value value) {
    // cautions
    if (list == nullptr) {
        std::cerr << "List is nullptr";
    }
    // push
    if (list->size == 0) {
        // if empty
        list->tail = new_node(value);
        list->head = list->tail;
    } else {
        insert_value_after_node(list->tail, value);
        list->tail = list->tail->next;
    }
    list->size++;
}

Node *get_node_from_front(LinkedList *list, std::size_t index) {
    // Cautions
    if (list == nullptr) {
        std::cerr << "Attempt to get node from empty linked list.";
        return nullptr;
    }
    if (index >= list->size) {
        std::cerr << "Attempt to get node out of bounds. size=" << list->size
                  << " index=" << index << std::endl;
        return nullptr;
    }
    // Get
    Node *current_node = list->head;
    while (index > 0) {
        current_node = current_node->next;
        if (current_node == nullptr) {
            std::cerr << "Unexpected error in get_node_from_front()";
            return nullptr;
        }
        index--;
    }
    return current_node;
}

bool insert_after_from_front(LinkedList *list, Value value, std::size_t index) {
    // Cautions
    Node *node = get_node_from_front(list, index);
    if (node == nullptr) {
        std::cerr << "Couldn't insert at index " << index << std::endl;
        return false;
    }
    // Insert
    insert_value_after_node(node, value);
    return true;
}

Node *get_node_by_ville(LinkedList *list, std::string ville) {
    Node *current_node = list->head;
    while (current_node != nullptr) {
        if (current_node->value.ville == ville)
            return current_node;
        current_node = current_node->next;
    }
    return nullptr;
}

} // namespace linked_list
