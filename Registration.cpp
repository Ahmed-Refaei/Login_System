#include <iostream>
#include <regex>
#include <conio.h>
#include <fstream>
#include <vector>
#include "Registration.h"

using namespace std;


string valid_password()
{
    // defining variables
    int a, chars = 0;
    string pass;
    string confirmation;
    // rules to accept password
    cout << "* password at least 8 charcters" << endl;
    cout << "* contain at least one uppercase letter" << endl;
    cout << "* contain at least one special character (? ! @ # $ % & *)" << endl;
    // input password
    cout << "password: ";

    while ((a = getch()) != 13)
    {
        if (a == 8 && chars > 0)
        {
            chars--;
            pass.pop_back();
            cout << "\b \b";
        }
        else
        {
            pass.push_back(a);
            cout << '*';
            chars++;
        }
    }
    // check the password
    regex filter("(?=.*[a-z])(?=.*[1-9])(?=.*[A-Z])(?=.*[?!@#$%])[a-z|A-Z|0-9|!?#@$%]{6,}");
    while (regex_match(pass, filter) != true)
    {
        cout << endl
             << "enter valid password: \n"
             << pass;

        while ((a = getch()) != 13)
        {
            if (a == 8)
            {
                pass.pop_back();
                cout << "\b \b";
            }
            else
            {
                pass.push_back(a);
                cout << '*';
            }
        }
    }
    // confirm the password
    cout << endl
         << "confirm password: ";

    while ((a = getch()) != 13)
    {
        if (a == 8)
        {
            confirmation.pop_back();
            cout << "\b \b";
        }
        else
        {
            confirmation.push_back(a);
            cout << '*';
        }
    }
    while (pass != confirmation)
    {
        cout << endl
             << "pls enter the same password" << endl;
        cout << "confirm password: ";
        confirmation.clear(); // To Clear The Password Stored in The Confirmation
        while ((a = getch()) != 13)
        {
            if (a == 8)
            {
                confirmation.pop_back();
                cout << "\b \b";
            }
            else
            {
                confirmation.push_back(a);
                cout << '*';
            }
        }
    }
    cout << endl;
    return pass;
}
int repeated_data(string data, int user_counter, user_data user[100])
{
    for (int i = 0; i <= user_counter; i++)
    {
        if (data == user[i].id)
        {
            return 1;
        }
        else if (data == user[i].email)
        {
            return 1;
        }
        else if (data == user[i].number)
        {
            return 1;
        }
        else if (data == user[i].username)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void sign_up(user_data user[100], int &user_counter, int &password_counter)
{
    string username, id, password, email, number;
    database.open("Database.txt", ios::app);
    password_database.open("Password Database.txt", ios::app);
    while (true)
    {
        bool repeated;
        cout << "enter a username:";
        getline(cin, username);
        repeated = repeated_data(username, user_counter, user);
        regex filter_user("^[a-zA-Z_]{5,15}$");
        if (regex_match(username, filter_user) == true && repeated == 0)
        {
            break;
        }
        else
        {
            if (repeated == 1)
            {
                cout << "username is repeated" << endl;
            }
            else
            {
                cout << "Enter a valid username" << endl;
            }
        }
    }
    while (true)
    {
        bool repeated;
        cout << "enter an id:";
        getline(cin, id);
        regex filter_id("^[0-9]{8}$");
        repeated = repeated_data(id, user_counter, user);
        if (regex_match(id, filter_id) == true && repeated == 0)
        {
            break;
        }
        else
        {
            if (repeated == 1)
            {
                cout << "id is repeated" << endl;
            }
            else
            {
                cout << "Enter valid id " << endl;
            }
        }
    }

    while (true)
    {
        bool repeated;
        cout << "enter an email:";
        getline(cin, email);
        regex filter_email("([a-z|A-Z|0-9|#|%|\\+|!|$|\\-||&|\\*]+(.{1}[a-z|A-Z|0-9|#|%|\\+|!|$|\\-||&|\\*]))+@{1}(([a-z|A-Z|0-9])+(\\-{1}[a-z|A-Z|0-9]+)*)+(.com){1}");
        repeated = repeated_data(email, user_counter, user);
        if (regex_match(email, filter_email) == true && repeated == 0)
        {
            break;
        }
        else
        {
            if (repeated == 1)
            {
                cout << "email is repeated" << endl;
            }
            else
            {
                cout << "Enter valid email" << endl;
            }
        }
    }

    while (true)
    {
        bool repeated;
        cout << "enter a mobile number:";
        getline(cin, number);
        regex filter_number("^01[0125][0-9]{8}$");
        repeated = repeated_data(number, user_counter, user);
        if (regex_match(number, filter_number) == true && repeated == 0)
        {
            break;
        }
        else
        {
            if (repeated == 1)
            {
                cout << "mobile number is repeated" << endl;
            }
            else
            {
                cout << "Enter valid mobile number" << endl;
            }
        }
    }
    database << username << '\n';
    user[user_counter].username = username;
    database << id << '\n';
    user[user_counter].id = id;
    database << email << '\n';
    user[user_counter].email = email;
    database << number << '\n';
    user[user_counter].number = number;
    string pass;
    pass = valid_password();
    user[user_counter].password = encrypt(pass);
    password_database << encrypt(pass) << '\n';
    passwords_vector.push_back(encrypt(pass));
    database.close();
    password_database.close();
    user_counter++;
    password_counter++;
}

string encrypt(string password)
{
    for (int i = 0; i < password.length(); i++)
    {
        password[i] = password[i] + 1;
    }
    return password;
}

string decrypt(string password)
{
    for (int i = 0; i < password.length(); i++)
    {
        password[i] = password[i] - 1;
    }
    return password;
}

void load_data(user_data user[100], int &user_counter, int &password_counter)
{
    database.open("Database.txt", ios::in);
    password_database.open("Password Database.txt", ios::in);
    if (!database.fail())
    {
        while (!database.eof())
        {
            getline(database, user[user_counter].username);
            getline(database, user[user_counter].id);
            getline(database, user[user_counter].email);
            getline(database, user[user_counter].number);
            user_counter++;
        }
        database.close();
    }
    else
    {
        database.open("Database.txt", ios::out);
        database.close();
    }
    if (!password_database.fail())
    {
        while (!password_database.eof())
        {
            getline(password_database, user[password_counter].password);
            passwords_vector.push_back(user[password_counter].password);
            password_counter++;
        }
        password_database.close();
    }
    else
    {
        password_database.open("Password Database.txt", ios::out);
        password_database.close();
    }
}

void login(user_data user[100], int user_counter)
{
    int deny_counter = 1, a;
    string id, password;
    bool valid_password = false, valid_id = false;
    // Verify User Credentials.
    while (true)
    {
        cout << "Please Enter Your ID: ";
        cin >> id;
        cin.clear();
        cin.sync();
        for (int i = 0; i <= user_counter; i++)
        {
            if (id == user[i].id)
            {
                valid_id = true;
                cout << "Please Enter Your Password: ";
                // To Cover Password While Entering with *
                while ((a = getch()) != 13)
                {
                    if (a == 8)
                    {
                        password.pop_back();
                        cout << "\b \b";
                    }
                    else
                    {
                        password.push_back(a);
                        cout << '*';
                    }
                }
                if (password == decrypt(user[i].password))
                {
                    valid_password = true;
                    cout << "\nLogin Successful.\n"
                         << "Welcome, " << user[i].username << ".\n";
                    deny_counter++;
                    break;
                }
                else
                {
                    while (true)
                    {
                        cout << "\nWrong Password!, Please Try Again.\n";
                        cout << "Password: ";
                        password.clear(); // To Empty The String From The Wrong Password
                        // To Cover Password While Entering With *
                        while ((a = getch()) != 13)
                        {
                            if (a == 8)
                            {
                                password.pop_back();
                                cout << "\b \b";
                            }
                            else
                            {
                                password.push_back(a);
                                cout << '*';
                            }
                        }
                        if (password == decrypt(user[i].password))
                        {
                            valid_password = true;
                            cout << "\n\nLogin Successful.\n"
                                 << "Welcome, " << user[i].username << ".\n\n";
                            break;
                        }
                        deny_counter++;
                        if (deny_counter == 3)
                        {
                            cout << "\n\nSorry, You Are Denied From Accessing The System.\n";
                            cout << "Please Try Again Later.\n\n";
                            break;
                        }
                    }
                    break; // Break From The For Loop
                }
            }
        }
        if (valid_id && valid_password)
        {
            break;
        }
        else if (valid_id && !valid_password)
        {
            break;
        }
        else if (!valid_id)
        {
            cout << "Wrong ID!\n";
            continue;
        }
    }
}

void change_password(user_data user[100], int user_counter)
{
    string old_password, new_password, id;
    int user_serial, a, deny_counter = 1;
    bool is_valid_password = false, valid_id = false;
    // Verify User Credentials.
    while (true)
    {
        cout << "Please Enter Your ID: ";
        cin >> id;
        cin.clear();
        cin.sync();
        for (int i = 0; i <= user_counter; i++)
        {
            if (id == user[i].id)
            {
                user_serial = i;
                valid_id = true;
                cout << "Please Enter Your Old Password: ";
                // To Cover Password While Entering with *
                while ((a = getch()) != 13)
                {
                    if (a == 8)
                    {
                        old_password.pop_back();
                        cout << "\b \b";
                    }
                    else
                    {
                        old_password.push_back(a);
                        cout << '*';
                    }
                }
                if (old_password == decrypt(user[i].password))
                {
                    is_valid_password = true;
                    cout << "\nEnter A New Password: \n";
                    new_password = valid_password();
                    while (new_password == old_password)
                    {
                        cout << "You Entered The Old Password! \n";
                        cout << "\nEnter A New Password: \n";
                        new_password = valid_password();
                    }
                    update_password(user_serial, new_password, user);
                    break;
                }
                else
                {
                    while (true)
                    {
                        cout << "\nWrong Password!, Please Try Again.\n";
                        cout << "Old Password: ";
                        old_password.clear(); // To Empty The String From The Wrong Password
                        // To Cover Password While Entering With *
                        while ((a = getch()) != 13)
                        {
                            if (a == 8)
                            {
                                old_password.pop_back();
                                cout << "\b \b";
                            }
                            else
                            {
                                old_password.push_back(a);
                                cout << '*';
                            }
                        }
                        if (old_password == decrypt(user[i].password))
                        {
                            is_valid_password = true;
                            cout << "\n\nEnter A New Password: \n";
                            new_password = valid_password();
                            while (new_password == old_password)
                            {
                                cout << "You Entered The Old Password! \n";
                                cout << "\nEnter A New Password: \n";
                                new_password = valid_password();
                            }
                            update_password(user_serial, new_password, user);
                            break;
                        }
                        deny_counter++;
                        if (deny_counter == 3)
                        {
                            cout << "\n\nSorry, You Are Denied From Accessing The System.\n";
                            cout << "Please Try Again Later.\n\n";
                            break;
                        }
                    }
                    break; // Break From The For Loop
                }
            }
        }
        if (valid_id && is_valid_password)
        {
            break;
        }
        else if (valid_id && !is_valid_password)
        {
            break;
        }
        else if (!valid_id)
        {
            cout << "Wrong ID!\n";
            continue;
        }
    }
}

void update_password(int user_serial, string new_password, user_data user[100])
{
    passwords_vector[user_serial] = encrypt(new_password);
    password_database.open("Password Database.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i = 0; i < passwords_vector.size(); i++)
    {
        password_database << passwords_vector[i] << '\n';
    }
    password_database.close();
    user[user_serial].password = encrypt(new_password); // Change The Old Password Stored in the Struct
}