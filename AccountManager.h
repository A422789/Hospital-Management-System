#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "StaffUser.h"
#include <iostream>
using namespace std;

class AccountManager {
private:
    // ============ Node Structure ============
    struct Node {
        StaffUser data;
        Node* left;
        Node* right;

        Node(StaffUser user) {
            data = user;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    // ============ Private Recursive Functions ============

    // دالة مساعدة للبحث داخل الشجرة - ترجع مؤشر للنود
    // ============ Private ============

Node* findUser(int id) {
    Node* current = root;           // نبدأ من الـ root
    while (current != NULL) {       // نكمل لحد ما نوصل NULL
        if (current->data.getId() == id) {
            return current;         // لقيناه ✅
        }
        if (id < current->data.getId()) {
            current = current->left;    // روح يسار
        } else {
            current = current->right;   // روح يمين
        }
    }
    return NULL;                    // ما لقيناه ❌
}

    // دالة recursive للإضافة
    Node* insertRecursive(Node* current, StaffUser user) {
        // وصلنا لمكان فاضي - هنا نحط النود الجديد
        if (current == NULL) {
            return new Node(user);
        }
        if (user.getId() < current->data.getId()) {
            current->left = insertRecursive(current->left, user);
        } else if (user.getId() > current->data.getId()) {
            current->right = insertRecursive(current->right, user);
        } else {
            // نفس الـ ID موجود مسبقاً - ما نضيفه
            cout << "User with ID " << user.getId() << " already exists!" << endl;
        }
        return current;
    }

    // دالة مساعدة لإيجاد أصغر نود في subtree (تستخدم في الحذف - الحالة الثالثة)
    Node* findMinNode(Node* current) {
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    // دالة recursive للحذف - الحالات الثلاث
    Node* deleteRecursive(Node* current, int id, bool& found) {
        // البيس كيس: ما لقيناه
        if (current == NULL) {
            found = false;
            return NULL;
        }

        if (id < current->data.getId()) {
            // الـ ID المطلوب في الجهة اليسرى
            current->left = deleteRecursive(current->left, id, found);

        } else if (id > current->data.getId()) {
            // الـ ID المطلوب في الجهة اليمنى
            current->right = deleteRecursive(current->right, id, found);

        } else {
            // لقيناه - الحالات الثلاث للحذف:
            found = true;

            // الحالة 1: النود ما عنده أطفال (Leaf Node)
            if (current->left == NULL && current->right == NULL) {
                delete current;
                return NULL;
            }

            // الحالة 2: النود عنده طفل واحد بس
            if (current->left == NULL) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == NULL) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            // الحالة 3: النود عنده طفلين
            // نلاقي الـ In-order Successor (أصغر نود في الـ subtree اليميني)
            Node* successor = findMinNode(current->right);
            // ننسخ بياناته للنود الحالي
            current->data = successor->data;
            // نحذف الـ successor من الـ subtree اليميني
            bool dummyFound = true;
            current->right = deleteRecursive(current->right, successor->data.getId(), dummyFound);
        }

        return current;
    }

    // دالة recursive لـ In-order Traversal (مرتبين حسب الـ ID)
    void inOrderRecursive(Node* current) {
        if (current == NULL) return;

        inOrderRecursive(current->left);
        cout << "-----------------------------" << endl;
        cout << "ID   : " << current->data.getId() << endl;
        cout << "Name : " << current->data.getName() << endl;
        cout << "Role : " << current->data.getRole() << endl;
        inOrderRecursive(current->right);
    }

    // دالة recursive لحذف كل الشجرة من الميموري (Destructor)
    void destroyTree(Node* current) {
        if (current == NULL) return;
        destroyTree(current->left);
        destroyTree(current->right);
        delete current;
    }

public:
    // Constructor
    AccountManager() {
        root = NULL;
    }

    // Destructor - يحرر كل الميموري
    ~AccountManager() {
        destroyTree(root);
    }

    // ============ Public Methods ============

    // إضافة موظف جديد للشجرة بناءً على الـ ID
    void addUser(StaffUser user) {
        root = insertRecursive(root, user);
    }

    // أهم ميثود: تبحث عن الـ ID وتتأكد من الـ Pass
    // ترجع StaffUser فيها id = -1 إذا فشل الـ Login
   // ============ Public ============

StaffUser login(int id, string pass) {
    Node* result = findUser(id);    // ✅ بدون root
    if (result == NULL) {
        StaffUser failed;
        return failed;
    }
    if (result->data.checkPassword(pass)) {
        return result->data;
    } else {
        StaffUser failed;
        return failed;
    }
}
    // حذف موظف من الشجرة
    void deleteUser(StaffUser user) {
        bool found = true;
        root = deleteRecursive(root, user.getId(), found);
        if (found) {
            cout << "User \"" << user.getName() << "\" deleted successfully." << endl;
        } else {
            cout << "User with ID " << user.getId() << " not found!" << endl;
        }
    }

    // overload بـ ID مباشرة (اختياري - يسهل الاستخدام)
    void deleteUser(int id) {
        bool found = true;
        root = deleteRecursive(root, id, found);
        if (found) {
            cout << "User with ID " << id << " deleted successfully." << endl;
        } else {
            cout << "User with ID " << id << " not found!" << endl;
        }
    }

    // طباعة كل الموظفين مرتبين حسب الـ ID (In-order Traversal)
    void displayAll() {
        if (root == NULL) {
            cout << "No staff members registered." << endl;
            return;
        }
        cout << "========== All Staff Members ==========" << endl;
        inOrderRecursive(root);
        cout << "=======================================" << endl;
    }

    // جلب موظف معين بالـ ID
    StaffUser getUser(int id) {
        Node* result = findUser(id);
        if (result != NULL) {
            return result->data;
        }
        return StaffUser(); // يرجع موظف فارغ بمعرف ID = -1
    }
};

#endif
