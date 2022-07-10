// BT2_Kiem tra tinh lien thong cua do thi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*Kiểm tra xem đồ thị đã cho có liên thông (mạnh/yếu) hay không;
Trường hợp đồ thị vô hướng không liên thông, liệt kê tất cả các thành phần liên thông của đồ thị.*/


#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stack>
using namespace std;

int n;
bool visited[1001]; // mảng dùng để lưu những đỉnh nào đã dùng

bool kiemtraFiletontai(ifstream& fi) {
    bool cotontai = true;
    bool khongtontai = fi.fail();
    if (khongtontai == true) {
        cotontai = false;
    }
    return cotontai;
}

void docfile(ifstream& fi, int** a, int n)
{
    int x, i;
    while (!fi.eof())
    {
        fi >> i;
        while (true)
        {
            fi >> x;
            if (x > 0)
                a[i][x] = 1;
            if (fi.eof())
                break;
            char c;
            fi.get(c);
            char ch[2] = { c };
            if (strcmp(ch, " ") != 0)
            {
                break;
            }
        }
    }
}

void xuatmatranke(int** a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
        visited[i] = false;
    }
}

bool kiemtradothi(int** a, int n)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != a[j][i]) {
                return true; // Do thi co huong
            }
        }
    }
    return false; // Do thi vo huong
}

// Viet ham menu chon xem dung cach DFS hay BFS
// Chon ham DFS, neu do thi vo huong thi ... neu do thi co huong thi ... (1)
// Chon ham BFS, neu do thi vo huong thi ... neu do thi co huong thi ... (2)
// (1) Neu do thi vo huong, kiem tra xem do thi co lien thong hay khong
// (1) Neu  do thi co huong, kiem tra xem do thi lien thong manh/yeu
// (2) tuong tu

int BFS(int** a, int u) {
    int counter = 0;
    queue<int> Q;
    Q.push(u); // push đỉnh u vào Q;
    visited[u] = true; // đã thăm đỉnh u vào queue;
    while (!Q.empty()) { // nếu queue chưa rỗng
        int s = Q.front(); // lấy đỉnh s là đầu của queue ra;
        counter++; // mỗi khi duyệt qua một đỉnh thì tăng counter lên 1 đơn vị
        Q.pop();
        for (int t = 1; t <= n; t++) {
            if (visited[t] == false && a[s][t] == 1) {
                Q.push(t); // nếu t chưa được thăm và a[s][t] = 1
                visited[t] = true; // thăm t
            }
        }
    }
    return counter;
}

int DFS(int**a, int u)
{
    int counter = 0;
    cout << "DFS(" << u << "): ";
    stack<int> st;
    st.push(u);
    visited[u] = true;
    cout << u << " ";
    while (!st.empty())
    {
        int v = st.top();
        counter++;
        st.pop();
        for (int t = 1; t <= n; t++)
        {
            if (visited[t] == false && a[v][t] == 1)
            {
                cout << t << " ";
                visited[t] = true;
                st.push(v);
                st.push(t);
                break;
            }
        }
    }
    return counter;
}

void reinit() {
    for (int v = 1; v <= n; v++) {
        visited[v] = false;
    }
}

bool kiemtratinhlienthong_BFS(int**a, int n) {
    for (int v = 1; v <= n; v++) {
        if (BFS(a, v) != n) {
            return false;
            break; // tối ưu chương trình
        }
        reinit();
    }
    return true;
}

bool kiemtratinhlienthong_DFS(int** a, int n) {
    for (int v = 1; v <= n; v++) {
        if (BFS(a, v) != n) {
            return false;
            break; // tối ưu chương trình
        }
        reinit();
    }
    return true;
}

// Thuat toan BFS cho do thi vo/co huong
void menu1(int** a, int n) {
    if (kiemtradothi(a, n) == false) // Do thi vo huong
    {
        if (kiemtratinhlienthong_BFS(a, n) == true) {
            cout << "Do thi vo huong lien thong";
            reinit();
        }
        else {
            cout << "Do thi vo huong khong lien thong";
            // Liet ke cac thanh phan lien thong cua do thi
            for (int v = 1; v <= n; v++) {
                cout << BFS(a, v) << endl;
                reinit();
            }
        }
    }
    else // Do thi co huong
    {
        if (kiemtratinhlienthong_BFS(a, n) == true) {
            cout << "Do thi co huong lien thong manh";
            reinit();
        }
        else {
            cout << "Do thi co huong lien thong yeu";
            reinit();
        }
    }
}

// Thuat toan DFS cho do thi vo/co huong
void menu2(int** a, int n) {
    if (kiemtradothi(a, n) == false) // Do thi vo huong
    {
        if (kiemtratinhlienthong_DFS(a, n) == true) {
            cout << "Do thi vo huong lien thong";
        }
        else {
            cout << "Do thi vo huong khong lien thong";
            // Liet ke cac thanh phan lien thong cua do thi
            for (int v = 1; v <= n; v++) {
                cout << DFS(a, v) << endl;
                reinit();
            }
        }
    }
    else // Do thi co huong
    {
        if (kiemtratinhlienthong_DFS(a, n) == true) {
            cout << "Do thi co huong lien thong manh";
        }
        else {
            cout << "Do thi co huong lien thong yeu";
        }
    }
}

void Menu() {
    cout << "==============CHON PHUONG THUC DUYET DO THI=============\n";
    cout << "1. Duyet do thi bang BFS\n";
    cout << "2. Duyet do thi bang DFS\n";
    cout << "3. Thoat!!!\n";
    cout << "=====================================";
}

int ChonMenu()
{
    int n = 0;
    cout << "\n\nMoi chon menu: ";
    cin >> n;
    if (n > 0 || n <= 3)
        return n;
    else return ChonMenu();
}

void XuLyMenu(int** a)
{
    int chon = ChonMenu();
    switch (chon)
    {
    case 1:
        cout << "1. Duyet do thi bang BFS\n";
        menu1(a, n);
        break;
    case 2:
        cout << "2. Duyet do thi bang DFS\n";
        menu2(a, n);
        break;
    case 3:
        cout << "Thoat!!!\n";
        exit(1);
        break;
    }
}

int main()
{
    cout << "TH02: Bieu dien do thi --- 2051120333/Tcheng Nhu Quan\n";
    ifstream fi("TH02_input.txt");
    kiemtraFiletontai(fi);
    if (kiemtraFiletontai(fi) == true) {
        cout << "File ton tai\n";
    }
    else {
        cout << "Loi. File khong ton tai!\n";
    }

    int n = 0;
    fi >> n;
    string s;
    getline(fi, s);

    int** a = new int* [n + 1];
    for (int i = 1; i <= n; i++)
        a[i] = new int[n + 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = 0;

    docfile(fi, a, n);
    cout << "Xuat ma tran ke cua do thi la: " << endl;
    xuatmatranke(a, n);

    
    fi.close();
    if (kiemtradothi(a, n) == false) {
        cout << "Ket luan: Do thi vo huong\n";
    }
    else {
        cout << "Ket luan: Do thi co huong\n";
    }
 
    //init();
    /*for (int v = 1; v <= n; v++) {
        cout << bfs(v) << endl;
        reinit();
    }*/
    Menu();
    while (true)
    {
        XuLyMenu(a);
    }

    for (int i = 1; i <= n; i++)
        delete[] a[i];
    delete[] a;
    return 0;

}




