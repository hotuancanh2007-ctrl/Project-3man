#ifndef COURSE_SECTION_H
#define COURSE_SECTION_H

#include <string>
#include "../DataStructures/RegistrationList.h"
#include "../DataStructures/Queue.h"

using namespace std;

struct CourseSection {
    string sectionId;
    string courseId;
    string sectionName;
    int maxCapacity;
    int currentEnrolled;
    int dayOfWeek;
    int startPeriod;
    int numPeriods;
    bool isOpen;
};

struct SectionNode {
    CourseSection data;

    RegistrationList registrations;
    Queue seniorQueue;
    Queue normalQueue;

    SectionNode* next;
};

#endif
