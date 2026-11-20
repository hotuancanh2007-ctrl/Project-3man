#ifndef COURSE_LIST_H
#define COURSE_LIST_H

#include "../Models/Course.h"

struct CourseList {
    CourseNode* head;
    CourseNode* tail;
    int size;
};

void initCourseList(CourseList &cList);
CourseNode* createCourseNode(Course data);
bool isValidCourse(Course data);

CourseNode* findCourseById(CourseList cList, string courseId);
bool addCourse(CourseList &cList, Course data);
bool updateCourse(CourseList &cList, Course newData);
bool deleteCourseById(CourseList &cList, string courseId);
void clearCourseList(CourseList &cList);

#endif
