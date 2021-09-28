#include <iostream>
#include <vector>
#include <fstream>
//#include <windows.h>
#include <string>

using namespace std;
class CharacterDirectory {
public:
    string name, surname;
    string alias;
    string mentionedIn;
    int dayOfBirth, monthOfBirth, yearOfBirth;
    int role;
    int id;

    void read() {
        cout << "  Имя: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        cout << "  Фамилия: ";
        std::getline(std::cin, surname);
        cout << "  Позывной: ";
        std::getline(std::cin, alias);
        cout << "  Персонаж появляется в книгах: ";
        std::getline(std::cin, mentionedIn);
        cout << "  Роль (1 - Главная, 2 - Второстепенная, 3 - Эпизодическая: ";
        cin >> role;
    }

    void print() {
        cout << "  Имя: " << name << endl;
        cout << "  Фамилия: " << surname << endl;
        cout << "  Позывной: " << alias << endl;
        cout << "  Персонаж появляется в книгах: " << mentionedIn << endl;
        cout << "  Роль: " << role << endl;
    }

    void readBooksMentionedIn() {
        cout << "  Персонаж появляется в книгах: ";
        cin >> mentionedIn;
    }

    void readRole() {
        cout << "  Роль: ";
        cin >> role;
    }
};

class BooksDirectory {
public:
    string name, author;
    string description;
    int dayOfRelease, monthOfRelease, yearOfRelease;
    int numberOfPages;
    int id;

    void read() {
        cout << "  Название книги: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        cout << "  Автор: ";
        std::getline(std::cin, author);
        cout << "  Короткое описание: ";
        std::getline(std::cin, description);
        cout << "  Дата выхода (день, месяц, год): ";
        cin >> dayOfRelease >> monthOfRelease >> yearOfRelease;
        cout << "  Количество страниц: ";
        cin >> numberOfPages;
    }

    void print() {
        cout << "  Название книги: " << name << endl;
        cout << "  Автор: " << author << endl;
        cout << "  Короткое описание: " << description << endl;
        cout << "  Дата выхода (день, месяц, год): " << dayOfRelease << ' ' << monthOfRelease << ' ' << yearOfRelease << endl;
        cout << "  Количество страниц: " << numberOfPages << endl;
    }

    void readDescription() {
        cout << "  Описание: ";
        cin >> description;
    }
    void readNumberOfPages() {
        cout << "  Количество страниц: ";
        cin >> numberOfPages;
    }
};

class CharacterBase {
public:
    int id = 1;
    vector<CharacterDirectory> data;

    void add() {
        CharacterDirectory temp;
        temp.read();
        temp.id = id++;
        cout << "  Индекс: " << temp.id << endl;
        data.push_back(temp);
    }

    int search(int id) {
        for (int i = 0; i < data.size(); i++)
            if (data[i].id == id)
                return i;

        return -1;
    }

    void remove(int pos) {
        data.erase(data.begin() + pos);
    }

    void open(const string& filename)
    {
        fstream ifs;
        ifs.open(filename, fstream::in | fstream::binary);
        if (ifs.fail())
            return;
        while (ifs.peek() != -1)
        {
            CharacterDirectory character;
            std::getline(ifs, character.name);
            std::getline(ifs, character.surname);
            std::getline(ifs, character.alias);
            std::getline(ifs, character.mentionedIn);
            ifs.read((char*)&character.role, sizeof(character.role));
            //user.print();
            character.id = id++;
            data.push_back(character);
        }
    }

    void save(const string& filename)
    {
        fstream ofs;
        ofs.open(filename, fstream::out | fstream::binary);
        for (unsigned int i = 0; i < data.size(); ++i)
        {
            ofs << data[i].name << '\n';
            ofs << data[i].surname << '\n';
            ofs << data[i].alias << '\n';
            ofs << data[i].mentionedIn << '\n';
            ofs.write((char*)&data[i].role, sizeof(data[i].role));
        }
    }
};

class BookBase {
public:
    int id = 1;
    vector<BooksDirectory> data;

    void add() {
        BooksDirectory temp;
        temp.read();
        temp.id = id++;
        cout << "  Индекс: " << temp.id << endl;
        data.push_back(temp);
    }

    int search(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].id == id) {
                return i;
            }
        }

        return -1;
    }

    void remove(int pos) {
        data.erase(data.begin() + pos);
    }

    void open(const string& filename)
    {
        fstream ifs;
        ifs.open(filename, fstream::in | fstream::binary);
        if (ifs.fail())
            return;
        while (ifs.peek() != -1)
        {
            BooksDirectory book;
            std::getline(ifs, book.name);
            std::getline(ifs, book.author);
            std::getline(ifs, book.description);
            ifs.read((char*)&book.dayOfRelease, sizeof(book.dayOfRelease));
            ifs.read((char*)&book.monthOfRelease, sizeof(book.monthOfRelease));
            ifs.read((char*)&book.yearOfRelease, sizeof(book.yearOfRelease));
            ifs.read((char*)&book.numberOfPages, sizeof(book.numberOfPages));
            book.id = id++;
            data.push_back(book);

        }
    }

    void save(const string& filename)
    {
        fstream of;
        of.open(filename, fstream::out | fstream::binary);
        for (unsigned int i = 0; i < data.size(); ++i)
        {
            of << data[i].name << '\n';
            of << data[i].author << '\n';
            of << data[i].description << '\n';
            of.write((char*)&data[i].dayOfRelease, sizeof(data[i].dayOfRelease));
            of.write((char*)&data[i].monthOfRelease, sizeof(data[i].monthOfRelease));
            of.write((char*)&data[i].yearOfRelease, sizeof(data[i].yearOfRelease));
            of.write((char*)&data[i].numberOfPages, sizeof(data[i].numberOfPages));
        }
    }
};

class CharacterInBookBase
{
public:
    vector<pair<int, int>> data;

    void addUserToNetwork(int character, int book)
    {
        data.push_back(make_pair(character, book));
    }

    void removeCharacter();

    void removeBook();
};

int main() {

    setlocale(LC_ALL, "Russian");
    const string charDir = "Персонажи.dat";
    const string booksDir = "Книги.dat";
    const string connection = "Связь.txt";

    BookBase book_base;
    CharacterBase char_base;
    BookBase book_char_connection;

    book_char_connection.open(connection);
    book_base.open(booksDir);
    char_base.open(charDir);

    int choice, option;
    bool exit = false;

    while (true) {
        cout << " Выберите операцию для выполнения:" << endl;
        cout << " ~~~ I. Добавить персонажа  II. Добавить книгу \n ~~~ III. Редактировать книгу  IV. Редактировать персонажа \n ~~~ V. Удалить книгу  VI. Удалить персонажа \n ~~~ VII. Найти книгу  VIII. Найти персонажа \n ~~~ IX. Связь персонажа с книгой \n ~~~ X. Выход с программы " << endl;
        cout << " \nОперация: "; cin >> choice;

        switch (choice) {
            case 1: {
                char_base.add();
                break;
            }
            case 2: {
                book_base.add();
                break;
            }
            case 3: {
                cout << " Что именно вы хотите отредактировать?" << endl;
                cout << " (1) Описание (2) Количество страниц" << endl;
                cout << "Операция: "; cin >> option;

                switch (option) {
                    case 1: {
                        int id;
                        cout << " Индекс книги: "; cin >> id;
                        int pos = book_base.search(id);

                        if (pos != -1) {
                            book_base.data[pos].readDescription();
                            cout << "Информация обновлена." << endl;
                        }
                        else
                            cout << "Книги с таким индексом не существует." << endl;

                        break;
                    }
                    case 2: {
                        int id;
                        cout << " Индекс книги: "; cin >> id;
                        int pos = book_base.search(id);

                        if (pos != -1)
                            book_base.data[pos].readNumberOfPages();
                        else
                            cout << "Книги с таким индексом не существует." << endl;

                        break;
                    }
                }
                break;
            }
            case 4: {
                //
                //
            }
                break;
            case 5: {
                int id;
                cout << " Индекс книги: "; cin >> id;
                int pos = book_base.search(id);

                if (pos != -1)
                    book_base.remove(pos);
                else
                    cout << "Книги с таким индексом не существует." << endl;
                break;
            }
            case 6: { // удаление пользователя и аккаунтов
                int id;
                cout << " Индекс персонажа: "; cin >> id;
                int pos = char_base.search(id);
                if (pos != -1)
                    char_base.remove(pos);
                else
                    cout << "Книги с таким индексом не существует." << endl;
                break;
            }
            case 7: {
                int id;
                cout << " Индекс книги: "; cin >> id;
                int pos = book_base.search(id);

                if (pos != -1)
                    book_base.data[pos].print();
                else
                    cout << "Книги с таким индексом не существует." << endl;
                break;
            }
            case 8: {
                int id;
                cout << " Индекс персонажа:"; cin >> id;
                int pos = char_base.search(id);
                if (pos != -1)
                    char_base.data[pos].print();
                else
                    cout << "Персонажа с таким индексом не существует." << endl;
                break;
            }
            case 9: {
                int book_id;
                int char_id;
                cout << " Индекс книги: "; cin >> book_id;
                int pos_book = book_base.search(book_id);
                cout << " Индекс персонажа:  "; cin >> char_id;
                int pos_char = char_base.search(char_id);
                if (pos_book != -1 && pos_char != -1) {

                    cout << "Связь была установлена." << endl;
                    fstream bookBase;
                    bookBase.open(connection, fstream::in | fstream::out | fstream::app);
                    bookBase << "  В книге с индексом " << book_id << " появляется персонаж с индексом " << char_id << endl;
                    bookBase.close();
                    cout << "  В книге с индексом " << book_id << " появляется персонаж с индексом " << char_id << endl;
                    book_base.data[pos_book].print();
                    cout << "-------------------------------------------------------------------" << endl;
                    char_base.data[pos_char].print();

                }
                else
                    cout << "Нет персонажа или книги с таким индексом" << endl;
                break;
            }

            case 10:
                exit = true;
                break;
            default:
                exit = true;
        }

        if (exit) {
            break;
        }

        cout << endl;
    }
    book_base.save(booksDir);
    char_base.save(charDir);
    return 0;
}