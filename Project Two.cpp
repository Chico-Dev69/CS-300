
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        this->course = c;
        left = right = nullptr;
    }
};

class CourseBST {
private:
    Node* root;

    void addNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        } else if (course.courseNumber < node->course.courseNumber) {
            addNode(node->left, course);
        } else {
            addNode(node->right, course);
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
            inOrder(node->right);
        }
    }

    Course* search(Node* node, string courseNumber) {
        if (node == nullptr) return nullptr;
        if (node->course.courseNumber == courseNumber) return &node->course;
        if (courseNumber < node->course.courseNumber)
            return search(node->left, courseNumber);
        else
            return search(node->right, courseNumber);
    }

public:
    CourseBST() {
        root = nullptr;
    }

    void Insert(Course course) {
        addNode(root, course);
    }

    void PrintInOrder() {
        inOrder(root);
    }

    Course* Search(string courseNumber) {
        return search(root, courseNumber);
    }
};

vector<Course> LoadCoursesFromFile(string fileName) {
    vector<Course> courses;
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, token;
        vector<string> prereqs;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        while (getline(ss, token, ',')) {
            prereqs.push_back(token);
        }

        Course course = {courseNumber, courseTitle, prereqs};
        courses.push_back(course);
    }

    return courses;
}

int main() {
    CourseBST bst;
    vector<Course> loadedCourses;
    bool isLoaded = false;
    int choice;
    string fileName, courseNum;

    while (true) {
        cout << "\n1 - Load course data" << endl;
        cout << "2 - Print all courses" << endl;
        cout << "3 - Print course details" << endl;
        cout << "9 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                cin >> fileName;
                loadedCourses = LoadCoursesFromFile(fileName);
                for (Course c : loadedCourses) {
                    bst.Insert(c);
                }
                isLoaded = true;
                cout << "Courses loaded." << endl;
                break;

            case 2:
                if (isLoaded) bst.PrintInOrder();
                else cout << "Please load course data first.\n";
                break;

            case 3:
                if (isLoaded) {
                    cout << "Enter course number: ";
                    cin >> courseNum;
                    Course* found = bst.Search(courseNum);
                    if (found) {
                        cout << "Course Number: " << found->courseNumber << endl;
                        cout << "Title: " << found->courseTitle << endl;
                        cout << "Prerequisites: ";
                        if (found->prerequisites.empty()) cout << "None";
                        else for (string p : found->prerequisites) cout << p << " ";
                        cout << endl;
                    } else cout << "Course not found." << endl;
                } else {
                    cout << "Please load course data first.\n";
                }
                break;

            case 9:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
