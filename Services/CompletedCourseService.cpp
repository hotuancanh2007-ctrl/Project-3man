#include "CompletedCourseService.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

static string trim(const string& value)
{
    const string whitespace = " \t\r\n";
    size_t first = value.find_first_not_of(whitespace);

    if (first == string::npos)
        return "";

    size_t last = value.find_last_not_of(whitespace);
    return value.substr(first, last - first + 1);
}

bool loadCompletedCoursesFromFile(CompletedCourseList& list,
                                  const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
        return false;

    // Gọi hàm này trên danh sách đã được khởi tạo.
    // Nạp lại file sẽ thay thế dữ liệu cũ trong danh sách.
    clearCompletedCourseList(list);

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        size_t separator = line.find('|');

        // Chỉ chấp nhận đúng một dấu phân cách.
        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos)
        {
            continue;
        }

        string MSSV = trim(line.substr(0, separator));
        string courseId = trim(line.substr(separator + 1));

        if (MSSV.empty() || courseId.empty())
            continue;

        addCompletedCourse(list, MSSV, courseId);
    }

    return !inFile.bad();
}

bool saveCompletedCoursesToFile(const CompletedCourseList& list,
                                const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
        return false;

    CompletedCourseNode* current = list.head;

    while (current != nullptr)
    {
        outFile << current->data.MSSV
                << '|'
                << current->data.courseId
                << '\n';

        current = current->next;
    }

    return outFile.good();
}

bool checkPrerequisiteCompleted(const CompletedCourseList& list,
                                const string& MSSV,
                                const string& prerequisiteId)
{
    if (prerequisiteId.empty() || prerequisiteId == "NONE")
        return true;

    return hasCompletedCourse(list, MSSV, prerequisiteId);
}
