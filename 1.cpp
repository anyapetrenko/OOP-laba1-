#include <string>
#include <iostream>
#include <ctime>

using namespace std;

typedef struct node
{
    int inf;
    node* left, * right;
} TNode;


void initTree(TNode*& root, int cntEl);
void insTree(TNode*& root, TNode* elem);
void findInTree(int key, TNode* root, TNode*& findNode);
void getMaxMin(TNode* root, int& max, int& min);
void delTree(TNode*& root);
void showTree(TNode* root);
void Read(TNode* root);

void t6(TNode*& root);
void t7(TNode*& root);

void initTree(TNode*& root, int cntEl)
{
    TNode* pNew;
    root = NULL;
    srand(time(NULL) | clock());
    for (int i = 0; i < cntEl; i++)
    {
        pNew = new TNode;
        pNew->inf = rand() % 100 - 50;
        pNew->left = NULL;
        pNew->right = NULL;
        insTree(root, pNew);
    }
}
void insTree(TNode*& root, TNode* elem)
{
    if (root == NULL)
    {
        root = elem;
    }
    else
    if (elem->inf < root->inf)
    {
        insTree(root->left, elem);
    }
    else
    {
        insTree(root->right, elem);
    }
}
void findInTree(int key, TNode* root, TNode*& findNode)
{
    if (root == NULL)
    {
        findNode = NULL;
        return;
    }
    if (root->inf > key)
    {
        findInTree(key, root->left, findNode);
    }
    else
    if (root->inf < key)
    {
        findInTree(key, root->right, findNode);
    }
    else
    {
        findNode = root;
        return;
    }
}

void getMaxMin(TNode* root, int& max, int& min)
{
    if (root == NULL)
    {
        return;
    }
    if (root->inf > max)
    {
        max = root->inf;
    }
    if (root->inf < min)
    {
        min = root->inf;
    }
    getMaxMin(root->left, max, min);
    getMaxMin(root->right, max, min);
}

void delTree(TNode*& root)
{
    if (root == NULL)
        return;
    if (root->left != NULL)
        delTree(root->left);
    if (root->right != NULL)
        delTree(root->right);
    if (root->left == NULL && root->right == NULL)
    {
        TNode* del = root;
        delete del;
        root = NULL;
    }
}

void showTree(TNode* root)
{
    static int tab = 0;
    if (!root)
    {
        cout << "NULL" << endl;
        return;
    }
    cout << root->inf << endl;
    tab++;
    for (int i = 0; i < tab; i++)
    {
        cout << "\t";
    }
    cout << "лв:";
    showTree(root->left);
    for (int i = 0; i < tab; i++)
    {
        cout << "\t";
    }
    cout << "пр:";
    showTree(root->right);
    tab--;
}

void Read(TNode* root)
{
    if (root != NULL)
    {
        PBDSP(root->left); //прохід в симетричному порядку лівого піддерева
        cout << root->inf << endl; //роздруківка вмісту
        PBDSP(root->right); //прохід в симетричному порядку правого піддерева
    }
}

void t6(TNode*& root)
{
    if (root == NULL)
    {
        return;
    }
    // если элемент отрицательный
    if (root->inf < 0)
    {
        root->inf = 0; // заменяем на 0
    }
    // рекурсивно вызываем функцию для левого и правого поддерева
    task6(root->left);
    task6(root->right);
}

void t7(TNode*& root)
{
    if (root == NULL)
    {
        return;
    }

    int s = (root->left ? root->left->inf : 0) + (root->right ? root->right->inf : 0);
    if (s % 2 == 0)
    {
        cout << root->inf << " (сума = " << s << ")" << endl;
    }

    task7(root->left);
    task7(root->right);
}


TNode* root;
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    root = NULL;
    char ch;
    do {
        system("clear");
        cout << "Выберите операцию, которую хотите выполнить:\n";
        cout << "---------------------------------\n";
        cout << "1.Сформировать бинарное дерево\n";
        cout << endl;
        cout << "2.Вывести минимальное и максимальное значение елемента\n";
        cout << endl;
        cout << "3.Вывести дерево\n";
        cout << endl;
        cout << "4.Удалить все дерево\n";
        cout << endl;
        cout << "5.Симетричный обход \n";
        cout << endl;
        cout << "6.Заменить все отрицательные узлы на нули\n";
        cout << endl;
        cout << "7.Вывести узлы, с парной сумой потомков\n";
        cout << "---------------------------------\n";
        cout << endl;
        cout << "Выберите операцию: ";
        cin >> ch;
        switch (ch) {
            case '1':
            {
                int cnt;
                cout << "\nВведите количество елементов дерева: ";
                cin >> cnt;
                initTree(root, cnt);
                cout << "\nДерево сформировано\n";
            }
                break;
            case '2':
            {
                int max = INT_MIN, min = INT_MAX;
                getMaxMin(root, max, min);
                cout << "\nМаксимальное значение: " << max << "\n";
                cout << "\nМинимальное значение: " << min << "\n";
            }
                break;
            case '3':
            {
                cout << "\n";
                showTree(root);
                cout << "\n";
            }
                break;
            case '4':
            {
                delTree(root);
                cout << "\nДерево удалено!\n";
            }
                break;
            case '5':
            {
                cout << "\n";
                Read(root);
                cout << "\n";
            }
                break;
            case '6':
            {
                cout << "\nК изменениям\n";
                showTree(root);
                cout << "\n";
                t6(root);
                cout << "\nПосле:\n";
                showTree(root);
                cout << "\n";
            }
                break;
            case '7':
            {
                cout << "\n";
                t7(root);
                cout << "\n";
            }
                break;
        }
    } while (true);
}
