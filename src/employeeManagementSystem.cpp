#include "workerManager.h"
#include <iostream>

using namespace std;
int main() {
  WorkerManager wm;
  int choice = 0;
  while (true) {
    wm.ShowMenu();
    cout << "Please enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 0: // Exit
      wm.ExitSystem();
      break;
    case 1: // Add
      wm.AddWorker();
      break;
    case 2: // Show
      wm.ShowWorkers();
      break;
    case 3: // Delete
      wm.DeleteWorker();
      break;
    case 4: // Modify
      wm.ModifyWorker();
      break;
    case 5: // Find
      wm.FindWorker();
      break;
    case 6: // Sort
      wm.SortWorkers();
      break;
    case 7: // Clear
      wm.CleanWorkers();
      break;
    default:
      system("cls");
      break;
    }
  }
  system("pause");
  return 0;
}
