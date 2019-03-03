#include <fstream>
using namespace std;

struct Client {
    int time;
    int code;
    int year;
    int month;
};

void fillingData(ifstream& fin, Client* clients, int n);

void quickSort(Client** clients, int start, int end);

void showResult(ofstream& fout, Client** clients, int n);

bool checkYear(Client client, int* years);

void main()
{
    int n;
    int code;
    string input, output;
    //pt >> input >> output;
    ifstream fin("input.txt");
    fin >> code >> n;
    ofstream fout("output.txt");
    Client* clients = new Client[n];
    fillingData(fin, clients, n);

    Client** ptr = new Client*[n];
    int length = 0;
    for (int i = 0; i < n; ++i) {
        if (clients[i].time != 0 && clients[i].code == code) {
            ptr[length++] = &clients[i];
        }
    }

    quickSort(ptr, 0, length - 1);
    showResult(fout, ptr, length);
}

void fillingData(ifstream& fin, Client* clients, int n)
{
    for (int i = 0; i < n; ++i) {
        fin >> clients[i].time >> clients[i].code >> clients[i].year >> clients[i].month;
    }
}

void quickSort(Client** clients, int start, int end)
{
    int i = start;
    int j = end;
    Client* pivot = clients[start + (end - start) / 2];
    while (i < j) {
        while (clients[i]->time < pivot->time || clients[i]->time == pivot->time && (clients[i]->year < pivot->year || clients[i]->year == pivot->year && clients[i]->month > pivot->month)) {
            i++;
        }
        while (clients[j]->time > pivot->time || clients[j]->time == pivot->time && (clients[j]->year > pivot->year || clients[j]->year == pivot->year && clients[j]->month < pivot->month)) {
            j--;
        }

        if (i <= j) {
            swap(clients[i], clients[j]);
            i++;
            j--;
        }
    }

    if (start < j) {
        quickSort(clients, start, j);
    }
    if (i < end) {
        quickSort(clients, i, end);
    }
}

void showResult(ofstream& fout, Client** clients, int n)
{
    int years[50];
    // for (int i = 0; i < 10; ++i) {
    //     years[i] = false;
    // }
    int length = 0;
    if (n == 0) {
        fout << "Нет данных";
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (checkYear(*clients[i], years)) {
            fout << clients[i]->time << " " << clients[i]->year << " " << clients[i]->month << endl;
            years[length++] = clients[i]->year;
        }
    }
    // if (n > 1 && checkYear(*clients[n - 1], years) && clients[n - 1]->year == clients[n - 2]->year) {
    //     fout << clients[n - 1]->time << " " << clients[n - 1]->year << " " << clients[n - 1]->month << endl;
    // }
}

bool checkYear(Client client, int* years)
{
    for (int i = 0; i < 11; ++i) {
        if (client.year == years[i]) {
            return false;
        }
    }
    return true;
}