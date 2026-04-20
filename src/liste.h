#ifndef LISTE_H
#define LISTE_H
#include <string>
namespace linked_list {

struct Value {
    std::string ville;
    int quantity;
};

struct Node {
    Value value;
    Node* next;
};

struct LinkedList {
    Node* head;
    size_t size;
};

// NODES

// LINKED_LISTS

LinkedList* new_linked_list();

void destroy(LinkedList* list);

void print(LinkedList* list);

void push_front(LinkedList* list, Value value);

bool pop_front(LinkedList* list);

Node* get_node_by_ville(LinkedList* list, std::string ville);

} // namespace linked_list
#endif
