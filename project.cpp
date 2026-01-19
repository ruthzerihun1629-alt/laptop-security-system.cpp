#include <iostream>
#include <cctype>
using namespace std;

/* ---------- FUNCTION PROTOTYPES ---------- */
bool isValidID(string id);
bool serialExists(string serial, string serialArr[], int count);
int findStudent(string id, string idArr[], int count);

void showMenu();
void addLaptop(string idArr[], string serialArr[], int* count, int maxStudents);
void updateLaptop(string idArr[], string serialArr[], int count);
void checkOutLaptop(string idArr[], string serialArr[], int* count);
void displayStatus(string idArr[], string serialArr[], int count);

/* ---------- MAIN FUNCTION ---------- */
int main() {
    int maxStudents;
    int count = 0;
    char choice;
// The Welcome Message
    cout << "==============================================\n";
    cout << "  Welcome to Smart Campus Laptop Security System\n";
    cout << "==============================================\n";
    

    /* ===== VALIDATE maxStudents ===== */
    do {
        cout << "Enter number of students/laptops you want to register: ";
        cin >> maxStudents;

        if (maxStudents <= 0) {
            cout << "Number must be greater than zero. Please try again.\n";
        }
    } while (maxStudents <= 0);

    string idArr[maxStudents];
    string serialArr[maxStudents];

    do {
        showMenu();
        cin >> choice;
        choice = toupper(choice);

        // Menu choice validation
        if (!isalpha(choice)) {
            cout << "Please enter a valid letter for your choice.\n";
            continue;
        }

        switch (choice) {
            case 'A':
                addLaptop(idArr, serialArr, &count, maxStudents);
                break;

            case 'U':
                updateLaptop(idArr, serialArr, count);
                break;

            case 'O':
                checkOutLaptop(idArr, serialArr, &count);
                break;

            case 'D':
                displayStatus(idArr, serialArr, count);
                break;

            case 'Q':
                cout << "Thank you for using the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Please choose a valid menu letter.\n";
        }

    } while (choice != 'Q');

    return 0;
}

/* ---------- FUNCTIONS ---------- */

void showMenu() {
    cout << "\n===== Main Menu =====\n";
    cout << "A - Add Laptop (New Student)\n";
    cout << "U - Update Laptop Serial (Lost Laptop)\n";
    cout << "O - Check Out Laptop (Student Leaving)\n";
    cout << "D - Display All Records\n";
    cout << "Q - Quit\n";
    cout << "Enter your choice: ";
}

/* --- Validate Student ID format --- */
bool isValidID(string id) {
    if (id.length() != 9)
        return false;

    if (toupper(id[0]) != 'E' && toupper(id[1]) != 'T' && toupper(id[2]) != 'S')
        return false;

    for (int i = 3; i < 9; i++) {
        if (!isdigit(id[i]))
            return false;
    }

    return true;
}

/* --- Check if serial already exists --- */
bool serialExists(string serial, string serialArr[], int count) {
    for (int i = 0; i < count; i++) {
        if (serialArr[i] == serial)
            return true;
    }
    return false;
}

/* --- Find student by ID --- */
int findStudent(string id, string idArr[], int count) {
    for (int i = 0; i < count; i++) {
        if (idArr[i] == id)
            return i;
    }
    return -1;
}

/* --- Add Laptop --- */
void addLaptop(string idArr[], string serialArr[], int* count, int maxStudents) {
    string id, serial;

    if (*count == maxStudents) {
        cout << "You have reached maximum capacity: " << maxStudents << " students.\n";
        return;
    }

    cout << "Enter Student ID (ETSxxxxxx): ";
    cin >> id;

    // Uppercase first 3 letters
    for (int i = 0; i < 3 && i < id.length(); i++)
        id[i] = toupper(id[i]);

    if (!isValidID(id)) {
        cout << "Invalid ID format. Must be ETS followed by 6 digits.\n";
        return;
    }
if (findStudent(id, idArr, *count) != -1) {
        cout << "Student already registered. Use Update option to change laptop serial.\n";
        return;
    }

    cout << "Enter Laptop Serial: ";
    cin >> serial;

    if (serialExists(serial, serialArr, *count)) {
        cout << "This laptop serial is already registered to another student.\n";
        return;
    }

    idArr[*count] = id;
    serialArr[*count] = serial;
    (*count)++;

    cout << "Laptop successfully registered for student " << id << ".\n";
}

/* --- Update Laptop Serial --- */
void updateLaptop(string idArr[], string serialArr[], int count) {
    string id, newSerial;

    cout << "Enter Student ID to update (ETSxxxxxx): ";
    cin >> id;

    for (int i = 0; i < 3 && i < id.length(); i++)
        id[i] = toupper(id[i]);

    if (!isValidID(id)) {
        cout << "Invalid ID format. Must be ETS followed by 6 digits.\n";
        return;
    }

    int index = findStudent(id, idArr, count);
    if (index == -1) {
        cout << "Student not found. Please check the ID and try again.\n";
        return;
    }

    cout << "Enter New Laptop Serial: ";
    cin >> newSerial;

    if (serialExists(newSerial, serialArr, count)) {
        cout << "This serial already exists for another student.\n";
        return;
    }

    cout << "Are you sure you want to update laptop serial for " << id << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    if (toupper(confirm) != 'Y') {
        cout << "Update cancelled.\n";
        return;
    }

    serialArr[index] = newSerial;
    cout << "Laptop serial updated successfully for student " << id << ".\n";
}

/* --- Check Out / Remove Student --- */
void checkOutLaptop(string idArr[], string serialArr[], int* count) {
    string id, serial;

    if (*count == 0) {
        cout << "No students registered yet.\n";
        return;
    }

    cout << "Enter Student ID to check out (ETSxxxxxx): ";
    cin >> id;

    for (int i = 0; i < 3 && i < id.length(); i++)
        id[i] = toupper(id[i]);

    if (!isValidID(id)) {
        cout << "Invalid ID format. Must be ETS followed by 6 digits.\n";
        return;
    }

    int index = findStudent(id, idArr, *count);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter Laptop Serial for confirmation: ";
    cin >> serial;

    if (serialArr[index] != serial) {
        cout << "Laptop serial does not match our records. Cannot check out.\n";
        return;
    }

    cout << "Are you sure you want to remove student " << id << " and check out the laptop? (Y/N): ";
    char confirm;
    cin >> confirm;
    if (toupper(confirm) != 'Y') {
        cout << "Checkout cancelled.\n";
        return;
    }

    // Shift arrays to remove student
    for (int i = index; i < *count - 1; i++) {
        idArr[i] = idArr[i + 1];
        serialArr[i] = serialArr[i + 1];
    }
    (*count)--;

    cout << "Student " << id << " successfully removed and laptop checked out.\n";
}

/* --- Display All Registered Laptops --- */
void displayStatus(string idArr[], string serialArr[], int count) {
    if (count == 0) {
        cout << "No records available.\n";
        return;
    }

    cout << "\nNo.\tStudent ID\tLaptop Serial\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << "\t" << idArr[i] << "\t" << serialArr[i] << endl;
    }
    cout << "Total Registered Students: " << count << "\n";
}
