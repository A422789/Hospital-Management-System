#include "AppointmentQueue.h"
#include <iostream>
using namespace std;

AppointmentQueue::AppointmentQueue()
{
    front = rear = NULL;
}

void AppointmentQueue::enqueue(int patientId)
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

int AppointmentQueue::dequeue()
{
    if (front == NULL)
    {
        cout << "Queue is empty.\n";
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

void AppointmentQueue::displayQueue()
{
    if (front == NULL)
    {
        cout << "No patients waiting.\n";
        return;
    }

    Node* temp = front;

    cout << "\nWaiting Queue:\n";

    while (temp != NULL)
    {
        cout << temp->patientId << " -> ";

        temp = temp->next;
    }

    cout << "END\n";
}
