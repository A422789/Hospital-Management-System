#include "PatientManager.h"
#include <iostream>
using namespace std;

PatientManager::PatientManager()
{
    root = NULL;
}

PatientManager::Node* PatientManager::insert(Node* node, PatientRecord p)
{
    if (node == NULL)
    {
        return new Node(p);
    }

    if (p.id < node->data.id)
    {
        node->left = insert(node->left, p);
    }
    else if (p.id > node->data.id)
    {
        node->right = insert(node->right, p);
    }

    return node;
}

PatientManager::Node* PatientManager::search(Node* node, int id)
{
    if (node == NULL || node->data.id == id)
    {
        return node;
    }

    if (id < node->data.id)
    {
        return search(node->left, id);
    }

    return search(node->right, id);
}

PatientManager::Node* PatientManager::findMin(Node* node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

PatientManager::Node* PatientManager::deleteNode(Node* node, int id)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (id < node->data.id)
    {
        node->left = deleteNode(node->left, id);
    }
    else if (id > node->data.id)
    {
        node->right = deleteNode(node->right, id);
    }
    else
    {
        // no child
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }

        // one child
        else if (node->left == NULL)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        else if (node->right == NULL)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // two children
        Node* temp = findMin(node->right);

        node->data = temp->data;

        node->right = deleteNode(node->right, temp->data.id);
    }

    return node;
}

void PatientManager::addPatient(PatientRecord p)
{
    root = insert(root, p);
}

void PatientManager::searchById(int id)
{
    Node* result = search(root, id);

    if (result == NULL)
    {
        cout << "Patient not found. Register first.\n";
    }
    else
    {
        cout << "\nPatient Found:\n";

        cout << "ID: " << result->data.id << endl;
        cout << "Name: " << result->data.name << endl;
        cout << "Disease: " << result->data.disease << endl;
        cout << "Severity: " << result->data.severity << endl;
    }
}

bool PatientManager::exists(int id)
{
    return search(root, id) != NULL;
}

void PatientManager::deletePatient(int id)
{
    root = deleteNode(root, id);
}
