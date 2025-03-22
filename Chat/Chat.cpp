#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale> 

using namespace std;

// Класс для хранения данных пользователя
class User {
public:
    string login;
    string password;
    string name;

    User() : login(""), password(""), name("") {}

    User(string l, string p, string n)
        : login(l), password(p), name(n) {}
};

// Класс для управления чатом
class Chat {
private:
    vector<User> users;
    vector<string> messageSenders;
    vector<string> messageRecipients;
    vector<string> messageTexts;

    string currentUserLogin = "";

    int findUserByLogin(const string& login) {
        auto it = find_if(users.begin(), users.end(), [&login](const User& user) {
            return user.login == login;
            });
        if (it != users.end()) {
            return distance(users.begin(), it);
        }
        return -1;
    }

public:
    // Регистрация нового пользователя
    void registerUser() {
        string login, password, name;
        cout << "Регистрация нового пользователя\n";
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;
        cout << "Введите имя: ";
        cin >> name;

        if (findUserByLogin(login) == -1) {
            users.emplace_back(login, password, name);
            cout << "Пользователь зарегистрирован!\n";
        }
        else {
            cout << "Пользователь с таким логином уже существует.\n";
        }
    }

    // Вход в систему
    void login() {
        string login, password;
        cout << "Вход в чат\n";
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;

        int userIndex = findUserByLogin(login);
        if (userIndex != -1 && users[userIndex].password == password) {
            currentUserLogin = login;
            cout << "Добро пожаловать, " << users[userIndex].name << "!\n";


            cout << "Ваши сообщения:\n";
            for (size_t i = 0; i < messageTexts.size(); i++) {
                if (messageRecipients[i] == currentUserLogin) {
                    cout << "От: " << messageSenders[i] << " | Сообщение: " << messageTexts[i] << "\n";
                }
            }
        }
        else {
            cout << "Неверный логин или пароль.\n";
        }
    }

    // Выход из системы
    void logout() {
        if (currentUserLogin != "") {
            cout << "Вы вышли из аккаунта.\n";
            currentUserLogin = "";
        }
        else {
            cout << "Вы не вошли в систему.\n";
        }
    }

    // Отправка сообщения конкретному пользователю
    void sendMessageToUser() {
        if (currentUserLogin == "") {
            cout << "Сначала войдите в систему.\n";
            return;
        }

        string recipientLogin, message;
        cout << "Введите логин получателя: ";
        cin >> recipientLogin;
        cout << "Введите сообщение: ";
        cin.ignore();
        getline(cin, message);

        if (findUserByLogin(recipientLogin) != -1) {
            messageSenders.push_back(currentUserLogin);
            messageRecipients.push_back(recipientLogin);
            messageTexts.push_back(message);
            cout << "Сообщение отправлено.\n";
        }
        else {
            cout << "Пользователь с таким логином не найден.\n";
        }
    }

    // Отправка сообщения всем пользователям
    void broadcastMessage() {
        if (currentUserLogin == "") {
            cout << "Сначала войдите в систему.\n";
            return;
        }

        string message;
        cout << "Введите сообщение для всех: ";
        cin.ignore();
        getline(cin, message);

        for (const auto& user : users) {
            if (user.login != currentUserLogin) {
                messageSenders.push_back(currentUserLogin);
                messageRecipients.push_back(user.login);
                messageTexts.push_back(message);
            }
        }
        cout << "Сообщение отправлено всем пользователям.\n";
    }

    // Главное меню
    void showMenu() {
        int choice;
        do {
            cout << "\nМеню:\n";
            if (currentUserLogin == "") {
                cout << "1. Регистрация\n";
                cout << "2. Вход\n";
            }
            else {
                cout << "1. Отправить сообщение пользователю\n";
                cout << "2. Отправить сообщение всем\n";
                cout << "3. Выйти из аккаунта\n";
            }
            cout << "0. Выход\n";
            cout << "Выберите действие: ";
            cin >> choice;

            if (currentUserLogin == "") {
                switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    login();
                    break;
                case 0:
                    cout << "Выход из программы.\n";
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            }
            else {
                switch (choice) {
                case 1:
                    sendMessageToUser();
                    break;
                case 2:
                    broadcastMessage();
                    break;
                case 3:
                    logout();
                    break;
                case 0:
                    cout << "Выход из программы.\n";
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            }
        } while (choice != 0);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Chat chat;
    chat.showMenu();
    return 0;
}