# 🏥 Hospital Management System (HMS)
**A Data Structures & Algorithms focused project for managing hospital operations.**

## 📌 Project Overview
This project is a high-performance CLI-based Hospital Management System. It is designed to handle complex tasks such as patient registration, staff management, emergency room prioritization, and administrative undo operations. The core of this project lies in implementing and integrating various **Data Structures** to ensure efficiency and data integrity.

---

## 🛠️ Data Structures Used
In this project, we moved beyond basic arrays to use advanced structures:

| Feature | Data Structure | Why? |
| :--- | :--- | :--- |
| **Staff Records** | Binary Search Tree (BST) | For O(log n) search, insertion, and deletion of employee accounts. |
| **Patient Records** | Binary Search Tree (BST) | To maintain a permanent, searchable database of all patients. |
| **Appointment Queue** | Linked Queue | To manage the daily "first-come, first-served" patient flow. |
| **Emergency Room** | Array & Bubble Sort | To store urgent cases and sort them dynamically by severity. |
| **Action Tracker** | Stack (Linked List) | To support "Undo" operations by pushing/popping recent actions. |

---

## 👥 The Team (Scrum Roles)
* **Programmer 1 (UI/UX & Flow):** Responsible for the `SystemInterface` and navigation logic.
* **Programmer 2 (Security):** Responsible for `AccountManager` and Authentication using BST.
* **Programmer 3 (Patient Flow):** Responsible for `PatientManager` (BST) and `AppointmentQueue`.
* **Programmer 4 (Operations):** Responsible for `EmergencyRoom` (Sorting) and `ActionTracker` (Stack).

---

## 🚀 Core Functionalities
### 1. Admin Dashboard
- Register/Delete Staff (Doctors, Receptionists).
- View all employees (In-order traversal).
- Undo last administrative action.

### 2. Receptionist Dashboard
- Register new patients.
- Add patients to the daily waiting list.
- Discharge patients from the system.

### 3. Doctor Dashboard
- Call the next patient from the queue.
- Search for a patient's medical history.
- Manage the Emergency Room (Sort cases by severity).

---

## 💻 How to Use
1. **Clone the Repo:**
   ```bash
   git clone [https://github.com/YourUsername/RepoName.git](https://github.com/YourUsername/RepoName.git)
