#include "boss.h"
#include <iostream>

Boss::Boss(int id, string name, int deptId) {
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = deptId;
}

void Boss::ShowInfo() {
  cout << "Worker ID: " << this->m_Id << "\tWorker Name: " << this->m_Name
       << "\tWorker Department: " << this->GetDeptName()
       << "\tWorker Position: Boss" << endl;
}

string Boss::GetDeptName() { return "Boss"; }
