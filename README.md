# Laptop ownership System (C++)

This is a menu-driven C++ program designed to manage laptop ownership records for university students. Each student is allowed to own only one laptop, identified by a unique serial number.

## Features

- Register a laptop for a new student
- Update a laptop serial number if a laptop is lost
- Check the owner of a laptop using its serial number
- Search for a laptop using a student ID
- Remove a laptop record when a student leaves
- Display all registered laptop records

## Student ID Format

A valid student ID must meet the following requirements:
- Exactly 9 characters long
- Starts with the letters ETS
- Ends with 6 numeric digits

Example:

ETS123456

````

## Program Description

The program uses two parallel arrays:
- One array to store student IDs
- One array to store laptop serial numbers

It applies input validation to ensure:
- No duplicate student IDs
- No duplicate laptop serial numbers
- Correct student ID format
- Accurate check-out operations

The system is controlled through a menu that allows the user to perform different operations until the program is terminated.

## Menu Options

A - Add Laptop (New Student)  
U - Update Laptop Serial (Lost Laptop)  
C - Check Laptop Owner by Serial  
F - Search Laptop by Student ID  
O - Check Out Laptop (Student Leaving)  
S - Display All Records  
Q - Quit  

## How to Compile and Run

Using g++ compiler:

g++ laptop_system.cpp -o laptop_system
./laptop_system
````

(Replace `laptop_system.cpp` with the actual source file name.)

## Limitations

* Data is stored only during program execution
* Records are lost once the program terminates
* Maximum number of students is fixed at runtime

## Possible Enhancements

* Use structures or classes instead of parallel arrays
* Add file handling for permanent storage
* Improve input handling and error messages

## Authors

Group Project

