#include "./RegistrationService.h"

bool isStudentExists(HashTable &students, string MSSV)
{
    return searchStudent(students, MSSV) != nullptr;
}

bool isAlreadyRegistered(CourseSectionList &sections, string MSSV, string sectionID)
{
    SectionNode *section = findSectionById(sections, sectionID);
    if (section == nullptr)
        return false;

    return searchRegistration(section->registrations, MSSV, sectionID) != nullptr;
}
bool isAlreadyWaiting(
    CourseSectionList &sections,
    string MSSV,
    string sectionID)
{
    SectionNode *section = findSectionById(sections, sectionID);

    if (section == nullptr)
        return false;

    if (isInQueue(section->seniorQueue, MSSV))
        return true;

    if (isInQueue(section->normalQueue, MSSV))
        return true;

    return false;
}
bool isInQueue(Queue &q, string MSSV)
{
    WaitNode *p = q.front;
    while (p != nullptr && p->MSSV != MSSV)
    {
        p = p->next;
    }
    return p != nullptr;
}
// bool checkPrerequisite(
//     CourseList &courses,
//     CompletedCourseList &completedCourses,
//     string MSSV,
//     string courseID)
// {
//     CourseNode *course =

//     if (section == nullptr)
//         return false;
// }

bool isSectionAvailable(
    CourseSectionList &sections,
    string sectionID)
{
    SectionNode *section = findSectionById(sections, sectionID);

    if (section == nullptr)
        return false;
    return section->data.isOpen;
}
bool isSectionFull(
    CourseSectionList &sections,
    string sectionID)
{
    SectionNode *section = findSectionById(sections, sectionID);

    if (section == nullptr)
        return false;
    return section->data.currentEnrolled >= section->data.maxCapacity;
}
bool isSeniorStudent(
    HashTable &students,
    string MSSV)
{
    StudentNode *p = searchStudent(students, MSSV);
    if (p == nullptr)
        return false;
    return p->data.SchoolYears == 4;
}
bool checkCreditLimit(
    int currentCredits,
    int newCredits)
{
    return currentCredits + newCredits <= 25;
}
int calculateStudentCredits(
    CourseList &courses,
    CourseSectionList &sections,
    string MSSV)
{
    SectionNode *p = sections.head;
    int total = 0;
    while (p != nullptr)
    {
        RegistrationNode *r = searchRegistration(p->registrations, MSSV, p->data.sectionId);
        if (r != nullptr)
        {
            CourseNode *course = findCourseById(
                courses,
                p->data.courseId);
            if (course != nullptr)
            {
                total += course->data.credits;
            }
        }
        p = p->next;
    }
    return total;
}
bool isScheduleConflict(
    CourseSectionList &sections,
    string MSSV,
    string newSectionID)
{
    // Tìm lớp học phần mới
    SectionNode *newSection = findSectionById(sections, newSectionID);

    if (newSection == nullptr)
        return false;

    // Duyệt tất cả lớp học phần
    SectionNode *p = sections.head;

    while (p != nullptr)
    {

        // Bỏ qua chính lớp đang muốn đăng ký
        if (p->data.sectionId != newSectionID)
        {

            // Kiểm tra sinh viên đã đăng ký lớp này chưa
            if (searchRegistration(p->registrations, MSSV, p->data.sectionId) != nullptr)
            {

                if (p->data.dayOfWeek == newSection->data.dayOfWeek)
                {

                    int oldStart = p->data.startPeriod;
                    int oldEnd = oldStart + p->data.numPeriods - 1;

                    int newStart = newSection->data.startPeriod;
                    int newEnd = newStart + newSection->data.numPeriods - 1;

                    if (oldStart <= newEnd && newStart <= oldEnd)
                        return true;
                }
            }
        }

        p = p->next;
    }

    return false;
}
RegistrationResult registerForSection(
    HashTable &students,
    CourseList &courses,
    CourseSectionList &sections,
    CompletedCourseList &completedCourses,
    string MSSV,
    string sectionID)
{
    if (!isStudentExists(students, MSSV))
        return STUDENT_NOT_FOUND;
    SectionNode *s = findSectionById(sections, sectionID);

    if (s == nullptr)
        return SECTION_NOT_FOUND;

    CourseNode *c = findCourseById(courses, s->data.courseId);

    if (c == nullptr)
        return FAILED;
    if (!isSectionAvailable(sections, sectionID))
        return SECTION_CLOSED;
    if (isAlreadyRegistered(sections, MSSV, sectionID) || isAlreadyWaiting(sections, MSSV, sectionID))
        return ALREADY_REGISTERED;
    if (c->data.prerequisiteId != "" &&
        c->data.prerequisiteId != "NONE")
    {
        if (!checkPrerequisiteCompleted(
                completedCourses,
                MSSV,
                c->data.prerequisiteId))
        {
            return PREREQUISITE_NOT_MET;
        }
    }
    if (isScheduleConflict(sections, MSSV, sectionID))
        return SCHEDULE_CONFLICT;

    if (!checkCreditLimit(calculateStudentCredits(courses, sections, MSSV), c->data.credits))
        return CREDIT_LIMIT_EXCEEDED;
    if (isSectionFull(sections, sectionID))
    {
        if (isSeniorStudent(students, MSSV))
        {
            if (!enqueue(s->seniorQueue, MSSV))
                return FAILED;
        }
        else
        {
            if (!enqueue(s->normalQueue, MSSV))
                return FAILED;
        }

        return WAITING;
    }
    else
    {
        if (!addTail(s->registrations, MSSV, sectionID))
            return FAILED;

        if (!increaseEnrolled(sections, sectionID))
        {
            removeRegistration(s->registrations, MSSV, sectionID);
            return FAILED;
        }
    }
    return SUCCESS;
}
