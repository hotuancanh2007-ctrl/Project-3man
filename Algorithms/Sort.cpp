#include "Sort.h"

void selectionSortSectionsByName(CourseSectionList &list) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    for (SectionNode* i = list.head; i->next != nullptr; i = i->next) {
        SectionNode* minNode = i;

        for (SectionNode* j = i->next; j != nullptr; j = j->next) {
            if (j->data.sectionName < minNode->data.sectionName) {
                minNode = j;
            }
        }

        if (minNode != i) {
            CourseSection tempData = i->data;
            i->data = minNode->data;
            minNode->data = tempData;

            RegistrationList tempReg = i->registrations;
            i->registrations = minNode->registrations;
            minNode->registrations = tempReg;

            Queue tempSenior = i->seniorQueue;
            i->seniorQueue = minNode->seniorQueue;
            minNode->seniorQueue = tempSenior;

            Queue tempNormal = i->normalQueue;
            i->normalQueue = minNode->normalQueue;
            minNode->normalQueue = tempNormal;
        }
    }
}
