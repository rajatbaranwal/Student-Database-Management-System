#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Define a structure to represent a student
struct Student {
  int rollNumber;
  string name;
  float marks;
  Student *left;
  Student *right;

  // Constructor
  Student(int roll, const string &n, float m)
      : rollNumber(roll), name(n), marks(m), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class for managing student records
class StudentBST {
private:
  Student *root;

  // Helper function to insert a student record into the BST
  Student *insert(Student *node, int roll, const string &name, float marks) {
    if (node == nullptr) {
      return new Student(roll, name, marks);
    }

    if (roll < node->rollNumber) {
      node->left = insert(node->left, roll, name, marks);
    } else if (roll > node->rollNumber) {
      node->right = insert(node->right, roll, name, marks);
    }

    return node;
  }

  // Helper function to perform an in-order traversal and display records
  void displayInOrder(Student *node) {
    if (node != nullptr) {
      displayInOrder(node->left);
      cout << "Roll Number: " << node->rollNumber << ", Name: " << node->name
           << ", Marks: " << node->marks << endl;
      displayInOrder(node->right);
    }
  }

  // Helper function to search for a student by roll number
  Student *search(Student *node, int roll) {
    if (node == nullptr || node->rollNumber == roll) {
      return node;
    }

    if (roll < node->rollNumber) {
      return search(node->left, roll);
    } else {
      return search(node->right, roll);
    }
  }

  // Helper function to find the node with the minimum value in a BST
  Student *findMin(Student *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  // Helper function to delete a student record from the BST
  Student *remove(Student *node, int roll) {
    if (node == nullptr) {
      return node;
    }

    // Recursive calls to find and delete the node
    if (roll < node->rollNumber) {
      node->left = remove(node->left, roll);
    } else if (roll > node->rollNumber) {
      node->right = remove(node->right, roll);
    } else {
      // Node with only one child or no child
      if (node->left == nullptr) {
        Student *temp = node->right;
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        Student *temp = node->left;
        delete node;
        return temp;
      }

      // Node with two children: Get the inorder successor (smallest
      // in the right subtree)
      Student *temp = findMin(node->right);

      // Copy the inorder successor's content to this node
      node->rollNumber = temp->rollNumber;
      node->name = temp->name;
      node->marks = temp->marks;

      // Delete the inorder successor
      node->right = remove(node->right, temp->rollNumber);
    }

    return node;
  }

public:
  // Constructor
  StudentBST() : root(nullptr) {}

  // Function to add a new student record
  void addStudent(int roll, const string &name, float marks) {
    root = insert(root, roll, name, marks);
  }

  void exportCSV(const string &filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
      cout << "Error opening file for writing!" << endl;
      return;
    }

    exportCSVHelper(root, outFile);
    outFile.close();
    cout << "Student records exported to " << filename << " in CSV format."
         << endl;
  }

  // Function to display all student records in sorted order
  void displayAllStudents() {
    cout << "All Student Records:" << endl;
    displayInOrder(root);
    cout << endl;
  }

  // Function to search for a student by roll number
  void searchStudent(int roll) {
    Student *result = search(root, roll);
    if (result != nullptr) {
      cout << "Student Found - Roll Number: " << result->rollNumber
           << ", Name: " << result->name << ", Marks: " << result->marks
           << endl;
    } else {
      cout << "Student with Roll Number " << roll << " not found." << endl;
    }
  }

  // Function to delete a student record
  void deleteStudent(int roll) {
    root = remove(root, roll);
    cout << "Student with Roll Number " << roll << " deleted." << endl;
  }

private:
  // Helper function to write student records to CSV
  void exportCSVHelper(Student *node, ofstream &outFile) {
    if (node != nullptr) {
      exportCSVHelper(node->left, outFile);
      outFile << node->rollNumber << "," << node->name << "," << node->marks
              << "\n";
      exportCSVHelper(node->right, outFile);
    }
  }
};

int main() {
  // Create an instance of StudentBST
  StudentBST studentDatabase;

  // Menu-driven program
  int choice, roll;
  string name;
  float marks;

  do {
    cout << "\nMenu:\n1. Add Student\n2. Search Student\n3. Delete Student\n4. "
            "Display All Students\n5. Export CSV\n6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Enter Roll Number: ";
      cin >> roll;
      cout << "Enter Name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter Marks: ";
      cin >> marks;
      studentDatabase.addStudent(roll, name, marks);
      break;

    case 2:
      cout << "Enter Roll Number to Search: ";
      cin >> roll;
      studentDatabase.searchStudent(roll);
      break;

    case 3:
      cout << "Enter Roll Number to Delete: ";
      cin >> roll;
      studentDatabase.deleteStudent(roll);
      break;

    case 4:
      studentDatabase.displayAllStudents();
      break;

      
      case 5:
      studentDatabase.exportCSV("student_records.csv");
      break;

    case 6:
      cout << "Exiting program.\n";
      break;


    default:
      cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 5);

  return 0;
}