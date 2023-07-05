#include <iostream>
#include <regex>
#include <conio.h>
#include <fstream>
#include <vector>
#include "Registration.h"
#include "Registration.cpp"

using namespace std;

int main()
{
    user_data user[100];
    int choose = 0, user_counter = 0, password_counter = 0;
    load_data(user, user_counter, password_counter);
    while (choose != 4)
    {
        cout << "Choose From The Menu Below:" << endl;
        cout << "1- Register" << endl;
        cout << "2- Login" << endl;
        cout << "3- Change password" << endl;
        cout << "4- Exit" << endl;
        cin >> choose;
        cin.clear();
        cin.sync();
        if (choose == 1)
        {
            sign_up(user, user_counter, password_counter);
        }
        else if (choose == 2)
        {
            login(user, user_counter);
        }
        else if (choose == 3)
        {
            change_password(user, user_counter);
        }
        else if (choose == 4)
        {
            break;
        }
    }
}

