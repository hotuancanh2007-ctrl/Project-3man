#ifndef REGISTRATION_SERVICE_H
#define REGISTRATION_SERVICE_H

#include "../Models/Registration.h"
#include "../Models/Course.h"
#include "../DataStructures/HashTable.h"
#include "../DataStructures/CourseSectionList.h"
#include "../DataStructures/CompletedCourseList.h"
#include "../DataStructures/CourseList.h"
#include "./CompletedCourseService.h"

#include <string>
using namespace std;

enum RegistrationResult
{
    SUCCESS,
    WAITING,
    STUDENT_NOT_FOUND,
    SECTION_NOT_FOUND,
    SECTION_CLOSED,
    ALREADY_REGISTERED,
    PREREQUISITE_NOT_MET,
    SCHEDULE_CONFLICT,
    CREDIT_LIMIT_EXCEEDED,
    FAILED
};
bool isStudentExists(HashTable &students, string MSSV);
bool isAlreadyRegistered(CourseSectionList &sections, string MSSV, string sectionID);
bool isAlreadyWaiting(CourseSectionList &sections, string MSSV, string sectionID);
bool isInQueue(Queue &q, string MSSV);
bool checkPrerequisite(
    CourseList &courses,
    CompletedCourseList &completedCourses,
    string MSSV,
    string courseID);
bool isSectionAvailable(
    CourseSectionList &sections,
    string sectionID);
bool isSectionFull(
    CourseSectionList &sections,
    string sectionID);
bool isSeniorStudent(
    HashTable &students,
    string MSSV);
bool checkCreditLimit(
    int currentCredits,
    int newCredits);

int calculateStudentCredits(
    CourseList &courses,
    CourseSectionList &sections,
    string MSSV);

bool isScheduleConflict(CourseSectionList &sections,
                        string MSSV,
                        string newSectionID);

RegistrationResult registerForSection(
    HashTable &students,
    CourseList &courses,
    CourseSectionList &sections,
    CompletedCourseList &completedCourses,
    string MSSV,
    string sectionID);

#endif