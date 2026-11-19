#pragma once
#include "../Services/StudentManager.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ============================================================
//  TV1 - StudentForm: Giao diện console quản lý sinh viên
// ============================================================

// Xóa buffer input sau khi nhập sai
static void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Hiển thị menu và xử lý tất cả chức năng quản lý sinh viên
void showStudentMenu(HashTable &ht)
{
    int choice = -1;
    do
    {
        cout << "\n";
        cout << "========================================\n";
        cout << "       QUAN LY SINH VIEN (TV1)         \n";
        cout << "========================================\n";
        cout << "  1. Them sinh vien moi\n";
        cout << "  2. Cap nhat thong tin sinh vien\n";
        cout << "  3. Xoa sinh vien\n";
        cout << "  4. Tim kiem sinh vien\n";
        cout << "  5. Hien thi tat ca sinh vien\n";
        cout << "  6. Luu du lieu ra file\n";
        cout << "  0. Quay lai menu chinh\n";
        cout << "========================================\n";
        cout << "Lua chon cua ban: ";

        if (!(cin >> choice))
        {
            clearInput();
            choice = -1;
            cout << "[Loi] Vui long nhap so nguyen!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        // ---- 1. Them sinh vien ----
        case 1:
        {
            cout << "\n--- THEM SINH VIEN MOI ---\n";
            string mssv, name;
            int year;

            cout << "Nhap MSSV (8 chu so): ";
            getline(cin, mssv);

            cout << "Nhap ho va ten: ";
            getline(cin, name);

            cout << "Nhap nam hoc (1-6): ";
            if (!(cin >> year))
            {
                clearInput();
                cout << "[Loi] Nam hoc khong hop le!\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            addStudent(ht, mssv, name, year);
            break;
        }

        // ---- 2. Cap nhat sinh vien ----
        case 2:
        {
            cout << "\n--- CAP NHAT THONG TIN SINH VIEN ---\n";
            string mssv, newName;
            int newYear;

            cout << "Nhap MSSV can cap nhat: ";
            getline(cin, mssv);

            // Kiem tra ton tai truoc
            if (searchStudent(ht, mssv) == nullptr)
            {
                cout << "[Loi] Khong tim thay sinh vien co MSSV: " << mssv << "\n";
                break;
            }

            cout << "Nhap ho ten moi: ";
            getline(cin, newName);

            cout << "Nhap nam hoc moi (1-6): ";
            if (!(cin >> newYear))
            {
                clearInput();
                cout << "[Loi] Nam hoc khong hop le!\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            updateStudent(ht, mssv, newName, newYear);
            break;
        }

        // ---- 3. Xoa sinh vien ----
        case 3:
        {
            cout << "\n--- XOA SINH VIEN ---\n";
            string mssv;
            cout << "Nhap MSSV can xoa: ";
            getline(cin, mssv);

            // Hien thi thong tin truoc khi xoa
            StudentNode *node = searchStudent(ht, mssv);
            if (node == nullptr)
            {
                cout << "[Loi] Khong tim thay sinh vien co MSSV: " << mssv << "\n";
                break;
            }
            cout << "Ten: " << node->data.FullName
                 << " | Nam hoc: " << node->data.SchoolYears << "\n";

            // Xac nhan
            char confirm;
            cout << "Ban co chac muon xoa? (Y/N): ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirm == 'Y' || confirm == 'y')
                removeStudent(ht, mssv);
            else
                cout << "[Huy] Thao tac xoa bi huy.\n";
            break;
        }

        // ---- 4. Tim kiem sinh vien ----
        case 4:
        {
            cout << "\n--- TIM KIEM SINH VIEN ---\n";
            string mssv;
            cout << "Nhap MSSV can tim: ";
            getline(cin, mssv);
            findStudent(ht, mssv);
            break;
        }

        // ---- 5. Hien thi tat ca ----
        case 5:
        {
            listAllStudents(ht);
            break;
        }

        // ---- 6. Luu file ----
        case 6:
        {
            cout << "\n--- LUU DU LIEU ---\n";
            if (saveStudentsToFile(ht, "Data/students.txt"))
                cout << "[OK] Da luu thanh cong vao Data/students.txt\n";
            break;
        }

        case 0:
            cout << "Quay lai menu chinh...\n";
            break;

        default:
            cout << "[Loi] Lua chon khong hop le, vui long chon lai (0-6).\n";
            break;
        }

    } while (choice != 0);
}
