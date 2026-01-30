Library Management System (LMS)
A robust, console-based solution for modern library record-keeping, developed in C.

📖 Introduction
Traditional library records are often prone to human error and data loss. This project provides a digital alternative that focuses on Data Integrity (keeping information accurate) and Persistence (keeping information saved). By using binary file structures, the system mimics the behavior of a professional database.

🛠️ System Architecture
The system is built on three main pillars:

1. Data Structures
We use struct to group related information.

Book Entity: Stores unique ID, Title, Author, and Stock Quantity.

Member Entity: Stores unique ID, Full Name, and Contact Details.

2. File Handling (The Persistence Layer)
Unlike standard text files (.txt), this system uses Binary Files (.bin).

Efficiency: Binary data is read and written directly from memory, making it much faster.

Security: Data is stored in a non-human-readable format, providing a basic layer of data protection.

3. Business Logic & Validation
Professional software must prevent user errors. This system includes:

Uniqueness Check: Automatically scans existing records to ensure no two books or members share the same ID.

Stock Safeguard: A conditional logic gate in the "Issue Book" function prevents the inventory from ever dropping below zero.

🚀 Key Features
Inventory Management: Add, update, and view the entire library collection.

Smart Search: Partial string matching allows you to find books even if you only remember one word of the title.

Member Directory: A dedicated database to track registered library users.

Automated Sync: Every change (Adding, Issuing, or Returning) is instantly synchronized with the binary file.

💻 Technical Setup
Prerequisites
A C compiler (GCC is recommended).

A terminal or command prompt.

Installation & Running
Clone or Download: Save library_management.c to your local machine.

Compile:
gcc library_management.c -o library

Execute:
./library
🧪 Operational Scenarios (Testing)
To verify the system's robustness, the following scenarios were tested:

ID Conflict: Attempting to register a book with an ID that already exists results in an error message.

Out of Stock: Attempting to issue a book with qty = 0 triggers a system block.

Power-Off Test: Closing the program after adding data and reopening it confirms that all records are successfully reloaded from the disk.
