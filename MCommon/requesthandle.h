#ifndef REQUESTHANDLE_H
#define REQUESTHANDLE_H
#include <QNetworkProxy>
#include <QString>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkAccessManager>
class RequestHandle: public QObject
{
    Q_OBJECT
public:
    RequestHandle(QString cookie, QString userAgent, QString proxy, int typeProxy);  
    QString RequestPost(QString url, const QString &data, QString contentType = "application/x-www-form-urlencoded");
    void AddCookie(const QString &cookie, QNetworkRequest& request);
    void Parse(int typeProxy, QString proxyAddress);
    QByteArray RequestGet(QString url);
    void IgnoreBadCertificates(QNetworkRequest& request);
    void addHeader(const QByteArray& headerName, const QByteArray& headerValue);
    QString GetUrl();
    void setConnectionTimeout(int milisecond);
private slots:
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
private:
    QNetworkProxy proxy;
    QNetworkAccessManager *manager;
    void setRequestHeaders(QNetworkRequest& request);
    QNetworkCookieJar* cookieJar;
    QMap<QByteArray, QByteArray> headers;
    QString cookies="";
    QString url= "";
protected:
    int _connectTimeout = 60000;
};

#endif // REQUESTHANDLE_H
