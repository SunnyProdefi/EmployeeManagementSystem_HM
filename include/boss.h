#ifndef BOSS_H
#define BOSS_H

#include "worker.h"

class Boss : public Worker {
public:
  Boss(int id, string name, int deptId);
  virtual void ShowInfo();
  virtual string GetDeptName();
};

#endif // BOSS_H
