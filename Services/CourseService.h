#ifndef COURSE_SERVICE_H
#define COURSE_SERVICE_H

#include "../DataStructures/CourseList.h"
#include "../DataStructures/CourseSectionList.h"

bool removeCourse(CourseList &cList, CourseSectionList sList, string courseId);

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
