#pragma once
#include "../DataStructures/HashTable.h"
#include <string>
#include <fstream>
using namespace std;

// ============================================================
//  TV1 - StudentManager: Quản lý sinh viên
//  Dùng struct + HashTable (Separate Chaining)
// ============================================================

// ---------- Validation ----------
bool isValidMSSV(const string &mssv);   // MSSV: đúng 8 chữ số
bool isValidName(const string &name);   // Không rỗng, chỉ chữ + khoảng trắng (hỗ trợ UTF-8)
bool isValidYear(int year);             // Năm học hợp lệ: 1..6

// ---------- CRUD ----------
void addStudent(HashTable &ht, const string &mssv, const string &name, int year);
void updateStudent(HashTable &ht, const string &mssv, const string &newName, int newYear);
void removeStudent(HashTable &ht, const string &mssv);
void findStudent(HashTable &ht, const string &mssv);
void listAllStudents(HashTable &ht);

// ---------- File I/O ----------
// Format mỗi dòng: MSSV|HoTen|NamHoc
bool loadStudentsFromFile(HashTable &ht, const string &filename);
bool saveStudentsToFile(HashTable &ht, const string &filename);

// ---------- Sinh dữ liệu lớn ----------
void generateLargeData(HashTable &ht, int count);
