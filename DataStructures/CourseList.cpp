#include "CourseList.h"

void initCourseList(CourseList &cList) {
    cList.head = nullptr;
    cList.tail = nullptr;
    cList.size = 0;
}

CourseNode* createCourseNode(Course data) {
    if (data.prerequisiteId == "") {
        data.prerequisiteId = "NONE";
    }

    CourseNode* newNode = new CourseNode;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

bool isValidCourse(Course data) {
    if (data.courseId == "" || data.courseName == "") return false;
    if (data.credits <= 0) return false;
    return true;
}

CourseNode* findCourseById(CourseList cList, string courseId) {
    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        if (curr->data.courseId == courseId) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool addCourse(CourseList &cList, Course data) {
    if (!isValidCourse(data)) return false;
    if (findCourseById(cList, data.courseId) != nullptr) return false;

    CourseNode* newNode = createCourseNode(data);

    if (cList.head == nullptr) {
        cList.head = cList.tail = newNode;
    } else {
        cList.tail->next = newNode;
        cList.tail = newNode;
    }
    cList.size++;
    return true;
}

bool updateCourse(CourseList &cList, Course newData) {
    if (!isValidCourse(newData)) return false;

    CourseNode* node = findCourseById(cList, newData.courseId);
    if (node == nullptr) return false;

    if (newData.prerequisiteId == "") {
        newData.prerequisiteId = "NONE";
    }

    node->data = newData;
    return true;
}

bool deleteCourseById(CourseList &cList, string courseId) {
    if (cList.head == nullptr) return false;

    CourseNode* curr = cList.head;
    CourseNode* prev = nullptr;

    while (curr != nullptr && curr->data.courseId != courseId) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;

    if (curr == cList.head) {
        cList.head = cList.head->next;
        if (cList.head == nullptr) {
            cList.tail = nullptr;
        }
    } else {
        prev->next = curr->next;
        if (curr == cList.tail) {
            cList.tail = prev;
        }
    }

    delete curr;
    cList.size--;
    return true;
}

void clearCourseList(CourseList &cList) {
    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        CourseNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    cList.head = cList.tail = nullptr;
    cList.size = 0;
}
