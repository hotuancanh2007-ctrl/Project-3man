#ifndef COMPLETED_COURSE_H
#define COMPLETED_COURSE_H

#include <string>
using namespace std;

// Một môn học mà sinh viên đã hoàn thành và đạt yêu cầu.
struct CompletedCourse
{
    string MSSV;
    string courseId;
};

struct CompletedCourseNode
{
    CompletedCourse data;
    CompletedCourseNode* next;
};

#endif
