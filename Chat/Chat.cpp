#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100; // Максимальное количество пользователей
const int MAX_MESSAGES = 1000; // Максимальное количество сообщений

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
    User users[MAX_USERS]; // Массив пользователей
    int userCount = 0; // Текущее количество пользователей

    // Массивы для хранения сообщений
    string messageSenders[MAX_MESSAGES];
    string messageRecipients[MAX_MESSAGES];
    string messageTexts[MAX_MESSAGES];
    int messageCount = 0; // Текущее количество сообщений

    // Текущий пользователь
    string currentUserLogin = "";

    // Поиск пользователя по логину
    int findUserByLogin(string login) {
        for (int i = 0; i < userCount; i++) {
            if (users[i].login == login) {
                return i; // Возвращаем индекс пользователя
            }
        }
        return -1; // Пользователь не найден
    }

public:
    // Регистрация нового пользователя
    void registerUser() {
        if (userCount >= MAX_USERS) {
            cout << "Достигнуто максимальное количество пользователей.\n";
            return;
        }

        string login, password, name;
        cout << "Регистрация нового пользователя\n";
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;
        cout << "Введите имя: ";
        cin >> name;

        if (findUserByLogin(login) == -1) {
            users[userCount] = User(login, password, name);
            userCount++;
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

            // Показываем сообщения для текущего пользователя
            cout << "Ваши сообщения:\n";
            for (int i = 0; i < messageCount; i++) {
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
        cin.ignore(); // Игнорируем предыдущий ввод
        getline(cin, message);

        if (findUserByLogin(recipientLogin) != -1) {
            messageSenders[messageCount] = currentUserLogin;
            messageRecipients[messageCount] = recipientLogin;
            messageTexts[messageCount] = message;
            messageCount++;
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
        cin.ignore(); // Игнорируем предыдущий ввод
        getline(cin, message);

        for (int i = 0; i < userCount; i++) {
            if (users[i].login != currentUserLogin) {
                messageSenders[messageCount] = currentUserLogin;
                messageRecipients[messageCount] = users[i].login;
                messageTexts[messageCount] = message;
                messageCount++;
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
    Chat chat;
    chat.showMenu();
    return 0;
}