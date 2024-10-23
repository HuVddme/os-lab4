#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t* list_alloc() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
}

void list_free(list_t* list) {
    node_t* current = list->head;
    node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_add_to_front(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

void list_add_to_back(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void list_add_at_index(list_t* list, int index, int value) {
    if (index == 0) {
        list_add_to_front(list, value);
        return;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    node_t* temp = list->head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp != NULL) {
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

int list_remove_from_back(list_t* list) {
    if (list->head == NULL) {
        return -1;  // List is empty
    }
    node_t* temp = list->head;
    if (temp->next == NULL) {
        int value = temp->value;
        free(temp);
        list->head = NULL;
        return value;
    }
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    int value = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    return value;
}

int list_remove_from_front(list_t* list) {
    if (list->head == NULL) {
        return -1;  // List is empty
    }
    node_t* temp = list->head;
    int value = temp->value;
    list->head = temp->next;
    free(temp);
    return value;
}

int list_remove_at_index(list_t* list, int index) {
    if (index == 0) {
        return list_remove_from_front(list);
    }
    node_t* temp = list->head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp != NULL && temp->next != NULL) {
        node_t* to_remove = temp->next;
        int value = to_remove->value;
        temp->next = to_remove->next;
        free(to_remove);
        return value;
    }
    return -1;  // Index out of range
}

int list_get_elem_at(list_t* list, int index) {
    node_t* temp = list->head;
    for (int i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp != NULL) {
        return temp->value;
    }
    return -1;  // Index out of range
}

int list_length(list_t* list) {
    int length = 0;
    node_t* temp = list->head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

char* listToString(list_t* list) {
    static char str[1024];
    str[0] = '\0';  // Empty the string
    node_t* temp = list->head;
    while (temp != NULL) {
        char buffer[32];
        sprintf(buffer, "%d -> ", temp->value);
        strcat(str, buffer);
        temp = temp->next;
    }
    strcat(str, "NULL");
    return str;
}
