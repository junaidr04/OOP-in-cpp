#include <bits/stdc++.h>
using namespace std;
class Student
{
public:
    int ID;
    string name, dept;
    void study()
    {
        cout << "Studying" << endl;
    }
};
int main()
{
    Student j;
    j.ID = 21;
    j.name = "JUNAID";
    j.dept = "CSE";
    j.study();
    cout << "ID is = " << j.ID << endl;
    cout << "Name is = " << j.name << endl;
    cout << "Dept is = " << j.dept << endl;
    return 0;
}
