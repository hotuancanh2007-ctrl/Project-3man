#ifndef COURSE_SECTION_LIST_H
#define COURSE_SECTION_LIST_H

#include "../Models/CourseSection.h"

struct CourseSectionList {
    SectionNode* head;
    SectionNode* tail;
    int size;
};

void initSectionList(CourseSectionList &list);
SectionNode* createSectionNode(CourseSection data);
bool isValidSection(CourseSection data);

SectionNode* findSectionById(CourseSectionList list, string sectionId);
bool addSection(CourseSectionList &list, CourseSection data);
bool removeSection(CourseSectionList &list, string sectionId);
bool updateSectionInfo(CourseSectionList &list, CourseSection newData);
bool setSectionStatus(CourseSectionList &list, string sectionId, bool isOpen);

bool increaseEnrolled(CourseSectionList &list, string sectionId);
bool decreaseEnrolled(CourseSectionList &list, string sectionId);

void clearSectionList(CourseSectionList &list);

#endif
