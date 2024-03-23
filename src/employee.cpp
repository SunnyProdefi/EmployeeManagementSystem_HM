#include "employee.h"
#include <iostream>
Employee::Employee(int id, string name, int deptId) {
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = deptId;
}

void Employee::ShowInfo() {
  cout << "Worker ID: " << this->m_Id << "\tWorker Name: " << this->m_Name
       << "\tWorker Department: " << this->GetDeptName()
       << "\tWorker Position: Employee" << endl;
}

string Employee::GetDeptName() { return "Employee"; }
