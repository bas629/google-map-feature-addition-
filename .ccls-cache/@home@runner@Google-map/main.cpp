#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

class Graph {
public:
  map<string, list<pair<string, int>>> adjList;
  void addEdge(string scr, string dst, int wt) {
    adjList[scr].push_back({dst, wt});
    adjList[dst].push_back({scr, wt});
  }

  void print() {
    for (auto i : adjList) {
      cout << i.first << "->";
      for (auto j : i.second) {
        cout << "{" << j.first << "," << j.second << "}"
             << " ";
      }
      cout << endl;
    }
  }
  void allPossiblePath(string scr, string dst, vector<string> temp,
                       vector<vector<string>> &ans, vector<int> &v, int wt,
                       map<string, bool> &m) {
    m[scr] = true;

    for (auto i : adjList[scr]) {
      if (scr == dst) {
        if (temp.size() == 0 ||
            (temp.size() != 0 && temp[temp.size() - 1] != scr)) {
          temp.push_back(scr);
        }
        temp.push_back(to_string(wt));
        ans.push_back(temp);
        wt = 0;
        temp.clear();
        return;
      } else if (i.first == dst) {
        if (temp.size() == 0 ||
            (temp.size() != 0 && temp[temp.size() - 1] != scr)) {
          temp.push_back(scr);
        }

        allPossiblePath(i.first, dst, temp, ans, v, wt + i.second, m);
        m[i.first] = false;

      } else if (!m[i.first]) {
        if (temp.size() == 0 ||
            (temp.size() != 0 && temp[temp.size() - 1] != scr)) {
          temp.push_back(scr);
        }
        allPossiblePath(i.first, dst, temp, ans, v, wt + i.second, m);
        m[i.first] = false;
      }
    }

    m[scr] = false;
  }
};

void loadData(Graph &g) {
  ofstream ofs1("socure.text", ios::app);
  ofstream ofs2("destination.text", ios::app);
  ofstream ofs3("distance.text", ios::app);

  ifstream ifs1, ifs2, ifs3, ifs4, ifs5;
  ifs1.open("room.text");
  ifs2.open("socure.text");
  ifs3.open("destination.text");
  ifs4.open("distance.text");
  ifs5.open("distance.text");

  string line;
  int lineCount = 0;
  while (getline(ifs5, line)) {
    lineCount++;
  }
  string scr, dest;
  int dist;
  for (int i = 0; i < lineCount; i++) {
    ifs2 >> scr;
    ifs3 >> dest;
    ifs4 >> dist;
    g.addEdge(scr, dest, dist);
  }
}

vector<vector<string>> AllPossibleMaps(Graph &g, string scr, string dst) {
  vector<string> temp;
  vector<int> v;
  int wt = 0;
  vector<vector<string>> ans;
  map<string, bool> m;
  g.allPossiblePath(scr, dst, temp, ans, v, wt, m);

  return ans;
}

void printpath(vector<vector<string>> &path) {
  for (auto i : path) {
    for (auto j : i) {
      cout << j << "->";
    }

    cout << endl;
  }
}
void printpath(vector<vector<string>> &path, string mid1, string mid2) {
  for (auto i : path) {
    for (auto j : i) {
      cout << j << "->";
    }

    cout << endl;
  }
}

std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(
      " \t\n\r"); // Find the first non-whitespace character
  size_t last =
      str.find_last_not_of(" \t\n\r"); // Find the last non-whitespace character

  if (first == std::string::npos) // If the string is all whitespace
    return "";

  return str.substr(first,
                    (last - first + 1)); // Extract the non-whitespace portion
}

void desirepath(vector<string> &desireplace, vector<vector<string>> path,
                vector<string> &allPossibleplace) {
  for (auto i : path) {
    int k = 0;
    for (auto j : i) {
      for (int l = 0; l < desireplace.size(); l++) {
        if (j == desireplace[l]) {
          k++;
        }
      }
    }

    if (k == desireplace.size()) {
      for (auto z : i) {
        allPossibleplace.push_back(z);
      }

      allPossibleplace.push_back("endl");
    }

    if (k != 0) {
      for (auto z : i) {
        cout << z << "--->";
      }
    }
    cout << endl;
  }
}

void midDestnation(vector<vector<string>> path) {
  ofstream ofs4("midScoure", ios::app);
  ofstream ofs5("midDestination", ios::app);
  ofstream ofs6("midDistance", ios::app);
  ofstream ofs7("shop", ios::app);

  map<pair<string, string>, list<pair<int, string>>> midDestination;

  ifstream ifs4, ifs5, ifs6, ifs7;
  ifs4.open("midScoure");
  ifs5.open("midDestination");
  ifs6.open("midDistance");
  ifs7.open("shop");
  string scr, dest, shop;
  int dist;
  for (int i = 0; i < 4; i++) {
    ifs4 >> scr;
    ifs5 >> dest;
    ifs6 >> dist;
    ifs7 >> shop;
    midDestination[{scr, dest}].push_back({dist, shop});
    midDestination[{dest, scr}].push_back({dist, shop});
  }

  string temp;
  for (int l = 0; l < path.size(); l++) {
    for (int i = 0, j = 1; j < path[l].size(); i++, j++) {
      temp = path[l][i];
      transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
      cout << temp << "--->";

      for (auto k : midDestination[{path[l][i], path[l][j]}]) {
        // if(k.second=="Petrol-Pump")
        {
          cout << "{" << k.first << "," << k.second << "}"
               << "---->";
        }
      }
      temp = path[l][j];
      transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
      cout << temp << "--->";
      cout << endl;
    }
    cout << endl;
    cout << endl;
  }
}

void sortestPath(vector<vector<string>> &path) {
  int n;
  int ans = INT_MAX;
  int index;
  for (int i = 0; i < path.size(); i++) {
    n = stoi(path[i][path[i].size() - 1]);
    if (ans > n) {
      ans = n;
      index = i;
    }
  }

  for (int i = 0; i < path[index].size(); i++) {
    cout << path[index][i] << "--->";
  }
}

int main() {

  Graph g;
  loadData(g);
  g.print();
  cout << endl;

  vector<vector<string>> path;
  string sr;
  string dt;
  cout << "Enter the Scoure" << endl;
  cin >> sr;

  cout << "Enter the Destination" << endl;
  cin >> dt;
  cout << endl;
  sr = trim(sr);

  dt = trim(dt);
  transform(sr.begin(), sr.end(), sr.begin(), ::tolower);
  transform(dt.begin(), dt.end(), dt.begin(), ::tolower);
  path = AllPossibleMaps(g, sr, dt);
  vector<string> desirePlace;
  string place;
  bool flag = true;
  while (flag) {
    cout << "Enter mid place otherwise -1" << endl;
    cin >> place;

    if (place == "-1") {
      flag = false;
    }

    else {
      transform(place.begin(), place.end(), place.begin(), ::tolower);

      place = trim(place);
      desirePlace.push_back(place);
    }
  }
  cout << endl;

  cout << "-----x-----------------------x------x-------------------------------"
          "-------------x-----"
       << endl;
  cout << "Your Desire Paths" << endl;

  vector<string> allPossibleplace;
  desirepath(desirePlace, path, allPossibleplace);
  cout << endl;
  cout << "-----x-----------------------x------x-------------------------------"
          "-x"
       << endl;
  cout << "Your all possible Desire Paths" << endl;
  printpath(path);
  cout << endl;
  cout << "-----x-----------------------x------x-----------x-------------------"
          "--------"
       << endl;
  cout << "Best path" << endl;
  cout << endl;
  for (auto i : allPossibleplace) {
    if (i == "endl") {
      cout << endl;
    } else {
      cout << i << "---->";
    }
  }
  cout << endl;
  cout << "-----x-----------------------x------x-----------x-------------------"
          "--------"
       << endl;
  cout << "Sortest path" << endl;
  cout << endl;
  sortestPath(path);
}