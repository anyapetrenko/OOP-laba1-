#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct TNode
{
    char type;
    double num;
    TNode* left;
    TNode* right;
};

char find_lexema();
TNode* exp1();
TNode* exp2();
TNode* exp3();

string s;
int i = 0;
char lexema;
double N;

double calculate(TNode* root, bool& error)
{
    if (root == NULL)
    {
        error = true;
        return 0;
    }
    if (root->type == 'n') return root->num;
    if (root->type == '+') return calculate(root->left, error) + calculate(root->right, error);
    if (root->type == '-') return calculate(root->left, error) - calculate(root->right, error);
    if (root->type == '*') return calculate(root->left, error) * calculate(root->right, error);
    if (root->type == '/')
    {
        double res = calculate(root->right, error);
        if (res != 0) return calculate(root->left, error) / res;
        else
        {
            cout << "ERROR: Divizion by zero is prohibited\n";
            return 0;
        }
    }
    if (root->type == 's') return sin(calculate(root->left, error));
}
char find_lexema()
{
    if (i >= s.size()) return 'e';
    if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')
    {
        i++;
        return s[i-1];
    }
    if(s[i] == 's')
        if (s.substr(i, 4) == "sin(")
        {
            i = i + 4;
            return 's';
        }
        else
        {
            cout << "ERROR: invalid syntax\n";
            return 'e';
        }
    if (s[i] >= '0' && s[i] <= '9')
    {
        N = 0;
        while (isdigit(s[i]))
        {
            N = N * 10 + (s[i] - 48);
            i++;
        }
        return 'n';
    }
    else
    {
        cout << "ERROR: There is no suitable lexema\n";
        return 'e';
    }
}

TNode* exp1()
{
    TNode* temp = exp2();
    while (lexema == '+' || lexema == '-')
    {
        TNode* node = new TNode;
        node->left = temp;
        node->type = lexema;
        node->right = exp2();
        temp = node;
    }
    return temp;
}

TNode* exp2()
{
    TNode* temp = exp3();
    while (lexema == '*' || lexema == '/')
    {
        TNode* node = new TNode;
        node->left = temp;
        node->type = lexema;
        node->right = exp3();
        temp = node;
    }
    return temp;
}

TNode* exp3()
{
    lexema = find_lexema();
    if (lexema == 'n')
    {
        TNode* temp = new TNode;
        temp->type = 'n';
        temp->num = N;
        temp->left = NULL;
        temp->right = NULL;
        lexema = find_lexema();
        return temp;
    }
    if (lexema == 's')
    {
        TNode* temp = new TNode;
        temp->type = 's';
        temp->right = NULL;
        temp->left = exp1();
        if (lexema == ')')
        {
            lexema = find_lexema();
            return temp;
        }
        else
        {
            cout << "ERROR: The bracket isn't closed\n";
            return NULL;
        }
        lexema = find_lexema();

        return temp;
    }
    if (lexema == '(')
    {
        TNode* temp = exp1();
        if (lexema == ')')
        {
            lexema = find_lexema();
            return temp;
        }
        else
        {
            cout << "ERROR: The bracket isn't closed\n";
            return NULL;
        }
    }
}

int main()
{
    int N; bool error; double res;
    cout << "Enter the number of expressions you want to count\n";
    cin >> N;
    for (int j = 0; j < N; j++)
    {
        i = 0;
        cout << "Enter an expression:\n";
        cin >> s;
        error = false;
        TNode* root = exp1();
        res = calculate(root, error);
        if (!error)
        {
            cout << "The result is equal:\n";
            cout << res << '\n';
        }
    }
    return 0;
}