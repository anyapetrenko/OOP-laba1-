#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <io.h>
#include <fcntl.h>

using namespace std;

struct Date
{
  int day,
    month,
    year;
};

struct DataOfUser {
    char name[256], surname[256],
     address[256],
     phoneNumber[256];
    Date dateOfBirth;
    int idNetwork;
    int postalCode;
    int id;
};

class UserDirectory {
protected:
    DataOfUser data;

public:
    UserDirectory() {}
    ~UserDirectory() {}

    void SetData(DataOfUser newData) {
        data = newData;
    }

    DataOfUser GetData() {
        return data;
    }

    void Print() {
        cout << "  ID: " << data.id << endl;
        cout << "  Имя: " << data.name << endl;
        cout << "  Фамилия: " << data.surname << endl;
        cout << "  Адрес: " << data.address << endl;
        cout << "  Номер телефона (мобильный): " << data.phoneNumber << endl;
        cout << "  Дата рождения ~ДД.ММ.ГГГГ~: " << data.dateOfBirth.day << ' ' << data.dateOfBirth.month << ' ' << data.dateOfBirth.year << endl;
        cout << "  Почтовый индекс: " << data.postalCode << endl;
        cout << "  ID соц сети: " << data.idNetwork << endl;
    }
};

struct DataOfNetwork {
    char name[256], version[256];
    char country[256];
    char owner[256];
    Date dateOfRelease;
    int yearOfLastUpdate;
    int id;
};

class NetworkDirectory {
protected:
    DataOfNetwork data;

public:
    NetworkDirectory(){}
    ~NetworkDirectory() {}

    void SetData(DataOfNetwork newData) {
        data = newData;
    }

    DataOfNetwork GetData() {
        return data;
    }

    void Print() {
        cout << "  ID: " << data.id << endl;
        cout << "  Название соцсети: " << data.name << endl;
        cout << "  Версия:: " << data.version << endl;
        cout << "  Регион: " << data.country << endl;
        cout << "  Владелец: " << data.owner << endl;
        cout << "  День выпуска ~ДД.ММ.ГГГГ~: " << data.dateOfRelease.day << ' ' << data.dateOfRelease.month << ' ' << data.dateOfRelease.year << endl;
        cout << "  Последнее обновление (год): " << data.yearOfLastUpdate << endl;
    }
};

// Ввод данных
        cout << "  Название соцсети: ";
        std::cin.ignore();
        cin >> buf.name;
        cout << "  Версия: ";
        cin >> buf.version;
        cout << "  Регион: ";
        cin >> buf.country;
        cout << "  Владелец: ";
        cin >> buf.owner;
        cout << "  День выпуска ~ДД.ММ.ГГГГ~: ";
        cin >> buf.dateOfRelease.day >> buf.dateOfRelease.month >> buf.dateOfRelease.year;
        cout << "  Последнее обновление (год): ";
        cin >> buf.yearOfLastUpdate;

        id = LastID();
        buf.id = ++id;

        system("cls");

        // Запись в конец файла
        ofstream save(fname, ios::binary | ios::app);
        save.write((char*)&buf, sizeof(buf));
        save.close();

        cout << "Данные добавлены!" << endl;
    }

    int LastID() {
        DataOfNetwork buf;
        ifstream file(fname, ios::binary | ios::in);

        // Если файл не открылся
        if (!file) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return -1;
        }

        // Выбор последнего ID
        while (!file.eof()) {
            file.read((char*)&buf, sizeof(DataOfNetwork));
        }
        file.close();

        return buf.id;
    }

    int Count() {
        DataOfNetwork buf;
        ifstream file(fname, ios::binary | ios::in);

        // Если файл не открылся
        if (!file) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return -1;
        }

        // Подсчет количества данных в файле
        count = 0;
        while (!file.eof()) {
            file.read((char*)&buf, sizeof(DataOfNetwork));
            count++;
        }
        file.close();

        count--; // так как в файле 1 пустая строка в конце, подсчет данных укажет на 1 больше, чем в действительности
        if (count < 0)
            count = 0;

        return count;
    }

    void Print() {
        // Проверка наличия данных
        if (IsEmpty()) {
            cout << "Данные пусты!" << endl;
            return;
        }

        DataOfNetwork buf;
        ifstream load(fname, ios::binary | ios::in);

        // Если файл не открылся
        if (!load) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return;
        }

        count = Count();

        // Поэлементное чтение и вывод
        for (int i = 0; i < count; i++)
        {
            load.read((char*)&buf, sizeof(DataOfNetwork));
            data.SetData(buf);
            data.Print();
            cout << "-------------------------" << endl;
        }
        load.close();
    }

    void Clear() {
        ifstream file(fname, ios::binary | ios::out);
        file.clear();
        file.close();
    }

    bool IsEmpty() {
        count = Count();
        return count == 0;
    }

    void Edit() {
        // Проверка наличия данных
        if (IsEmpty()) {
            cout << "Данные пусты!" << endl;
            return;
        }

        // Выбор позиции
        int pos;
        int id;
        cout << "Укажите ID: " << endl;
        cin >> id;

        pos = PosByID(id);
        system("cls");

        // Проверка выбранной позиции
        if (pos < 0 || pos > count - 1) {
            cout << "Позиция выбрана неверно!" << endl;
            return;
        }

        DataOfNetwork buf;

        // Ввод данных
        cout << "  Название соцсети: ";
        std::cin.ignore();
        cin >> buf.name;
        cout << "  Версия: ";
        cin >> buf.version;
        cout << "  Регион: ";
        cin >> buf.country;
        cout << "  Владелец: ";
        cin >> buf.owner;
        cout << "  День выпуска ~ДД.ММ.ГГГГ~: ";
        cin >> buf.dateOfRelease.day >> buf.dateOfRelease.month >> buf.dateOfRelease.year;
        cout << "  Последнее обновление (год): ";
        cin >> buf.yearOfLastUpdate;
        system("cls");

        buf.id = id;

// Запись в указанное место в файле
        ofstream save(fname, ios::binary | ios::in);
        save.seekp(sizeof(buf) * pos, ios::beg);
        save.write((char*)&buf, sizeof(buf));
        save.close();

        cout << "Данные изменены!" << endl;
    }

    void Del() {
        // Проверка наличия данных
        if (IsEmpty()) {
            cout << "Данные пусты!" << endl;
            return;
        }

        // Выбор позиции
        int pos;
        int id;
        cout << "Укажите ID: " << endl;
        cin >> id;

        system("cls");

        pos = PosByID(id);
        pos++;

        // Проверка выбранной позиции
        if (pos < 0 || pos > count - 1) {
            cout << "Позиция выбрана неверно!" << endl;
            return;
        }

        // Новый вариант удаления

        // Читаем файл с места следующего после удаления
        DataOfNetwork buf;
        ifstream load(fname, ios::binary | ios::in);
        load.seekg(sizeof(buf) * pos, ios::beg);

        // Записываем на место удаляемого
        ofstream save(fname, ios::binary | ios::in);
        save.seekp(sizeof(buf) * (pos - 1), ios::beg);

        int biteSize = 0;
        for (int i = pos; i < count; i++) {
            load.read((char*)&buf, sizeof(DataOfNetwork));
            save.write((char*)&buf, sizeof(buf));
        }

        load.close();
        save.close();

        // Открываем файл для обрезания не нужной части
        int fh, result;
        if (_sopen_s(&fh, fname.c_str(), _O_RDWR | _O_CREAT, _SH_DENYNO,
            _S_IREAD | _S_IWRITE) == 0)
        {
            cout << "Размер файла до удалени: " << _filelength(fh) << endl;

            if ((result = _chsize(fh, sizeof(DataOfNetwork) * (count - 1))) == 0)
                cout << "Размер файла изменен..." << endl;
            else
                cout << "Ошибка изменения размера файла!" << endl;

            cout << "Текущий размер файла: " << _filelength(fh) << endl;
            _close(fh);
        }

        cout << "Данные удалены!" << endl;
    }

    void Search() {
        // Проверка наличия данных
        if (IsEmpty()) {
            cout << "Данные пусты!" << endl;
            return;
        }

        int id;
        cout << "Укажите ID для поиска: ";
        cin >> id;

        system("cls");

        DataOfNetwork buf;
        ifstream load(fname, ios::binary | ios::in);
        bool found = false;

        // Если файл не открылся
        if (!load) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return;
        }

        count = Count();

        // Поэлементное чтение и вывод
        for (int i = 0; i < count; i++)
        {
            load.read((char*)&buf, sizeof(DataOfNetwork));

            if (id == buf.id) {
                data.SetData(buf);
                data.Print();
                found = true;
                break;
            }
        }
        load.close();

        if (!found)
            cout << "Совпадений не найдено!" << endl;
    }

    int PosByID(int id) {
        DataOfNetwork buf;
        ifstream load(fname, ios::binary | ios::in);

        // Если файл не открылся
        if (!load) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return -1;
        }

        int count = Count();
        int pos = -1;

        // Поэлементное чтение и вывод
        for (int i = 0; i < count; i++)
        {
            load.read((char*)&buf, sizeof(DataOfNetwork));

            if (id == buf.id) {
                pos = i;
                break;
            }
        }
        load.close();

        return pos;
    }

    void Menu(int& act) {
        cout << "Выберите действие: " << endl
            << "(0) Назад" << endl
            << "(1) Вывод" << endl
            << "(2) Добавить" << endl
            << "(3) Изменить" << endl
            << "(4) Удалить" << endl
            << "(5) Поиск" << endl
            << "(6) Очистить" << endl
            << "(7) Изменить файл" << endl
            << "Ваш выбор: ";
        cin >> act;

system("cls");
    }
};
...class DataBase {
public:
    UserBase users;
    NetworkBase networks;

    DataBase(){}
    ~DataBase(){}

    void ModeMenu(int& act) {
        cout << "Выберите режим: " << endl
            << "(0) Выход" << endl
            << "(1) Пользователи" << endl
            << "(2) Соц Сети" << endl
            << "(3) Определить соц сеть у пользователя" << endl
            << "Ваш выбор: ";
        cin >> act;

        system("cls");
    }

    void Identify() {
        if (users.IsEmpty() || networks.IsEmpty()) {
            cout << "Данные отсутствуют!" << endl;
            return;
        }

        int idNetwork = -1;
        int id;
        cout << "Укажите ID пользователя: ";
        cin >> id;

        system("cls");

        // Чтение данных о пользователях
        string fnameUsers = users.FileName("");
        int countUsers = users.Count();

        UserDirectory dataUser;
        DataOfUser buf;
        ifstream loadUsers(fnameUsers, ios::binary | ios::in);
        bool found = false;

        // Если файл не открылся
        if (!loadUsers) {
            cout << "Ошибка открытия файла класса UserBase!" << endl;
            return;
        }

        // Поэлементное чтение и вывод
        for (int i = 0; i < countUsers; i++)
        {
            loadUsers.read((char*)&buf, sizeof(DataOfUser));

            if (id == buf.id) {
                idNetwork = buf.idNetwork;

                cout << "*** Данные пользователя ***" << endl;
                dataUser.SetData(buf);
                dataUser.Print();

                break;
            }
        }
        loadUsers.close();

        if (idNetwork == -1)
            cout << "Совпадений не найдено!" << endl;

        // Чтения данных о соц сетях
        string fnameNetwork = networks.FileName("");
        int countNetwork = networks.Count();

        NetworkDirectory dataNetwork;
        DataOfNetwork bufN;

        ifstream load(fnameNetwork, ios::binary | ios::in);

        // Если файл не открылся
        if (!load) {
            cout << "Ошибка открытия файла класса NetworkBase!" << endl;
            return;
        }

        // Поэлементное чтение и вывод
        for (int i = 0; i < countNetwork; i++)
        {
            load.read((char*)&bufN, sizeof(DataOfNetwork));

            if (idNetwork == bufN.id) {
                cout << "\n*** Данные о соц сети ***" << endl;
                dataNetwork.SetData(bufN);
                dataNetwork.Print();
                found = true;
                break;
            }
        }
        load.close();

        if (!found)
            cout << "Совпадений не найдено!" << endl;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
   // SetConsoleOutputCP(1251);

    DataBase db;
    int act = 0;
    int mode = 0;
    string fname;

    do {
        db.ModeMenu(mode);

        switch (mode)
        {
        case 0:
            break;

        case 1:
            do {
                db.users.Menu(act);

                switch (act)
                {
                case 0:
                    break;

                case 1:
                    db.users.Print();
                    break;

                case 2:
                    db.users.Add();
                    break;

                case 3:
                    db.users.Edit();
                    break;

                case 4:
                    db.users.Del();
                    break;

                case 5:
                    db.users.Search();
                    break;

                case 6:
                    db.users.Clear();
                    break;

                case 7:
                    cout << "Укажите имя файла: ";
                    cin >> fname;
                    db.users.FileName(fname);
                    break;

                default:
                    cout << "Неверный выбор!" << endl;
                    break;
                }

system("pause");
                system("cls");
            } while (act != 0);
            act = -1; // значение, которое не проверяется
            break;

        case 2:
            do {
                db.networks.Menu(act);

                switch (act)
                {
                case 0:
                    break;

                case 1:
                    db.networks.Print();
                    break;

                case 2:
                    db.networks.Add();
                    break;

                case 3:
                    db.networks.Edit();
                    break;

                case 4:
                    db.networks.Del();
                    break;

                case 5:
                    db.networks.Search();
                    break;

                case 6:
                    db.networks.Clear();
                    break;

                case 7:
                    cout << "Укажите имя файла: ";
                    cin >> fname;
                    db.users.FileName(fname);
                    break;

                default:
                    cout << "Неверный выбор!" << endl;
                    break;
                }

                system("pause");
                system("cls");
            } while (act != 0);
            act = -1; // значение, которое не проверяется
            break;

        case 3:
            db.Identify();
            break;

        default:
            cout << "Неверный выбор!" << endl;
            break;
        }

        system("pause");
        system("cls");
    } while (mode != 0);
}
