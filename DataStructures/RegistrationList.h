#pragma once
#include "../Models/Registration.h"
#include <iostream>
#include <iomanip>

void initRegistrationList(RegistrationList &l);
bool isEmpty(RegistrationList &l);
bool addTail(RegistrationList &l, string mssv, string sectionID);
RegistrationNode *searchRegistration(RegistrationList &l, string mssv, string sectionID);
bool removeRegistration(RegistrationList &l, string mssv, string sectionID);
void printRegistrationList(RegistrationList &l);
void destroyRegistrationList(RegistrationList &l);
bool isDuplicate(RegistrationList &l, string mssv, string sectionID);
void printRegistrationBySection(RegistrationList &l, string sectionID);