#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

struct Course {
    string courseId;
    string courseName;
    int credits;
    string prerequisiteId;
};

struct CourseNode {
    Course data;
    CourseNode* next;
};

struct CourseList {
    CourseNode* head;
    CourseNode* tail;
    int size;
};

#endif
