#pragma once
#include "worker.h"
class WorkerManager {
public:
  WorkerManager();
  void ShowMenu();
  void ExitSystem();
  int m_EmpNum;
  Worker **m_Workers;
  void AddWorker();
  void SaveWorkers();
  bool m_FileIsEmpty;
  int getWorkerNum();
  void InitWorkers();
  void ShowWorkers();
  int IsExist(int id);
  void DeleteWorker();
  void ModifyWorker();
  void FindWorker();
  void SortWorkers();
  void CleanWorkers();
  ~WorkerManager();
};