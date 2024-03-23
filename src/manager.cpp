#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(int id, string name, int deptId) {
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = deptId;
}

void Manager::ShowInfo() {
  cout << "Worker ID: " << this->m_Id << "\tWorker Name: " << this->m_Name
       << "\tWorker Department: " << this->GetDeptName()
       << "\tWorker Position: Manager" << endl;
}

string Manager::GetDeptName() { return "Manager"; }