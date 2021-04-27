/**
 * @file ListaDobleEnlazada.cpp
 * @version 1.0
 * @title ListaDobleEnlazada
 * @brief Manejo de la lista enlazada de las lineas del codigo al presionar run
 */
#pragma once
#include <iostream>

using namespace std;

/**
 * @brief Clase Node se encarga de manejar la informacion de las lineas y los punteros al siguiente
 */
class Node{
public:
    std::string data;
    Node* next;
    Node* prev;
};
/**
 * @brief insert_end para insertar una nueva linea al final de la lista
 * @param head el espacio de memoria de la cabeza de la lista
 * @param new_data la informacion o string que se mantendra en ese nodo
 */
void insert_end(Node** head, std::string new_data)
{
    Node* newNode = new Node();

    Node* last = *head;

    newNode->data = new_data;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        newNode->prev = nullptr;
        *head = newNode;
        return;
    }
    while(last->next != nullptr)
        last = last->next;
    last->next = newNode;
    newNode->prev = last;
}
/**
 * @brief deleteNode para eliminar un nodo dado
 * @param head_ref el espacio de memoria de la cabeza de la lista
 * @param del es el puntero al nodo que se quiere eliminar o borrar
 */
void deleteNode(Node** head_ref, Node* del)
{
    if (*head_ref == nullptr || del == nullptr)
        return;
    if (*head_ref == del)
        *head_ref = del->next;
    if (del->next != nullptr)
        del->next->prev = del->prev;
    if (del->prev != nullptr)
        del->prev->next = del->next;

    free(del);
}
/**
 * @brief clearDLList es para eliminar todos los nodos de la lista
 * @param head_ref es el espacio de memoria de la cabeza de la lista
 */
void clearDLList(Node** head_ref)
{
    Node* ptr = *head_ref;
    Node* next;

    while (ptr != nullptr)
    {
        next = ptr->next;
        deleteNode(head_ref, ptr);
        ptr = next;
    }
}
/**
 * @brief printList funcion para imprimir en terminal la lista
 * @param node es el nodo del cual la impresion empezara
 */
void printList(Node* node)
{
    Node* last;
    while (node != nullptr)
    {
        std::cout << node->data << ", ";
        last = node;
        node = node->next;
    }
    cout << endl;
}
/*int main()
{
    struct Node* head =  nullptr;
    insert_end(&head, "10");
    insert_end(&head, "9");
    insert_end(&head, "7");
    insert_end(&head, "6");
    insert_end(&head, "5");
    printList(head);
    clearDLList(&head);
    printList(head);
}*/