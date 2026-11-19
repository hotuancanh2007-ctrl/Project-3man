#ifndef COURSE_SERVICE_H
#define COURSE_SERVICE_H

#include "../Models/Course.h"
#include "../DataStructures/CourseSectionList.h"

void initCourseList(CourseList &cList);
CourseNode* findCourseById(CourseList cList, string courseId);
bool addCourse(CourseList &cList, Course data);
bool updateCourse(CourseList &cList, Course newData);
bool removeCourse(CourseList &cList, CourseSectionList sList, string courseId);
void clearCourseList(CourseList &cList);

bool addSectionWithCheck(CourseList cList, CourseSectionList &sList, CourseSection data);
CourseSectionList getAvailableSectionsByCourse(CourseSectionList sList, string courseId);

string getPrerequisiteCourseId(CourseList cList, string courseId);
bool isScheduleConflict(CourseSection secA, CourseSection secB);
int getSectionCredits(CourseList cList, CourseSectionList sList, string sectionId);

bool loadCoursesFromFile(CourseList &cList, string filename);
bool saveCoursesToFile(CourseList cList, string filename);
bool loadSectionsFromFile(CourseList cList, CourseSectionList &sList, string filename);
bool saveSectionsToFile(CourseSectionList sList, string filename);

#endif
