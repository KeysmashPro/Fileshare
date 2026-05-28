#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef unsigned long long u64;
typedef unsigned int u32;

int isit(int b) {
  while (b > 0) {
    if (b % 8 == 3)
      return(1);
  b /= 8;
  }
  return(0);
}

int main() {
  ifstream file("numbers.txt");
  vector<int> numbers;
  int num;

  while (file >> num)
      numbers.push_back(num);
  file.close();
  
  int s = 0;
  int m = 999999999;
  vector<int> stupid;

  int mne = 0;
  for(int i = 0; i < numbers.size(); ++i) {
    int a = numbers[i];
    if (a % 133 == 0){
      if (a > mne) mne = a;
    }
  }

  for(int i = 0; i < numbers.size() - 1; ++i) {
    int a = numbers[i+0];
    int b = numbers[i+1];
    if ((a > mne or b > mne) && (isit(a) or isit(b))) {
      s++;
      if(a + b < m) m = a + b;
    }
  }
  
  cout << s << " " << m << endl;

  return 0;
}
