#include "dijkstra.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#define LIM 10000

int
main()
{
  struct timespec b_time, e_time;

  // example of the slides

  Graph gp{};
  gp.addEdge(0, 1, 1);
  gp.addEdge(0, 2, 5);
  gp.addEdge(1, 5, 15);
  gp.addEdge(2, 3, 2);
  gp.addEdge(3, 4, 1);
  gp.addEdge(4, 5, 3);
  clock_gettime(CLOCK_REALTIME, &b_time);
  dijkstra_array(gp, 0);
  clock_gettime(CLOCK_REALTIME, &e_time);
  std::cout << std::endl
            << "Array\t" << get_execution_time(b_time, e_time) << std::endl
            << std::endl;

  for (int i = 1; i < gp.size(); i++)
    printPath(gp, i, 0);

  Graph gp2{};
  gp2.addEdge(0, 1, 1);
  gp2.addEdge(0, 2, 5);
  gp2.addEdge(1, 5, 15);
  gp2.addEdge(2, 3, 2);
  gp2.addEdge(3, 4, 1);
  gp2.addEdge(4, 5, 3);

  clock_gettime(CLOCK_REALTIME, &b_time);
  dijkstra(gp2, 0);
  clock_gettime(CLOCK_REALTIME, &e_time);
  std::cout << std::endl
            << "Heap\t" << get_execution_time(b_time, e_time) << std::endl
            << std::endl;

  for (int i = 1; i < gp2.size(); i++)
    printPath(gp2, i, 0);

  // example of the book

  Graph gp3{};

  gp3.addEdge(0, 1, 5);
  gp3.addEdge(0, 2, 10);
  gp3.addEdge(1, 3, 2);
  gp3.addEdge(3, 4, 6);
  gp3.addEdge(2, 4, 1);
  gp3.addEdge(1, 2, 3);
  gp3.addEdge(2, 1, 2);
  gp3.addEdge(1, 4, 9);
  gp3.addEdge(3, 0, 7);
  gp3.addEdge(4, 3, 4);

  clock_gettime(CLOCK_REALTIME, &b_time);
  dijkstra_array(gp3, 0);
  clock_gettime(CLOCK_REALTIME, &e_time);
  std::cout << std::endl
            << "Array\t" << get_execution_time(b_time, e_time) << std::endl
            << std::endl;

  for (int i = 1; i < gp3.size(); i++)
    printPath(gp3, i, 0);

  Graph gp4{};
  gp4.addEdge(0, 1, 5);
  gp4.addEdge(0, 2, 10);
  gp4.addEdge(1, 3, 2);
  gp4.addEdge(3, 4, 6);
  gp4.addEdge(2, 4, 1);
  gp4.addEdge(1, 2, 3);
  gp4.addEdge(2, 1, 2);
  gp4.addEdge(1, 4, 9);
  gp4.addEdge(3, 0, 7);
  gp4.addEdge(4, 3, 4);

  clock_gettime(CLOCK_REALTIME, &b_time);
  dijkstra(gp4, 0);
  clock_gettime(CLOCK_REALTIME, &e_time);
  std::cout << std::endl
            << "Heap\t" << get_execution_time(b_time, e_time) << std::endl
            << std::endl;

  for (int i = 1; i < gp4.size(); i++)
    printPath(gp4, i, 0);

  // the graph is not random at all, and in fact favours a lot the heap
  // implementation cause the Edge number is << than V^2
  std::cout << "For a (not so) randomly generated graph" << std::endl;
  // test the time on a quite sparse graph
  for (int j = 10; j < LIM; j = j * 10) {
    Graph gp5{};
    for (int i = 0; i < j; i++)
      for (int k = 0; k < j; k++) {
        if (abs(i - k) < 3)
          gp5.addEdge(i, k, i * 2 + k * 3 + 4);
        gp5.addEdge(k, i, i + k * 2 + 4);
      }
    Graph gp6{};
    for (int i = 0; i < j; i++)
      for (int k = 0; k < j; k++) {
        if (abs(i - k) < 3)
          gp6.addEdge(i, k, i * 2 + k * 3 + 4);
        gp5.addEdge(k, i, i + k * 2 + 4);
      }

    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_array(gp5, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << std::endl
              << "Array "
              << "dim=" << j << "\t" << get_execution_time(b_time, e_time)
              << std::endl
              << std::endl;

    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra(gp6, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << std::endl
              << "Heap "
              << "dim=" << j << "\t" << get_execution_time(b_time, e_time)
              << std::endl
              << std::endl;
  }
}
