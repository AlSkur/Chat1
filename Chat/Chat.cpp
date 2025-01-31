#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100; // ���ᨬ��쭮� ������⢮ ���짮��⥫��
const int MAX_MESSAGES = 1000; // ���ᨬ��쭮� ������⢮ ᮮ�饭��

// ����� ��� �࠭���� ������ ���짮��⥫�
class User {
public:
    string login;
    string password;
    string name;

    User() : login(""), password(""), name("") {}

    User(string l, string p, string n)
        : login(l), password(p), name(n) {}
};

// ����� ��� �ࠢ����� �⮬
class Chat {
private:
    User users[MAX_USERS]; // ���ᨢ ���짮��⥫��
    int userCount = 0; // ����饥 ������⢮ ���짮��⥫��

    // ���ᨢ� ��� �࠭���� ᮮ�饭��
    string messageSenders[MAX_MESSAGES];
    string messageRecipients[MAX_MESSAGES];
    string messageTexts[MAX_MESSAGES];
    int messageCount = 0; // ����饥 ������⢮ ᮮ�饭��

    // ����騩 ���짮��⥫�
    string currentUserLogin = "";

    // ���� ���짮��⥫� �� ������
    int findUserByLogin(string login) {
        for (int i = 0; i < userCount; i++) {
            if (users[i].login == login) {
                return i; // �����頥� ������ ���짮��⥫�
            }
        }
        return -1; // ���짮��⥫� �� ������
    }

public:
    // ��������� ������ ���짮��⥫�
    void registerUser() {
        if (userCount >= MAX_USERS) {
            cout << "���⨣��� ���ᨬ��쭮� ������⢮ ���짮��⥫��.\n";
            return;
        }

        string login, password, name;
        cout << "��������� ������ ���짮��⥫�\n";
        cout << "������ �����: ";
        cin >> login;
        cout << "������ ��஫�: ";
        cin >> password;
        cout << "������ ���: ";
        cin >> name;

        if (findUserByLogin(login) == -1) {
            users[userCount] = User(login, password, name);
            userCount++;
            cout << "���짮��⥫� ��ॣ����஢��!\n";
        }
        else {
            cout << "���짮��⥫� � ⠪�� ������� 㦥 �������.\n";
        }
    }

    // �室 � ��⥬�
    void login() {
        string login, password;
        cout << "�室 � ��\n";
        cout << "������ �����: ";
        cin >> login;
        cout << "������ ��஫�: ";
        cin >> password;

        int userIndex = findUserByLogin(login);
        if (userIndex != -1 && users[userIndex].password == password) {
            currentUserLogin = login;
            cout << "���� ����������, " << users[userIndex].name << "!\n";

            // �����뢠�� ᮮ�饭�� ��� ⥪�饣� ���짮��⥫�
            cout << "��� ᮮ�饭��:\n";
            for (int i = 0; i < messageCount; i++) {
                if (messageRecipients[i] == currentUserLogin) {
                    cout << "��: " << messageSenders[i] << " | ����饭��: " << messageTexts[i] << "\n";
                }
            }
        }
        else {
            cout << "������ ����� ��� ��஫�.\n";
        }
    }

    // ��室 �� ��⥬�
    void logout() {
        if (currentUserLogin != "") {
            cout << "�� ��諨 �� ������.\n";
            currentUserLogin = "";
        }
        else {
            cout << "�� �� ��諨 � ��⥬�.\n";
        }
    }

    // ��ࠢ�� ᮮ�饭�� �����⭮�� ���짮��⥫�
    void sendMessageToUser() {
        if (currentUserLogin == "") {
            cout << "���砫� ������ � ��⥬�.\n";
            return;
        }

        string recipientLogin, message;
        cout << "������ ����� �����⥫�: ";
        cin >> recipientLogin;
        cout << "������ ᮮ�饭��: ";
        cin.ignore(); // ������㥬 �।��騩 ����
        getline(cin, message);

        if (findUserByLogin(recipientLogin) != -1) {
            messageSenders[messageCount] = currentUserLogin;
            messageRecipients[messageCount] = recipientLogin;
            messageTexts[messageCount] = message;
            messageCount++;
            cout << "����饭�� ��ࠢ����.\n";
        }
        else {
            cout << "���짮��⥫� � ⠪�� ������� �� ������.\n";
        }
    }

    // ��ࠢ�� ᮮ�饭�� �ᥬ ���짮��⥫�
    void broadcastMessage() {
        if (currentUserLogin == "") {
            cout << "���砫� ������ � ��⥬�.\n";
            return;
        }

        string message;
        cout << "������ ᮮ�饭�� ��� ���: ";
        cin.ignore(); // ������㥬 �।��騩 ����
        getline(cin, message);

        for (int i = 0; i < userCount; i++) {
            if (users[i].login != currentUserLogin) {
                messageSenders[messageCount] = currentUserLogin;
                messageRecipients[messageCount] = users[i].login;
                messageTexts[messageCount] = message;
                messageCount++;
            }
        }
        cout << "����饭�� ��ࠢ���� �ᥬ ���짮��⥫�.\n";
    }

    // ������� ����
    void showMenu() {
        int choice;
        do {
            cout << "\n����:\n";
            if (currentUserLogin == "") {
                cout << "1. ���������\n";
                cout << "2. �室\n";
            }
            else {
                cout << "1. ��ࠢ��� ᮮ�饭�� ���짮��⥫�\n";
                cout << "2. ��ࠢ��� ᮮ�饭�� �ᥬ\n";
                cout << "3. ��� �� ������\n";
            }
            cout << "0. ��室\n";
            cout << "�롥�� ����⢨�: ";
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
                    cout << "��室 �� �ணࠬ��.\n";
                    break;
                default:
                    cout << "������ �롮�. ���஡�� ᭮��.\n";
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
                    cout << "��室 �� �ணࠬ��.\n";
                    break;
                default:
                    cout << "������ �롮�. ���஡�� ᭮��.\n";
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