#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define Height 10
#define Width 10

#define array_size 1000

void Display_map(int map[Height][Width]);
void Create_map(int map[Height][Width]);
void A_star_path_finding(int map[Height][Width], int cost_map[Height][Width],
                         int start_point[2], int end_point[2]);
int Get_heuristic_function(int current_point[2], int Goal[2]);
bool check_end_point_in_openset(int end_point[2], int OpenSet[array_size][3]);
int Get_minimun_fn_coord(int Openset[array_size][3]);
int Get_gn(int current_point[2], int start_point[2]);

// create a map using 2-D array
void Create_map(int map[Height][Width])
{
  for (int i = 0; i < Height; i++)
  {
    for (int j = 0; j < Width; j++)
    {
      if ((i == 2 && j >= 2 && j <= 7) || ((i == 7 && j >= 2 && j <= 7)) ||
          (i >= 3 && i <= 6 && j == 7))
      {
        map[i][j] = 100;
      }
      else
      {
        map[i][j] = 0;
      }
    }
  }
}

// path finding function,can be alternate to other algorithm like Dijstra
void A_star_path_finding(int map[Height][Width], int cost_map[Height][Width],
                         int start_point[2], int end_point[2])
{
  int ClosedSet[array_size][3];
  int OpenSet[array_size][3];
  int current_point[2];
  int min_index = 0;
  int hn = 0, gn = 0;

  OpenSet[0][0] = start_point[0];
  OpenSet[0][1] = start_point[1];
  min_index = Get_minimun_fn_coord(OpenSet);

  current_point[0] = OpenSet[min_index][0];
  current_point[1] = OpenSet[min_index][1];

  hn = Get_heuristic_function(current_point, end_point);
  gn = Get_gn(current_point, start_point);
  cout << hn << "\t" << gn << endl;
}

// get Manhaton distance
int Get_heuristic_function(int current_point[2], int Goal[2])
{
  return (abs(Goal[1] - current_point[1]) + abs(Goal[0] - current_point[0]));
}

int Get_gn(int current_point[2], int start_point[2])
{
  return (abs(start_point[1] - current_point[1]) + abs(start_point[0] - current_point[0]));
}

bool check_end_point_in_openset(int end_point[2], int OpenSet[array_size][3])
{
  for (int i = 0; i < array_size; i++)
  {
    if (OpenSet[i][0] == end_point[0] && OpenSet[i][1] == end_point[1])
      return true;
  }
  return false;
}

int Get_minimun_fn_coord(int Openset[array_size][3])
{
  int result_index = 0;
  int minimun = Openset[0][2];
  for (int i = 0; i < array_size; i++)
  {
    if (Openset[i][2] < minimun)
    {
      result_index = i;
      minimun = Openset[i][2];
    }
  }
  return result_index;
}

// display the map with grid
void Display_map(int map[Height][Width])
{
  for (int i = 0; i < Height; i++)
  {
    for (int j = 0; j < Width; j++)
    {
      printf("%5d", map[i][j]);
    }
    cout << endl;
  }
}

int main(int argc, char **argv)
{
  int map[Height][Width], cost_map[Height][Width];
  Create_map(map);
  Create_map(cost_map);
  cout << "original map" << endl;
  Display_map(map);

  int start_point[2] = {5, 0};
  int end_point[2] = {9, 5};
  A_star_path_finding(map, cost_map, start_point, end_point);

  return 0;
}
