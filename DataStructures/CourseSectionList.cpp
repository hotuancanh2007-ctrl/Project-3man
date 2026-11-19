#include "CourseSectionList.h"

void initSectionList(CourseSectionList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

SectionNode* createSectionNode(CourseSection data) {
    SectionNode* newNode = new SectionNode;
    newNode->data = data;
    initRegistrationList(newNode->registrations);
    initQueue(newNode->seniorQueue);
    initQueue(newNode->normalQueue);
    newNode->next = nullptr;
    return newNode;
}

bool isValidSection(CourseSection data) {
    if (data.sectionId == "" || data.courseId == "" || data.sectionName == "") return false;
    if (data.maxCapacity <= 0) return false;
    if (data.currentEnrolled < 0 || data.currentEnrolled > data.maxCapacity) return false;
    if (data.dayOfWeek < 2 || data.dayOfWeek > 8) return false;
    if (data.startPeriod < 1 || data.startPeriod > 12) return false;
    if (data.numPeriods < 1 || (data.startPeriod + data.numPeriods - 1) > 12) return false;
    return true;
}

SectionNode* findSectionById(CourseSectionList list, string sectionId) {
    SectionNode* curr = list.head;
    while (curr != nullptr) {
        if (curr->data.sectionId == sectionId) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool addSection(CourseSectionList &list, CourseSection data) {
    if (!isValidSection(data)) return false;
    if (findSectionById(list, data.sectionId) != nullptr) return false;

    SectionNode* newNode = createSectionNode(data);

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    } else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
    list.size++;
    return true;
}

bool removeSection(CourseSectionList &list, string sectionId) {
    if (list.head == nullptr) return false;

    SectionNode* curr = list.head;
    SectionNode* prev = nullptr;

    while (curr != nullptr && curr->data.sectionId != sectionId) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;
    if (curr->data.currentEnrolled > 0) return false;

    if (curr == list.head) {
        list.head = list.head->next;
        if (list.head == nullptr) {
            list.tail = nullptr;
        }
    } else {
        prev->next = curr->next;
        if (curr == list.tail) {
            list.tail = prev;
        }
    }

    destroyRegistrationList(curr->registrations);
    destroyQueue(curr->seniorQueue);
    destroyQueue(curr->normalQueue);

    delete curr;
    list.size--;
    return true;
}

bool updateSectionInfo(CourseSectionList &list, CourseSection newData) {
    if (!isValidSection(newData)) return false;

    SectionNode* node = findSectionById(list, newData.sectionId);
    if (node == nullptr) return false;
    if (node->data.courseId != newData.courseId) return false;

    node->data = newData;
    return true;
}

bool setSectionStatus(CourseSectionList &list, string sectionId, bool isOpen) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;

    node->data.isOpen = isOpen;
    return true;
}

bool increaseEnrolled(CourseSectionList &list, string sectionId) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;
    if (!node->data.isOpen) return false;
    if (node->data.currentEnrolled >= node->data.maxCapacity) return false;

    node->data.currentEnrolled++;
    return true;
}

bool decreaseEnrolled(CourseSectionList &list, string sectionId) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;
    if (node->data.currentEnrolled <= 0) return false;

    node->data.currentEnrolled--;
    return true;
}

void clearSectionList(CourseSectionList &list) {
    SectionNode* curr = list.head;
    while (curr != nullptr) {
        SectionNode* temp = curr;
        curr = curr->next;

        destroyRegistrationList(temp->registrations);
        destroyQueue(temp->seniorQueue);
        destroyQueue(temp->normalQueue);

        delete temp;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}
