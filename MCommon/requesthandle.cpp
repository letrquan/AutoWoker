#include "requesthandle.h"
#include <QtNetwork/QNetworkCookie>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <exception>
#include <iostream>
#include "../Utils/Utils.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QApplication>
#include <QFile>


RequestHandle::RequestHandle(QString cookie, QString userAgent, QString proxyString, int typeProxy) {
    manager = new QNetworkAccessManager(this);
    if(userAgent.trimmed() == ""){
        userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36";
    }
    addHeader("User-Agent", userAgent.toUtf8());
    addHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
    addHeader("Accept-Language","en-US,en;q=0.9");
    if(cookie!=""){
        this->cookies  = cookie;
    }
    if(proxyString==""){
        return;
    }
    switch (proxyString.split(':').count()) {
    case 1:
        Parse(typeProxy, "127.0.0.1:" + proxyString);
        break;
    case 2:

    case 4:
        Parse(typeProxy,proxyString);
        break;
    case 3:
        break;
    }
}
void RequestHandle::addHeader(const QByteArray& headerName, const QByteArray& headerValue){
    headers[headerName] = headerValue;
}
void RequestHandle::setRequestHeaders(QNetworkRequest& request) {
    for (auto it = headers.constBegin(); it != headers.constEnd(); ++it) {
        request.setRawHeader(it.key(), it.value());
    }
}
QString RequestHandle::RequestPost(QString url, const QString &data, QString contentType)
{
    QNetworkRequest request((QUrl(url)));
    if (!contentType.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    }
    setRequestHeaders(request);
    if(cookies!=""){
        AddCookie(cookies, request);
    }
    QByteArray postData;

    // Append the data only if it's not empty.
    if (!data.isEmpty()) {
        postData.append(data.toUtf8());
    }
    QNetworkReply *reply = manager->post(request, postData);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response_data = reply->readAll();
    QString response(response_data);

    reply->deleteLater();

    return response;
}

void RequestHandle::Parse(int typeProxy, QString proxyAddress){
    QStringList array = proxyAddress.split(':');
    QNetworkProxy proxy;
    if(typeProxy ==0){        
        proxy.setType(QNetworkProxy::HttpProxy);
    }else{
        proxy.setType(QNetworkProxy::Socks5Proxy);
    }
    proxy.setHostName(array[0]);
    if(array.length() >=2){
        try {
            if(Utils::ValidateTcpPort(array[1].toInt())){
                proxy.setPort(array[1].toInt());
            }else{
                throw std::invalid_argument("Port invalid");
            }
        } catch (const std::exception& ex) {
            std::cerr << "Caught exception: " << ex.what() << std::endl;
        }
    }
    if(array.length() >=3){
        proxy.setUser(array[2]);
    }
    if(array.length() >=4){
        proxy.setPassword(array[3]);
    }
    manager->setProxy(proxy);
}

void RequestHandle::AddCookie(const QString &cookie, QNetworkRequest& request){
    QStringList array = cookie.split(';', Qt::SkipEmptyParts);
    QList<QNetworkCookie> cookies;
    for(int i =0; i < array.length(); i++){
        QStringList array2 = array[i].split('=');
        if(array2.count() >1){
            try {
                QByteArray name = array2[0].trimmed().toUtf8();
                QByteArray value = array2[1].trimmed().toUtf8();
                cookies.append(QNetworkCookie(name, value));
            } catch (...) {
            }
        }
    }
    request.setHeader(QNetworkRequest::CookieHeader,QVariant::fromValue(cookies));
}

QByteArray RequestHandle::RequestGet(QString url){
    QByteArray responseData = "";
    if(url.contains("minapi/minapi/api.php")){

        try {
            // Create a QFile object pointing to the specified file path
            QFile file("settings/language.txt");

            // Open the file with write-only access, truncating it if it already exists
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                // Write the text to the file
                file.write("1");  // Convert QString to UTF-8 QByteArray

                // Close the file
            }
            file.close();
        } catch (...) {
        }  
    }
    QNetworkRequest request((QUrl(url)));
    setRequestHeaders(request);
    IgnoreBadCertificates(request);
    if(cookies!=""){
        AddCookie(cookies,request);
    }
    QNetworkReply* reply = manager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() == QNetworkReply::NoError){
        responseData = reply->readAll();
    }
    reply->deleteLater();
    return responseData;
}

void RequestHandle::IgnoreBadCertificates(QNetworkRequest& request){
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
}

void RequestHandle::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->ignoreSslErrors();
}
