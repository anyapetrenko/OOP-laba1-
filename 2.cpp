system("cls");
    }
};

class DataBase {
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
