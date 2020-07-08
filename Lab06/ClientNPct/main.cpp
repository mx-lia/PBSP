#include "windows.h"
#include <string>
#include "iostream"

#define STOP_WORD "~"


using namespace std;

string GetErrorPipe(int code) {
    string msgText;

    switch (code) {
        case WSAEINTR:
            msgText = "Работа функции прервана\n";
            break;
        case WSAEACCES:
            msgText = "Разрешение отвергнуто\n";
            break;
        case WSAEFAULT:
            msgText = "Ошибочный адрес\n";
            break;
        case WSAEINVAL:
            msgText = "Ошибка в аргументе\n";
            break;
        case WSAEMFILE:
            msgText = "Слишком много файлов открыто\n";
            break;
        case WSAEWOULDBLOCK:
            msgText = "Ресурс временно недоступен\n";
            break;
        case WSAEINPROGRESS:
            msgText = "Операция в процессе развития\n";
            break;
        case WSAEALREADY:
            msgText = "Операция уже выполняется\n";
            break;
        case WSAENOTSOCK:
            msgText = "Сокет задан неправильно\n";
            break;
        case WSAEDESTADDRREQ:
            msgText = "Требуется адрес расположения\n";
            break;
        case WSAEMSGSIZE:
            msgText = "Сообщение слишком длинное\n";
            break;
        case WSAEPROTOTYPE:
            msgText = "Неправильный тип протокола для сокета\n";
            break;
        case WSAENOPROTOOPT:
            msgText = "Ошибка в опции протокола\n";
            break;
        case WSAEPROTONOSUPPORT:
            msgText = "Протокол не поддерживается\n";
            break;
        case WSAESOCKTNOSUPPORT:
            msgText = "Тип сокета не поддерживается\n";
            break;
        case WSAEOPNOTSUPP:
            msgText = "Операция не поддерживается\n";
            break;
        case WSAEPFNOSUPPORT:
            msgText = "Тип протоколов не поддерживается\n";
            break;
        case WSAEAFNOSUPPORT:
            msgText = "Тип адресов не поддерживается протоколом\n";
            break;
        case WSAEADDRINUSE:
            msgText = "Адрес уже используется\n";
            break;
        case WSAEADDRNOTAVAIL:
            msgText = "Запрошенный адрес не может быть использован\n";
            break;
        case WSAENETDOWN:
            msgText = "Сеть отключена\n";
            break;
        case WSAENETUNREACH:
            msgText = "Сеть не достижима\n";
            break;
        case WSAENETRESET:
            msgText = "Сеть разорвала соединение\n";
            break;
        case WSAECONNABORTED:
            msgText = "Программный отказ связи\n";
            break;
        case WSAECONNRESET:
            msgText = "Связь восстановлена\n";
            break;
        case WSAENOBUFS:
            msgText = "Не хватает памяти для буферов\n";
            break;
        case WSAEISCONN:
            msgText = "Сокет уже подключен\n";
            break;
        case WSAENOTCONN:
            msgText = "Сокет не подключен\n";
            break;
        case WSAESHUTDOWN:
            msgText = "Нельзя выполнить send: сокет завершил работу\n";
            break;
        case WSAETIMEDOUT:
            msgText = "Закончился отведенный интервал  времени\n";
            break;
        case WSAECONNREFUSED:
            msgText = "Соединение отклонено\n";
            break;
        case WSAEHOSTDOWN:
            msgText = "Хост в неработоспособном состоянии\n";
            break;
        case WSAEHOSTUNREACH:
            msgText = "Нет маршрута для хоста\n";
            break;
        case WSAEPROCLIM:
            msgText = "Слишком много процессов\n";
            break;
        case WSASYSNOTREADY:
            msgText = "Сеть не доступна\n";
            break;
        case WSAVERNOTSUPPORTED:
            msgText = "Данная версия недоступна\n";
            break;
        case WSANOTINITIALISED:
            msgText = "Не выполнена инициализация WS2_32.DLL\n";
            break;
        case WSAEDISCON:
            msgText = "Выполняется отключение\n";
            break;
        case WSATYPE_NOT_FOUND:
            msgText = "Класс не найден\n";
            break;
        case WSAHOST_NOT_FOUND:
            msgText = "Хост не найден\n";
            break;
        case WSATRY_AGAIN:
            msgText = "Неавторизированный хост не найден\n";
            break;
        case WSANO_RECOVERY:
            msgText = "Неопределенная ошибка\n";
            break;
        case WSANO_DATA:
            msgText = "Нет записи запрошенного типа\n";
            break;
        case WSAEINVALIDPROCTABLE:
            msgText = "Ошибочный сервис\n";
            break;
        case WSAEINVALIDPROVIDER:
            msgText = "Ошибка в версии сервиса\n";
            break;
        case WSAEPROVIDERFAILEDINIT:
            msgText = "Невозможно инициализировать сервис\n";
            break;
        case WSASYSCALLFAILURE:
            msgText = "Аварийное завершение системного вызова\n";
            break;
        default:
            msgText = "Error " + to_string(code) + " \n";
            break;
    };

    return msgText;
};

string SetErrorPipe(string msgText, int code) {
    return msgText + GetErrorPipe(code);
};

int main() {
    setlocale(LC_CTYPE, "Russian");

    cout << "ClientNPct" << endl << endl;

    try {
        char rbuf[50];
        char wbuf[50] = "Hello from ClientNPct";
        DWORD rb = sizeof(rbuf);
        DWORD wb = sizeof(wbuf);


        char buf[sizeof(wbuf)];
        strcpy(buf, wbuf);
        wb = sizeof(wbuf);

        int numberOfMessages;
        cout << "Please enter number of message to send" << endl;
        cin >> numberOfMessages;

        for (int i = 0; i < numberOfMessages; i++) {

            if (!CallNamedPipe(R"(\\.\pipe\Tube)", buf, wb, rbuf, rb, &rb, 20))
                throw SetErrorPipe("CallNamedPipe: ", GetLastError());

            cout << rbuf << endl;
        }
    }
    catch (char const *e) {
        cout << e << endl;
    }
    catch (string e) {
        cout << e << endl;
    }
    catch (...) {
        cout << "Error" << endl;
    }

    return 0;
}