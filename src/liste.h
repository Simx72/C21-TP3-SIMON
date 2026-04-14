#ifndef LISTE_H
#define LISTE_H
#include <string>
namespace linked_list {

struct Value {
    std::string str;
    int number;
};

struct Node {
    Value value;
    Node *next;
    Node *prev;
};

struct LinkedList {
    Node *head;
    Node *tail;
    size_t size;
};

// NODES

// Node *new_node(Value value);

// void destroy_node(Node *node);

// void insert_after_node(Node *node, Value value);

// LINKED_LISTS

LinkedList *new_linked_list();

void destroy(LinkedList *list);

void print(LinkedList *list);

void push_front(LinkedList *list, Value value);

void push_back(LinkedList *list, Value value);

Node *get_node_from_front(LinkedList *list, std::size_t index);

bool insert_after_from_front(LinkedList *list, Value value, std::size_t index);

} // namespace linked_list
#endif
