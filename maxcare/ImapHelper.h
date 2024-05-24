#ifndef IMAPHELPER_H
#define IMAPHELPER_H
#include <QString>
#include <QLibrary>
#include <QSslSocket>

class ImapHelper {
public:
    ImapHelper();
    static QString tut1(const QString& email);
    static QSslSocket* tut2(const QString& email, const QString& password);
    static void tut3(QSslSocket* socket);
    static bool CheckConnectImap(const QString& email, const QString& password);

private:
    static bool connectToImapServer(QSslSocket &socket, const QString& server, const QString& email, const QString& password);
};

#endif // IMAPHELPER_H
