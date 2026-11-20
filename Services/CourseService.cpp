#include "CourseService.h"
#include <fstream>
#include <sstream>

string cleanString(string s) {
    if (!s.empty() && s[s.length() - 1] == '\r') {
        s.erase(s.length() - 1);
    }
    return s;
}

int stringToInt(string s) {
    s = cleanString(s);
    if (s == "") return -1;

    int result = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return -1;
        result = result * 10 + (s[i] - '0');
    }
    return result;
}

bool removeCourse(CourseList &cList, CourseSectionList sList, string courseId) {
    if (cList.head == nullptr) return false;

    SectionNode* secCurr = sList.head;
    while (secCurr != nullptr) {
        if (secCurr->data.courseId == courseId) {
            return false;
        }
        secCurr = secCurr->next;
    }

    return deleteCourseById(cList, courseId);
}

bool addSectionWithCheck(CourseList cList, CourseSectionList &sList, CourseSection data) {
    if (findCourseById(cList, data.courseId) == nullptr) {
        return false;
    }
    return addSection(sList, data);
}

CourseSectionList getAvailableSectionsByCourse(CourseSectionList sList, string courseId) {
    CourseSectionList result;
    initSectionList(result);

    SectionNode* curr = sList.head;
    while (curr != nullptr) {
        if (curr->data.courseId == courseId &&
            curr->data.isOpen == true &&
            curr->data.currentEnrolled < curr->data.maxCapacity) {
            addSection(result, curr->data);
        }
        curr = curr->next;
    }
    return result;
}

string getPrerequisiteCourseId(CourseList cList, string courseId) {
    CourseNode* node = findCourseById(cList, courseId);
    if (node == nullptr) return "NONE";
    return node->data.prerequisiteId;
}

bool isScheduleConflict(CourseSection secA, CourseSection secB) {
    if (secA.dayOfWeek != secB.dayOfWeek) return false;

    int endA = secA.startPeriod + secA.numPeriods - 1;
    int endB = secB.startPeriod + secB.numPeriods - 1;

    if (secA.startPeriod <= endB && secB.startPeriod <= endA) {
        return true;
    }
    return false;
}

int getSectionCredits(CourseList cList, CourseSectionList sList, string sectionId) {
    SectionNode* secNode = findSectionById(sList, sectionId);
    if (secNode == nullptr) return 0;

    CourseNode* courseNode = findCourseById(cList, secNode->data.courseId);
    if (courseNode == nullptr) return 0;

    return courseNode->data.credits;
}

bool loadCoursesFromFile(CourseList &cList, string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    clearCourseList(cList);

    string line;
    while (getline(file, line)) {
        line = cleanString(line);
        if (line == "") continue;

        stringstream ss(line);
        Course c;
        string creditsStr;

        getline(ss, c.courseId, '|');
        getline(ss, c.courseName, '|');
        getline(ss, creditsStr, '|');
        getline(ss, c.prerequisiteId, '|');

        c.courseId = cleanString(c.courseId);
        c.courseName = cleanString(c.courseName);
        c.prerequisiteId = cleanString(c.prerequisiteId);
        c.credits = stringToInt(creditsStr);

        if (c.credits > 0) {
            addCourse(cList, c);
        }
    }
    file.close();
    return true;
}

bool saveCoursesToFile(CourseList cList, string filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        file << curr->data.courseId << "|"
             << curr->data.courseName << "|"
             << curr->data.credits << "|"
             << curr->data.prerequisiteId << "\n";
        curr = curr->next;
    }
    file.close();
    return true;
}

bool loadSectionsFromFile(CourseList cList, CourseSectionList &sList, string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    clearSectionList(sList);

    string line;
    while (getline(file, line)) {
        line = cleanString(line);
        if (line == "") continue;

        stringstream ss(line);
        CourseSection sec;
        string maxCapStr, curEnrStr, dayStr, startStr, numPerStr, openStr;

        getline(ss, sec.sectionId, '|');
        getline(ss, sec.courseId, '|');
        getline(ss, sec.sectionName, '|');
        getline(ss, maxCapStr, '|');
        getline(ss, curEnrStr, '|');
        getline(ss, dayStr, '|');
        getline(ss, startStr, '|');
        getline(ss, numPerStr, '|');
        getline(ss, openStr, '|');

        sec.sectionId = cleanString(sec.sectionId);
        sec.courseId = cleanString(sec.courseId);
        sec.sectionName = cleanString(sec.sectionName);
        openStr = cleanString(openStr);

        sec.maxCapacity = stringToInt(maxCapStr);
        sec.currentEnrolled = stringToInt(curEnrStr);
        sec.dayOfWeek = stringToInt(dayStr);
        sec.startPeriod = stringToInt(startStr);
        sec.numPeriods = stringToInt(numPerStr);
        sec.isOpen = (openStr == "1");

        if (cList.head != nullptr) {
            addSectionWithCheck(cList, sList, sec);
        } else {
            addSection(sList, sec);
        }
    }
    file.close();
    return true;
}

bool saveSectionsToFile(CourseSectionList sList, string filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    SectionNode* curr = sList.head;
    while (curr != nullptr) {
        file << curr->data.sectionId << "|"
             << curr->data.courseId << "|"
             << curr->data.sectionName << "|"
             << curr->data.maxCapacity << "|"
             << curr->data.currentEnrolled << "|"
             << curr->data.dayOfWeek << "|"
             << curr->data.startPeriod << "|"
             << curr->data.numPeriods << "|"
             << (curr->data.isOpen ? 1 : 0) << "\n";
        curr = curr->next;
    }
    file.close();
    return true;
}
