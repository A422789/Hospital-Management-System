#ifndef APPOINTMENTQUEUE_H
#define APPOINTMENTQUEUE_H

#include <iostream>
using namespace std;

class AppointmentQueue
{
private:

    struct Node
    {
        int patientId;
        Node* next;

        Node(int id)
        {
            patientId = id;
            next = NULL;
        }
    };

    Node* front;
    Node* rear;

public:

    AppointmentQueue()
    {
        front = NULL;
        rear = NULL;
    }

    void enqueue(int patientId)
    {
        Node* newNode = new Node(patientId);

        if (rear == NULL)
        {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;

        rear = newNode;
    }

    int dequeue()
    {
        if (front == NULL)
        {
            cout << "Queue is empty." << endl;
            return -1;
        }

        Node* temp = front;

        int id = temp->patientId;

        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        delete temp;

        return id;
    }

    void displayQueue()
    {
        if (front == NULL)
        {
            cout << "No patients waiting." << endl;
            return;
        }

        Node* temp = front;

        cout << "Waiting Queue:" << endl;

        while (temp != NULL)
        {
            cout << temp->patientId << " -> ";

            temp = temp->next;
        }

        cout << "END" << endl;
    }
};

#endif
