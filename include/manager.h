#pragma once
#include "worker.h"
#include <string>

using namespace std;

class Manager : public Worker {
public:
  Manager(int id, string name, int deptId);
  virtual void ShowInfo();
  virtual string GetDeptName();
};