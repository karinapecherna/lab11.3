#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function prototypes
void CreateRoutesFile(const char* filename);
void ViewRoutesFile(const char* filename);
void AddRouteToFile(const char* filename);
void SearchRoutes(const char* filename, const string& point);
bool IsFileEmpty(const char* filename);

int main() {
    char filename[100];
    int choice;

    cout << "Enter file name: ";
    cin >> filename;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create routes file\n";
        cout << "2. View routes file\n";
        cout << "3. Add a route\n";
        cout << "4. Search routes by point\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateRoutesFile(filename);
            break;
        case 2:
            ViewRoutesFile(filename);
            break;
        case 3:
            AddRouteToFile(filename);
            break;
        case 4: {
            string point;
            cout << "Enter the point name: ";
            cin.ignore();
            getline(cin, point);
            SearchRoutes(filename, point);
            break;
        }
        case 5:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to create a new routes file
void CreateRoutesFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Error creating file.\n";
        return;
    }
    cout << "File created successfully. You can now add routes.\n";
    fout.close();
}

// Function to view the contents of the routes file
void ViewRoutesFile(const char* filename) {
    ifstream fin(filename);
    if (!fin || IsFileEmpty(filename)) {
        cout << "File is empty or does not exist.\n";
        return;
    }

    string line;
    cout << "\nRoutes in file:\n";
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

// Function to add a route to the file
void AddRouteToFile(const char* filename) {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cout << "Error opening file.\n";
        return;
    }

    string startPoint, endPoint, routeNumber;
    cin.ignore(); // Clear the buffer
    cout << "Enter start point: ";
    getline(cin, startPoint);
    cout << "Enter end point: ";
    getline(cin, endPoint);
    cout << "Enter route number: ";
    getline(cin, routeNumber);

    fout << startPoint << ";" << endPoint << ";" << routeNumber << endl;
    cout << "Route added successfully.\n";
    fout.close();
}

// Function to search for routes by a specific point
void SearchRoutes(const char* filename, const string& point) {
    ifstream fin(filename);
    if (!fin || IsFileEmpty(filename)) {
        cout << "File is empty or does not exist.\n";
        return;
    }

    string line;
    vector<string> matchingRoutes;
    while (getline(fin, line)) {
        size_t startIdx = line.find(point + ";");
        size_t endIdx = line.rfind(";" + point);
        if (startIdx == 0 || endIdx != string::npos) {
            matchingRoutes.push_back(line);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "No routes found for the point: " << point << endl;
    }
    else {
        cout << "\nRoutes matching point \"" << point << "\":\n";
        for (const auto& route : matchingRoutes) {
            cout << route << endl;
        }
    }
    fin.close();
}

// Function to check if the file is empty
bool IsFileEmpty(const char* filename) {
    ifstream fin(filename, ios::ate);
    return fin.tellg() == 0;
}
