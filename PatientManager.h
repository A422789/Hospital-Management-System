#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "PatientRecord.h"

class PatientManager
{
private:

    struct Node
    {
        PatientRecord data;
        Node* left;
        Node* right;

        Node(PatientRecord p)
        {
            data = p;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    Node* insert(Node* node, PatientRecord p)
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

    Node* search(Node* node, int id)
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

    Node* findMin(Node* node)
    {
        while (node->left != NULL)
        {
            node = node->left;
        }

        return node;
    }

    Node* deleteNode(Node* node, int id)
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
            if (node->left == NULL && node->right == NULL)
            {
                delete node;
                return NULL;
            }

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

            Node* temp = findMin(node->right);

            node->data = temp->data;

            node->right = deleteNode(node->right, temp->data.id);
        }

        return node;
    }

public:

    PatientManager()
    {
        root = NULL;
    }

    void addPatient(PatientRecord p)
    {
        root = insert(root, p);
    }

    void searchById(int id)
    {
        Node* result = search(root, id);

        if (result == NULL)
        {
            cout << "Patient not found. Register first." << endl;
        }

        else
        {
            cout << "Patient Found:" << endl;

            cout << "ID: " << result->data.id << endl;
            cout << "Name: " << result->data.name << endl;
            cout << "Disease: " << result->data.disease << endl;
            cout << "Severity: " << result->data.severity << endl;
        }
    }

    bool exists(int id)
    {
        return search(root, id) != NULL;
    }

    void deletePatient(int id)
    {
        root = deleteNode(root, id);
    }
};

#endif
