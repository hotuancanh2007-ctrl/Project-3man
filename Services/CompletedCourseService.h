#ifndef COMPLETED_COURSE_SERVICE_H
#define COMPLETED_COURSE_SERVICE_H

#include "CompletedCourseList.h"
#include <string>
using namespace std;

// Đọc file có định dạng: MSSV|courseId
// Dòng sai định dạng hoặc bị trùng sẽ được bỏ qua.
bool loadCompletedCoursesFromFile(CompletedCourseList& list,
                                  const string& filename);

// Ghi toàn bộ danh sách ra file theo định dạng: MSSV|courseId
bool saveCompletedCoursesToFile(const CompletedCourseList& list,
                                const string& filename);

// Hàm tiện ích: kiểm tra điều kiện tiên quyết.
// prerequisiteId rỗng hoặc "NONE" nghĩa là môn không có môn tiên quyết.
bool checkPrerequisiteCompleted(const CompletedCourseList& list,
                                const string& MSSV,
                                const string& prerequisiteId);

#endif
