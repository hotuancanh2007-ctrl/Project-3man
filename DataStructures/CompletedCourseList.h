#ifndef COMPLETED_COURSE_LIST_H
#define COMPLETED_COURSE_LIST_H

#include "CompletedCourse.h"

// Danh sách liên kết đơn lưu các môn sinh viên đã hoàn thành.
struct CompletedCourseList
{
    CompletedCourseNode *head;
    CompletedCourseNode *tail;
    int size;
};

void initCompletedCourseList(CompletedCourseList &list);
bool isCompletedCourseListEmpty(const CompletedCourseList &list);

// Thêm một cặp MSSV-courseId. Trả false nếu dữ liệu rỗng hoặc đã tồn tại.
bool addCompletedCourse(CompletedCourseList &list,
                        const string &MSSV,
                        const string &courseId);

// Kiểm tra sinh viên đã hoàn thành môn học chưa.
bool hasCompletedCourse(const CompletedCourseList &list,
                        const string &MSSV,
                        const string &courseId);

// Xóa một môn đã hoàn thành của một sinh viên.
bool removeCompletedCourse(CompletedCourseList &list,
                           const string &MSSV,
                           const string &courseId);

// Xóa toàn bộ môn đã hoàn thành của một sinh viên.
int removeAllCompletedCoursesByStudent(CompletedCourseList &list,
                                       const string &MSSV);

void printCompletedCoursesByStudent(const CompletedCourseList &list,
                                    const string &MSSV);
void clearCompletedCourseList(CompletedCourseList &list);

#endif
