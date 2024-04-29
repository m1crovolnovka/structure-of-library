#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <fstream>

using namespace std;

struct Book {
    int bookNumber;
    string author;
    string title;
    int year;
    string publisher;
    int pageCount;
};


void View(Book *mas, int count) {
    for (int i = 0;i < count;i++)
        cout << to_string(mas[i].bookNumber) + ' ' + mas[i].author + " " + mas[i].title + ' ' + to_string(mas[i].year) + ' ' + mas[i].publisher + ' ' + to_string(mas[i].pageCount) + '\n';

}

int Year_before(Book* p, int count, int year) {
    for (int i = 0; i < count;i++) {
        if (p[i].year <= year) {
            for (int k = i; k < count - 1;k++) {
                p[k] = p[k + 1];
            }
            count--;
            i--;
        }
    }
    return count;
}
void Sort_pryam_vibor(Book* p, int count) {
    int buf;
    Book r;
    for (int i = 0; i < count - 1; i++)
    {
        buf = i;
        for (int k = i + 1;k < count; k++)
        {
            if (p[buf].author > p[k].author)
                buf = k;
        }
        if (buf == i) continue;
        r = p[buf];
        p[buf] = p[i];
        p[i] = r;

    }
}
int Search_binary(Book* mas, int size, string author) {
    Book mid = mas[int(size / 2)];
    if (mid.author == author) {
        return mid.bookNumber;
    }
    else {
        if (size == 0){
            cout << "Такого автора нет\n";
        return -1;
    }
        else{
            if (mid.author > author) 
                return Search_binary(mas, size / 2, author);
                    
            else {

                return Search_binary(&mas[size / 2 + 1], size - size / 2 - 1, author);
            }
        }
    }
}
void qsortRecursive(Book* mas, int size) {
    int i = 0;
    int j = size - 1;
    Book mid = mas[size / 2];
    do {
        while (mas[i].author < mid.author)
            i++;
        while (mas[j].author > mid.author)
            j--;
        if (i <= j) {
            Book tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        qsortRecursive(mas, j + 1);  
    if (i < size-1)
        qsortRecursive(&mas[i], size - i);
}
int Search_line(string author) {
    ifstream filin;
    filin.open("Data.txt");
    int count = 0;
    string stroka;
    while (!filin.eof()) {
        stroka = " ";
        getline(filin, stroka, '/');
        getline(filin, stroka, '/');
        if (stroka == author) {
            filin.close();
            return count;
        }
        getline(filin, stroka);
        count++;
    }
    filin.close();
    return -1;
}
string vivod(Book* mas, int count) {
    ifstream filin;
    filin.open("Data.txt", ifstream::in);
    string stroka;
    int i = 0;
    while (!filin.eof() && i != count) {
        getline(filin, stroka, '/');
        mas[i].bookNumber = atoi(stroka.c_str());
        getline(filin, stroka, '/');
        mas[i].author = stroka;
        getline(filin, stroka, '/');
        mas[i].title = stroka;
        getline(filin, stroka, '/');
        mas[i].year = atoi(stroka.c_str());
        getline(filin, stroka, '/');
        mas[i].publisher = stroka;
        getline(filin, stroka);
        mas[i].pageCount = atoi(stroka.c_str());
        i++;
    }
    filin.close();
    return stroka;
}

int vvod(Book* mas, int count) {
    ofstream filin;
    filin.open("Data.txt", fstream::app);
    for (int i = count -1; i < count;i++) {
        filin << mas[i].bookNumber<< '/' << mas[i].author << '/'<< mas[i].title +  '/' << mas[i].year<< '/' + mas[i].publisher + '/' <<mas[i].pageCount <<'\n';
    }
    filin.close();
    return 0;
}
int vvod_time(Book* mas, int count) {
    ofstream filin;
    filin.open("ChangedFile.txt");
    for (int i = 0; i < count;i++) {
        filin << to_string(mas[i].bookNumber) + ' ' + mas[i].author + " \"" + mas[i].title + "\" " + to_string(mas[i].year) + ' ' + mas[i].publisher + ' ' + to_string(mas[i].pageCount) + '\n';
    }
    filin.close();
    return 0;
}
int Count() {
    ifstream filin;
    filin.open("Data.txt", ifstream::in);
    int count = -1;
    string stroka;
    while (!filin.eof()) {
        getline(filin, stroka);
        count++;
    }
    filin.close();
    return count;
}

void Add(Book* mas, int count) {
    string stroka;
    int value;
    if (mas[count - 1].bookNumber == NULL)
        mas[count].bookNumber = 1;
    else
        mas[count].bookNumber = mas[count - 1].bookNumber + 1;
    cout << "Введите автора книги\n";
    cin.ignore();
    getline(cin, stroka);
    mas[count].author = stroka;
    cout << "Введите название книги\n";
    getline(cin, stroka);
    mas[count].title = stroka;
    cout << "Введите год издания книги\n";
    while (true) {
                cin >> mas[count].year;
                if (cin.fail()) {
                    cout << "Please try again" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else break;
           }
    cin.ignore();
    cout << "Введите издательство выпустившее книгу\n";
    getline(cin, stroka);
    mas[count].publisher = stroka;
    cout << "Введите количество страниц в книге\n";
    while (true) {
        cin >> mas[count].pageCount;
        if (cin.fail() || mas[count].pageCount<0) {
            cout << "Please try again" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else break;
    
    }
    cin.ignore();

}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    while (true) {
        int bam;
        string author;
        int count = Count();
        Book* t = new Book[count + 1];
        cout << "Выберете пункт из данных:" << endl << "1 - Просмотр книг" << endl << "2 - Вывести список книг в алфавитном порядке по автору, изданных после заданного года" << endl << "3 - Вывести отсортированный список" << endl << "4 - Дополнить список\n" <<"5 - Поиск книги (по автору)\n" << "6 - Выход\n";
        while (true) {
            cin >> bam;
            if (cin.fail() || bam <= 0 || bam > 6) {
                cout << "Please try again" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else {
                break;
            }
        }
        switch (bam) {
        case 1:
            vivod(t, count);
            View(t, count);
            vvod_time(t, count);
            delete[] t;
            break;
        case 2:
            vivod(t, count);
            qsortRecursive(t, count);
            cout << "Введите заданный год\n";
            while(true) {
                cin >> bam;
                if (cin.fail()) {
                    cout << "Please try again" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    break;
                }
            }
            count = Year_before(t, count, bam);
            View(t, count);
            vvod_time(t, count);
            delete[] t;
            break;
        case 3:
            cout << "Какую сортировку вы хотите использовать\n" << "1 - Сортировка прямого выбора\n" << "2 - QuickSotr\n";
            while (true) {
                cin >> bam;
                if (cin.fail() || bam <= 0 || bam > 2) {
                    cout << "Please try again" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    break;
                }
            }
            vivod(t, count);
            switch (bam) {
            case 1:
                Sort_pryam_vibor(t, count);
                break;

            case 2:
                qsortRecursive(t, count);
            }
            View(t, count);
            vvod_time(t, count);
            delete[] t;
            break;
        case 4:
            vivod(t, count);
            Add(t, count);
            View(t, count + 1);
            vvod(t, count + 1);
            vvod_time(t, count + 1);
            delete[] t;
            break;
        case 5: 
            cout << "Введите способ поиска:\n1-Линейный поиск в файле\n2-Бинарный поиск в структуре\n";
            while (true) {
                cin >> bam;
                if (cin.fail() || bam <= 0 || bam > 2) {
                    cout << "Please try again" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    break;
                }
            }
            cout << "Введите автора\n";
            cin.ignore();
            getline(cin, author);
            
            vivod(t, count);
            switch (bam) {
            case 1:
                bam = Search_line(author);
                if (bam == -1) {
                    break;
                }
                break;

            case 2:         
                Sort_pryam_vibor(t, count);
                bam = Search_binary(t, count, author) - 1;
                if (bam < -1) {
                    break;
                }
                vivod(t, count);
                break;
            }
            vvod_time(&t[bam], 1);
            View(&t[bam], 1);
            delete[] t;
            break;
            
            break;
        case 6:
            delete[] t;
            return 0;
        }  
    }
    return 0;
}
