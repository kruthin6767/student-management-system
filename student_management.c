#include <stdio.h>

#define MAX_STUDENTS 100

// Structure to store student information
struct Student {
    int rollNo;
    char name[50];
    char year[20];
    char branch[50];
    char section[10];
    float marks;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Save students to file
void saveStudents() {
    FILE *file = fopen("student.txt", "w");

    if (file == NULL) {
        printf("\nError: Could not save student data!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%.2f\n",
                students[i].rollNo,
                students[i].name,
                students[i].year,
                students[i].branch,
                students[i].section,
                students[i].marks);
    }

    fclose(file);
}

// Load students from file
void loadStudents() {
    FILE *file = fopen("student.txt", "r");

    if (file == NULL) {
        return;
    }

    while (studentCount < MAX_STUDENTS &&
           fscanf(file, "%d|%49[^|]|%19[^|]|%49[^|]|%9[^|]|%f\n",
                  &students[studentCount].rollNo,
                  students[studentCount].name,
                  students[studentCount].year,
                  students[studentCount].branch,
                  students[studentCount].section,
                  &students[studentCount].marks) == 6) {

        studentCount++;
    }

    fclose(file);
}

// Add a student
void addStudent() {

    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &students[studentCount].rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", students[studentCount].name);

    printf("Enter Year: ");
    scanf(" %[^\n]", students[studentCount].year);

    printf("Enter Branch: ");
    scanf(" %[^\n]", students[studentCount].branch);

    printf("Enter Section: ");
    scanf(" %[^\n]", students[studentCount].section);

    printf("Enter Marks: ");
    scanf("%f", &students[studentCount].marks);

    studentCount++;

    // Save immediately after adding
    saveStudents();

    printf("\nStudent added successfully!\n");
}

// Display all students
void displayStudents() {

    if (studentCount == 0) {
        printf("\nNo students found!\n");
        return;
    }

    printf("\n----- Student Details -----\n");

    for (int i = 0; i < studentCount; i++) {

        printf("\nRoll Number: %d", students[i].rollNo);
        printf("\nName: %s", students[i].name);
        printf("\nYear: %s", students[i].year);
        printf("\nBranch: %s", students[i].branch);
        printf("\nSection: %s", students[i].section);
        printf("\nMarks: %.2f\n", students[i].marks);
    }
}

// Search for a student
void searchStudent() {

    int rollNo;
    int found = 0;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].rollNo == rollNo) {

            printf("\nStudent Found!\n");

            printf("Roll Number: %d\n", students[i].rollNo);
            printf("Name: %s\n", students[i].name);
            printf("Year: %s\n", students[i].year);
            printf("Branch: %s\n", students[i].branch);
            printf("Section: %s\n", students[i].section);
            printf("Marks: %.2f\n", students[i].marks);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent not found!\n");
    }
}

// Delete a student
void deleteStudent() {

    int rollNo;
    int found = 0;

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].rollNo == rollNo) {

            // Move remaining students one position back
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;
            found = 1;

            // Save updated list
            saveStudents();

            printf("\nStudent deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\nStudent not found!\n");
    }
}

// Main function
int main() {

    int choice;

    // Load previously saved students
    loadStudents();

    while (1) {

        printf("\n\n===== STUDENT MANAGEMENT SYSTEM =====");

        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Delete Student");
        printf("\n5. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                printf("\nThank you!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}