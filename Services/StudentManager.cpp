#include "./StudentManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;

// ============================================================
//  Validation
// ============================================================

bool isValidMSSV(const string &mssv)
{
    if (mssv.length() != 8)
        return false;
    for (char c : mssv)
        if (!isdigit(c))
            return false;
    return true;
}

bool isValidName(const string &name)
{
    if (name.empty())
        return false;
    // Hỗ trợ UTF-8 tiếng Việt: cho phép byte >= 0x80 (multi-byte)
    // Chỉ từ chối ký tự ASCII đặc biệt (không phải chữ, số, khoảng trắng)
    for (unsigned char c : name)
    {
        if (c >= 128)
            continue; // UTF-8 multi-byte
        if (!isalpha(c) && !isspace(c))
            return false;
    }
    return true;
}

bool isValidYear(int year)
{
    return (year >= 1 && year <= 6);
}

// ============================================================
//  CRUD
// ============================================================

void addStudent(HashTable &ht, const string &mssv, const string &name, int year)
{
    if (!isValidMSSV(mssv))
    {
        cout << "[Loi] MSSV phai co dung 8 chu so!\n";
        return;
    }
    if (!isValidName(name))
    {
        cout << "[Loi] Ho ten khong hop le (khong duoc rong, chi chua chu va khoang trang)!\n";
        return;
    }
    if (!isValidYear(year))
    {
        cout << "[Loi] Nam hoc phai tu 1 den 6!\n";
        return;
    }
    if (IsDuplicate(ht, mssv))
    {
        cout << "[Loi] MSSV " << mssv << " da ton tai trong he thong!\n";
        return;
    }
    Student s;
    s.MSSV = mssv;
    s.FullName = name;
    s.SchoolYears = year;
    insert(ht, s);
    cout << "\n[Thanh cong] Da them sinh vien: " << name << " (MSSV: " << mssv << ")\n";
}

void updateStudent(HashTable &ht, const string &mssv, const string &newName, int newYear)
{
    StudentNode *node = searchStudent(ht, mssv);
    if (node == nullptr)
    {
        cout << "[Loi] Khong tim thay sinh vien co MSSV: " << mssv << "\n";
        return;
    }
    if (!isValidName(newName))
    {
        cout << "[Loi] Ho ten moi khong hop le!\n";
        return;
    }
    if (!isValidYear(newYear))
    {
        cout << "[Loi] Nam hoc moi phai tu 1 den 6!\n";
        return;
    }
    node->data.FullName = newName;
    node->data.SchoolYears = newYear;
    cout << "\n[Thanh cong] Da cap nhat thong tin sinh vien MSSV: " << mssv << "\n";
}

void removeStudent(HashTable &ht, const string &mssv)
{
    if (!isValidMSSV(mssv))
    {
        cout << "[Loi] MSSV khong hop le!\n";
        return;
    }
    if (deleteStudent(ht, mssv))
        cout << "\n[Thanh cong] Da xoa sinh vien co MSSV: " << mssv << "\n";
    else
        cout << "\n[Loi] Khong tim thay sinh vien co MSSV: " << mssv << "\n";
}

void findStudent(HashTable &ht, const string &mssv)
{
    StudentNode *node = searchStudent(ht, mssv);
    if (node == nullptr)
    {
        cout << "\n[Thong bao] Khong tim thay sinh vien co MSSV: " << mssv << "\n";
        return;
    }
    cout << "\n========== THONG TIN SINH VIEN ==========\n";
    cout << left
         << setw(12) << "MSSV"
         << setw(30) << "Ho va ten"
         << setw(10) << "Nam hoc" << "\n";
    cout << string(52, '-') << "\n";
    cout << left
         << setw(12) << node->data.MSSV
         << setw(30) << node->data.FullName
         << setw(10) << node->data.SchoolYears << "\n";
    cout << string(52, '=') << "\n";
}

void listAllStudents(HashTable &ht)
{
    cout << "\n========== DANH SACH SINH VIEN ==========\n";
    cout << left
         << setw(5)  << "STT"
         << setw(12) << "MSSV"
         << setw(30) << "Ho va ten"
         << setw(10) << "Nam hoc" << "\n";
    cout << string(57, '-') << "\n";

    int count = 0;
    for (int i = 0; i < ht.capacity; i++)
    {
        StudentNode *p = ht.buckets[i];
        while (p != nullptr)
        {
            count++;
            cout << left
                 << setw(5)  << count
                 << setw(12) << p->data.MSSV
                 << setw(30) << p->data.FullName
                 << setw(10) << p->data.SchoolYears << "\n";
            p = p->next;
        }
    }

    if (count == 0)
        cout << "   (Chua co sinh vien nao trong he thong)\n";

    cout << string(57, '=') << "\n";
    cout << "Tong so: " << count << " sinh vien\n";
}

// ============================================================
//  File I/O
// ============================================================

// Trim ký tự \r và khoảng trắng cuối dòng
static string trimLine(const string &s)
{
    string result = s;
    while (!result.empty() && (result.back() == '\r' || result.back() == '\n' || result.back() == ' '))
        result.pop_back();
    return result;
}

bool loadStudentsFromFile(HashTable &ht, const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "[Loi] Khong mo duoc file: " << filename << "\n";
        return false;
    }

    string line;
    int loaded = 0, skipped = 0;
    while (getline(fin, line))
    {
        line = trimLine(line);
        if (line.empty())
            continue;

        // Parse: MSSV|HoTen|NamHoc
        size_t pos1 = line.find('|');
        if (pos1 == string::npos) { skipped++; continue; }

        size_t pos2 = line.find('|', pos1 + 1);
        if (pos2 == string::npos) { skipped++; continue; }

        string mssv    = line.substr(0, pos1);
        string fullName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string yearStr  = line.substr(pos2 + 1);

        // Validate
        int year = 0;
        bool validYear = true;
        for (char c : yearStr)
            if (!isdigit(c)) { validYear = false; break; }
        if (!validYear || yearStr.empty()) { skipped++; continue; }

        year = stoi(yearStr);
        if (!isValidMSSV(mssv) || fullName.empty() || !isValidYear(year))
        {
            skipped++;
            continue;
        }
        if (!IsDuplicate(ht, mssv))
        {
            Student s;
            s.MSSV = mssv;
            s.FullName = fullName;
            s.SchoolYears = year;
            insert(ht, s);
            loaded++;
        }
        else
            skipped++;
    }
    fin.close();
    cout << "[File] Da tai " << loaded << " sinh vien tu " << filename;
    if (skipped > 0)
        cout << " (" << skipped << " dong bi bo qua)";
    cout << "\n";
    return true;
}

bool saveStudentsToFile(HashTable &ht, const string &filename)
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        cout << "[Loi] Khong ghi duoc file: " << filename << "\n";
        return false;
    }

    int count = 0;
    for (int i = 0; i < ht.capacity; i++)
    {
        StudentNode *p = ht.buckets[i];
        while (p != nullptr)
        {
            fout << p->data.MSSV << "|"
                 << p->data.FullName << "|"
                 << p->data.SchoolYears << "\n";
            count++;
            p = p->next;
        }
    }
    fout.close();
    cout << "[File] Da luu " << count << " sinh vien vao " << filename << "\n";
    return true;
}

// ============================================================
//  Sinh dữ liệu lớn (để kiểm thử Hash Table)
// ============================================================

void generateLargeData(HashTable &ht, int count)
{
    cout << "[Generate] Dang sinh " << count << " ban ghi sinh vien...\n";
    int added = 0;
    for (int i = 1; i <= count; i++)
    {
        // MSSV: 8 chu so, bat dau tu 20000001
        ostringstream mssvStream;
        int mssvNum = 20000000 + i;
        mssvStream << mssvNum;
        string mssv = mssvStream.str();

        // Ten: "Sinh Vien X"
        ostringstream nameStream;
        nameStream << "Sinh Vien " << i;
        string name = nameStream.str();

        int year = (i % 4) + 1;

        if (!IsDuplicate(ht, mssv))
        {
            Student s;
            s.MSSV = mssv;
            s.FullName = name;
            s.SchoolYears = year;
            insert(ht, s);
            added++;
        }
    }
    cout << "[Generate] Hoan thanh: da them " << added << " sinh vien.\n";
}
