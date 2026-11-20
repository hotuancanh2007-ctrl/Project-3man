#include "CompletedCourseList.h"
#include <iostream>

using namespace std;

void initCompletedCourseList(CompletedCourseList& list)
{
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

bool isCompletedCourseListEmpty(const CompletedCourseList& list)
{
    return list.head == nullptr;
}

bool hasCompletedCourse(const CompletedCourseList& list,
                        const string& MSSV,
                        const string& courseId)
{
    if (MSSV.empty() || courseId.empty())
        return false;

    CompletedCourseNode* current = list.head;

    while (current != nullptr)
    {
        if (current->data.MSSV == MSSV &&
            current->data.courseId == courseId)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool addCompletedCourse(CompletedCourseList& list,
                        const string& MSSV,
                        const string& courseId)
{
    if (MSSV.empty() || courseId.empty())
        return false;

    if (hasCompletedCourse(list, MSSV, courseId))
        return false;

    CompletedCourseNode* newNode = new CompletedCourseNode;
    newNode->data.MSSV = MSSV;
    newNode->data.courseId = courseId;
    newNode->next = nullptr;

    if (list.head == nullptr)
    {
        list.head = newNode;
        list.tail = newNode;
    }
    else
    {
        list.tail->next = newNode;
        list.tail = newNode;
    }

    ++list.size;
    return true;
}

bool removeCompletedCourse(CompletedCourseList& list,
                           const string& MSSV,
                           const string& courseId)
{
    CompletedCourseNode* current = list.head;
    CompletedCourseNode* previous = nullptr;

    while (current != nullptr)
    {
        if (current->data.MSSV == MSSV &&
            current->data.courseId == courseId)
        {
            if (previous == nullptr)
                list.head = current->next;
            else
                previous->next = current->next;

            if (current == list.tail)
                list.tail = previous;

            delete current;
            --list.size;

            if (list.head == nullptr)
                list.tail = nullptr;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

int removeAllCompletedCoursesByStudent(CompletedCourseList& list,
                                       const string& MSSV)
{
    int removedCount = 0;
    CompletedCourseNode* current = list.head;
    CompletedCourseNode* previous = nullptr;

    while (current != nullptr)
    {
        if (current->data.MSSV == MSSV)
        {
            CompletedCourseNode* nodeToDelete = current;
            current = current->next;

            if (previous == nullptr)
                list.head = current;
            else
                previous->next = current;

            if (nodeToDelete == list.tail)
                list.tail = previous;

            delete nodeToDelete;
            --list.size;
            ++removedCount;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (list.head == nullptr)
        list.tail = nullptr;

    return removedCount;
}

void printCompletedCoursesByStudent(const CompletedCourseList& list,
                                    const string& MSSV)
{
    CompletedCourseNode* current = list.head;
    bool found = false;

    cout << "Cac mon da hoan thanh cua sinh vien " << MSSV << ":\n";

    while (current != nullptr)
    {
        if (current->data.MSSV == MSSV)
        {
            cout << "- " << current->data.courseId << '\n';
            found = true;
        }

        current = current->next;
    }

    if (!found)
        cout << "Sinh vien chua co mon hoc hoan thanh nao.\n";
}

void clearCompletedCourseList(CompletedCourseList& list)
{
    CompletedCourseNode* current = list.head;

    while (current != nullptr)
    {
        CompletedCourseNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}
