#include "ImapHelper.h"

ImapHelper::ImapHelper(){}

QString ImapHelper::tut1(const QString& email) {
    QString imapServer = "";
    if (email.contains("@hotmail.") || email.contains("@live.") || email.contains("@rickystar.") || email.contains("@outlook.")) {
        imapServer = "outlook.office365.com|imap-mail.outlook.com";
    } else if (email.contains("@yandex.")) {
        imapServer = "imap.yandex.com";
    } else if (email.contains("@gmail.")) {
        imapServer = "imap.gmail.com";
    }
    return imapServer;
}

bool ImapHelper::connectToImapServer(QSslSocket &socket, const QString& server, const QString& email, const QString& password) {
    socket.connectToHostEncrypted(server, 993);
    if (!socket.waitForEncrypted(5000)) {
        qDebug() << "Failed to establish encrypted connection:" << socket.errorString();
        return false;
    }

    QTextStream stream(&socket);
    stream << "a001 LOGIN " << email << " " << password << "\r\n";
    stream.flush();

    if (!socket.waitForReadyRead(5000)) {
        qDebug() << "Login response timeout:" << socket.errorString();
        return false;
    }

    QString response = socket.readAll();
    if (response.contains("a001 OK")) {
        qDebug() << "Login successful.";
        return true;
    } else {
        qDebug() << "Login failed:" << response;
        return false;
    }
}

QSslSocket* ImapHelper::tut2(const QString& email, const QString& password) {
    QSslSocket* socket = nullptr;
    QString imapServers = tut1(email);
    if (!imapServers.isEmpty()) {
        QStringList serverList = imapServers.split('|');
        for (int i = 0; i < 10; ++i) {
            bool retry = false;
            for (const QString& server : serverList) {
                socket = new QSslSocket();
                if (connectToImapServer(*socket, server, email, password)) {
                    return socket;
                }
                delete socket;
                socket = nullptr;
                // Handle specific connection errors to determine retry
                retry = true; // Simulate retry logic based on errors
            }
            if (!retry) {
                break;
            }
        }
    }
    return socket;
}

void ImapHelper::tut3(QSslSocket* socket) {
    if (socket) {
        if (socket->isOpen()) {
            QTextStream stream(socket);
            stream << "a002 LOGOUT\r\n";
            stream.flush();
            socket->waitForReadyRead(5000);
            socket->close();
        }
        delete socket;
    }
}

bool ImapHelper::CheckConnectImap(const QString& email, const QString& password) {
    QSslSocket* socket = tut2(email, password);
    bool isConnected = (socket != nullptr);
    tut3(socket);
    return isConnected;
}

