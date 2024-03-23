#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

WorkerManager::WorkerManager() {
  cout << "WorkerManager constructor" << endl;
  ifstream ifs;
  ifs.open("worker.txt", ios::in);
  if (!ifs.is_open()) {
    cout << "File does not exist" << endl;
    this->m_FileIsEmpty = true;
    this->m_EmpNum = 0;
    this->m_Workers = NULL;
    ifs.close();
    return;
  }
  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    cout << "File is empty" << endl;
    this->m_FileIsEmpty = true;
    this->m_EmpNum = 0;
    this->m_Workers = NULL;
    ifs.close();
    return;
  }
  int num = this->getWorkerNum();
  cout << "Number of workers: " << num << endl;
  this->m_EmpNum = num;
  this->m_Workers = new Worker *[this->m_EmpNum];
  this->InitWorkers();
  this->m_FileIsEmpty = false;
}

int WorkerManager::getWorkerNum() {
  ifstream ifs;
  ifs.open("worker.txt", ios::in);
  int id;
  string name;
  int deptId;
  int num = 0;
  while (ifs >> id && ifs >> name && ifs >> deptId) {
    num++;
  }
  ifs.close();
  return num;
}

void WorkerManager::InitWorkers() {
  cout << "Initializing Workers" << endl;
  ifstream ifs;
  ifs.open("worker.txt", ios::in);
  int id;
  string name;
  int deptId;
  int index = 0;
  while (ifs >> id && ifs >> name && ifs >> deptId) {
    Worker *worker = NULL;
    if (deptId == 1) {
      worker = new Employee(id, name, deptId);
    } else if (deptId == 2) {
      worker = new Manager(id, name, deptId);
    } else if (deptId == 3) {
      worker = new Boss(id, name, deptId);
    }
    this->m_Workers[index] = worker;
    index++;
  }
  ifs.close();
}

WorkerManager::~WorkerManager() {
  cout << "WorkerManager destructor" << endl;
  if (this->m_Workers != NULL) {
    for (int i = 0; i < this->m_EmpNum; i++) {
      delete this->m_Workers[i];
    }
    delete[] this->m_Workers;
    this->m_Workers = NULL;
  }
}

void WorkerManager::ShowMenu() {
  cout << "WorkerManager Menu" << endl;
  cout << "1. Add Worker" << endl;
  cout << "2. Show Worker" << endl;
  cout << "3. Delete Worker" << endl;
  cout << "4. Modify Worker" << endl;
  cout << "5. Find Worker" << endl;
  cout << "6. Sort Worker" << endl;
  cout << "7. Clear Worker" << endl;
  cout << "0. Exit" << endl;
  cout << "Select: ";
}

void WorkerManager::ExitSystem() {
  cout << "Exiting WorkerManager" << endl;
  system("pause");
  exit(0);
}

void WorkerManager::AddWorker() {
  cout << "Adding Worker" << endl;
  cout << "Enter number of workers to add: ";
  int addNum = 0;
  cin >> addNum;
  if (addNum > 0) {
    int newSize = this->m_EmpNum + addNum;
    Worker **newSpace = new Worker *[newSize];
    if (this->m_Workers != NULL) {
      for (int i = 0; i < this->m_EmpNum; i++) {
        newSpace[i] = this->m_Workers[i];
      }
    }
    for (int i = 0; i < addNum; i++) {
      int id;
      string name;
      int deptId;
      cout << "Enter worker " << i + 1 << " id: ";
      cin >> id;
      cout << "Enter worker " << i + 1 << " name: ";
      cin >> name;
      cout << "Enter worker " << i + 1 << " deptId: ";
      cout << "Selecting worker type..." << endl;
      cout << "1. Employee" << endl;
      cout << "2. Manager" << endl;
      cout << "3. Boss" << endl;
      cin >> deptId;
      Worker *worker = NULL;
      if (deptId == 1) {
        worker = new Employee(id, name, deptId);
      } else if (deptId == 2) {
        worker = new Manager(id, name, deptId);
      } else if (deptId == 3) {
        worker = new Boss(id, name, deptId);
      } else {
        cout << "Invalid deptId" << endl;
      }
      newSpace[this->m_EmpNum + i] = worker;
    }
    delete[] this->m_Workers;
    this->m_Workers = newSpace;
    this->m_EmpNum = newSize;
    this->m_FileIsEmpty = false;
    cout << "Added " << addNum << " workers" << endl;
    this->SaveWorkers();
  } else {
    cout << "Invalid number of workers" << endl;
  }
  system("pause");
  system("cls");
}

void WorkerManager::SaveWorkers() {
  cout << "Saving Workers" << endl;
  ofstream ofs;
  ofs.open("worker.txt", ios::out);
  for (int i = 0; i < this->m_EmpNum; i++) {
    ofs << this->m_Workers[i]->m_Id << " " << this->m_Workers[i]->m_Name << " "
        << this->m_Workers[i]->m_DeptId << endl;
  }
  ofs.close();
}

void WorkerManager::ShowWorkers() {
  cout << "Showing Workers" << endl;
  if (this->m_FileIsEmpty) {
    cout << "File is empty" << endl;
  } else {
    for (int i = 0; i < this->m_EmpNum; i++) {
      this->m_Workers[i]->ShowInfo();
    }
  }
  system("pause");
  system("cls");
}

int WorkerManager::IsExist(int id) {
  int index = -1;
  for (int i = 0; i < this->m_EmpNum; i++) {
    if (this->m_Workers[i]->m_Id == id) {
      index = i;
      break;
    }
  }
  return index;
}

void WorkerManager::DeleteWorker() {
  cout << "Deleting Worker" << endl;
  if (this->m_FileIsEmpty) {
    cout << "File is empty" << endl;
  } else {
    int id;
    cout << "Enter worker id to delete: ";
    cin >> id;
    int index = this->IsExist(id);
    if (index != -1) {
      for (int i = index; i < this->m_EmpNum - 1; i++) {
        this->m_Workers[i] = this->m_Workers[i + 1];
      }
      this->m_EmpNum--;
      this->SaveWorkers();
      cout << "Deleted worker with id " << id << endl;
    } else {
      cout << "Worker with id " << id << " does not exist" << endl;
    }
  }
  system("pause");
  system("cls");
}

void WorkerManager::ModifyWorker() {
  cout << "Modifying Worker" << endl;
  if (this->m_FileIsEmpty) {
    cout << "File is empty" << endl;
  } else {
    int id;
    cout << "Enter worker id to modify: ";
    cin >> id;
    int index = this->IsExist(id);
    if (index != -1) {
      delete this->m_Workers[index];
      int newId;
      string newName;
      int newDeptId;
      cout << "Enter new id: ";
      cin >> newId;
      cout << "Enter new name: ";
      cin >> newName;
      cout << "Enter new deptId: ";
      cin >> newDeptId;
      Worker *worker = NULL;
      if (newDeptId == 1) {
        worker = new Employee(newId, newName, newDeptId);
      } else if (newDeptId == 2) {
        worker = new Manager(newId, newName, newDeptId);
      } else if (newDeptId == 3) {
        worker = new Boss(newId, newName, newDeptId);
      } else {
        cout << "Invalid deptId" << endl;
      }
      this->m_Workers[index] = worker;
      cout << "Modified worker with id " << id << endl;
      this->SaveWorkers();
    } else {
      cout << "Worker with id " << id << " does not exist" << endl;
    }
  }
  system("pause");
  system("cls");
}

void WorkerManager::FindWorker() {
  cout << "Finding Worker" << endl;
  if (this->m_FileIsEmpty) {
    cout << "File is empty" << endl;
  } else {
    cout << "Enter search criteria: " << endl;
    cout << "1. By id" << endl;
    cout << "2. By name" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
      int id;
      cout << "Enter worker id to find: ";
      cin >> id;
      int index = this->IsExist(id);
      if (index != -1) {
        this->m_Workers[index]->ShowInfo();
      } else {
        cout << "Worker with id " << id << " does not exist" << endl;
      }
    } else if (choice == 2) {
      string name;
      cout << "Enter worker name to find: ";
      cin >> name;
      bool flag = false;
      for (int i = 0; i < this->m_EmpNum; i++) {
        if (this->m_Workers[i]->m_Name == name) {
          this->m_Workers[i]->ShowInfo();
          flag = true;
        }
      }
      if (!flag) {
        cout << "Worker with name " << name << " does not exist" << endl;
      }
    } else {
      cout << "Invalid choice" << endl;
    }
  }
  system("pause");
  system("cls");
}

void WorkerManager::SortWorkers() {
  cout << "Sorting Workers" << endl;
  if (this->m_FileIsEmpty) {
    cout << "File is empty" << endl;
  } else {
    cout << "Enter sort criteria: " << endl;
    cout << "1. By id" << endl;
    cout << "2. By name" << endl;
    cout << "3. By deptId" << endl;
    int choice;
    cin >> choice;
    for (int i = 0; i < this->m_EmpNum; i++) {
      int minOrMax = i;
      for (int j = i + 1; j < this->m_EmpNum; j++) {
        if (choice == 1) {
          if (this->m_Workers[minOrMax]->m_Id > this->m_Workers[j]->m_Id) {
            minOrMax = j;
          }
        } else if (choice == 2) {
          if (this->m_Workers[minOrMax]->m_Name > this->m_Workers[j]->m_Name) {
            minOrMax = j;
          }
        } else if (choice == 3) {
          if (this->m_Workers[minOrMax]->m_DeptId >
              this->m_Workers[j]->m_DeptId) {
            minOrMax = j;
          }
        }
      }
      if (minOrMax != i) {
        Worker *temp = this->m_Workers[i];
        this->m_Workers[i] = this->m_Workers[minOrMax];
        this->m_Workers[minOrMax] = temp;
      }
    }
    cout << "Sorted workers" << endl;
    this->SaveWorkers();
  }
  system("pause");
  system("cls");
}

void WorkerManager::CleanWorkers() {
  cout << "Cleaning Workers" << endl;
  cout << "Are you sure you want to clear all workers?" << endl;
  cout << "1. Yes" << endl;
  cout << "2. No" << endl;
  int choice;
  cin >> choice;
  if (choice == 1) {
    ofstream ofs;
    ofs.open("worker.txt", ios::trunc);
    ofs.close();
    if (this->m_Workers != NULL) {
      for (int i = 0; i < this->m_EmpNum; i++) {
        delete this->m_Workers[i];
      }
      delete[] this->m_Workers;
      this->m_Workers = NULL;
      this->m_EmpNum = 0;
      this->m_FileIsEmpty = true;
    }
    cout << "Cleared workers" << endl;
  } else {
    cout << "Did not clear workers" << endl;
  }
  system("pause");
  system("cls");
}
