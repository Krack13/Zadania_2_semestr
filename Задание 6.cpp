#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Regions {
    int line = 0, barrier = 0, plots = 0;
    vector <string> arr;
public:

    Regions() {
        ifstream in_data("INPUT.txt", ios::in);
        if (!in_data.is_open())cout << "Ошибка при открытии файла!\n";
        else {
            string tmp = "def";
            in_data >> line >> barrier;
            for (int i = 0; i < line; i++) {in_data >> tmp;arr.emplace_back(tmp);}
        }
    }

    void field() {
        cout << line << " " << barrier << endl;
        for (int i = 0; i < line; i++) {cout << arr[i];cout << endl;}
    }

    void print() {cout << plots << endl;}

    void open_file(int& out_result) {
        ofstream out; 
        out.open("OUTPUT.txt"); 
        if (out.is_open()){out << out_result <<endl;}
        out.close();
        cout << "Файл записан" <<endl;
    }

    void delet(int i, int j) {
        while (true) {
            if (arr[i][j] == *"#") { arr[i][j] = *".";}
            if (i != line - 1 and arr[i + 1][j] == *"#") { arr[i][j] = *".";i += 1;continue;}
            if (j != barrier - 1 and arr[i][j + 1] == *"#") { arr[i][j] = *".";j += 1;continue;}
            if (j != 0 and arr[i][j - 1] == *"#") { arr[i][j] = *".";j -= 1;continue;}
            if (i != 0 and arr[i - 1][j] == *"#") { arr[i][j] = *".";i -= 1;continue;}
            break;
        }
    }

    void search() {
        for (int line_num = 0; line_num < line; line_num++) {
            for (int stolb_num = 0; stolb_num < barrier; stolb_num++) {
                if (arr[line_num][stolb_num] == *"#") {
                    plots++;
                    delet(line_num, stolb_num);
                }
            }
        }
        open_file(plots);
    }
};



int main() {
    Regions region;
    region.field();
    region.search();
    region.print();
}