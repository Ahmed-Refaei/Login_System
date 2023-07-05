#ifndef Registration_H
#define Registration_H

using namespace std;

struct user_data
{
    string username;
    string password;
    string id;
    string email;
    string number;
};

fstream database;
fstream password_database;
vector<string> passwords_vector;


void sign_up(user_data user[100], int &user_counter, int &password_counter);
string valid_password();
void valid_id();
string encrypt(string password);
string decrypt(string password);
void load_data(user_data user[100], int &user_counter, int &password_counter);
void login(user_data user[100], int user_counter);
void change_password(user_data user[100], int user_counter);
void update_password(int user_serial, string new_password, user_data user[100]);

#endif
