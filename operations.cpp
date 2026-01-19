#include "functions.h"

void addLaptop(string idArr[], string serialArr[], int* count, int maxStudents) {
    if (*count >= maxStudents) {
        cout << "System storage full.\n";
        return;
    }

    string id, serial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    if (!isValidID(id)) {
        cout << "Invalid ID format.\n";
        return;
    }

    if (findStudent(id, idArr, *count) != -1) {
        cout << "Student already has a laptop. Update serial if lost.\n";
        return;
    }

    cout << "Enter Laptop Serial Number: ";
    cin >> serial;

    if (serialExists(serial, serialArr, *count)) {
        cout << "This laptop already belongs to another student.\n";
        return;
    }

    idArr[*count] = id;
    serialArr[*count] = serial;
    (*count)++;
    cout << "Laptop registered successfully.\n";
}

void updateLaptop(string idArr[], string serialArr[], int count) {
    string id, newSerial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, count);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter New Laptop Serial Number: ";
    cin >> newSerial;

    if (serialExists(newSerial, serialArr, count)) {
        cout << "This serial already exists.\n";
        return;
    }

    serialArr[index] = newSerial;
    cout << "Laptop serial updated successfully.\n";
}

void checkLaptop(string serialArr[], string idArr[], int count) {
    string serial;
    cout << "Enter Laptop Serial Number: ";
    cin >> serial;

    for (int i = 0; i < count; i++) {
        if (serialArr[i] == serial) {
            cout << "Laptop belongs to Student ID: " << idArr[i] << endl;
            return;
        }
    }
    cout << "Laptop not found.\n";
}

void searchByID(string idArr[], string serialArr[], int count) {
    string id;
    cout << "Enter Student ID to search: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, count);
    if (index != -1) {
        cout << "Student ID: " << idArr[index]
             << " owns Laptop Serial: " << serialArr[index] << endl;
    } else {
        cout << "Student ID not found.\n";
    }
}

void checkOutLaptop(string idArr[], string serialArr[], int* count) {
    string id, serial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, *count);
    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    cout << "Enter Laptop Serial Number: ";
    cin >> serial;

    if (serialArr[index] != serial) {
        cout << "Serial does not match the student's laptop. Cannot check out.\n";
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        idArr[i] = idArr[i + 1];
        serialArr[i] = serialArr[i + 1];
    }
    (*count)--;
    cout << "Laptop checked out. Student has left the university.\n";
}
