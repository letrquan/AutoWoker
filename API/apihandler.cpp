// apihandler.cpp
#include "apihandler.h"
#include "qeventloop.h"
#include "qthread.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>
#include "../Utils/Utils.h"
ApiHandler::ApiHandler(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_apiProcess(new QProcess(this))
{
}

ApiHandler::~ApiHandler()
{
    stopApiProcess();
}

void ApiHandler::startApiProcess()
{
    QString path = Utils::getBuildFolderPath() + "/autochrome.py";
    m_apiProcess->start("python", QStringList() << path);
    if(!isApiRunningExternally()){
        if (m_apiProcess->waitForStarted())
        {
            // Wait a bit for the Flask app to initialize
            QThread::msleep(3000);
            emit apiStarted();
        }
        else
        {
            emit errorOccurred("Failed to start Python API");
        }
    }
}

void ApiHandler::stopApiProcess()
{
    if (m_apiProcess->state() == QProcess::Running)
    {
        m_apiProcess->terminate();
        m_apiProcess->waitForFinished();
        emit apiStopped();
    }
}

QString ApiHandler::createInstance(int indexChrome, bool disableImage, const QString &userAgent, const QString &profilePath, const QPoint &size, const QPoint &position, int timeWaitForSearchingElement, int timeWaitForLoadingPage, const QString &proxy, int typeProxy, bool disableSound, const QString &appUrl, bool isUsePortable, const QString &pathToPortableZip)
{
    QString url ="/create_instance";
    QJsonObject jsonObject;
    jsonObject["indexChrome"] = indexChrome;
    jsonObject["disableImage"] = disableImage;
    jsonObject["userAgent"] = userAgent;
    jsonObject["profilePath"] = profilePath;
    jsonObject["size"] = QString("%1x%2").arg(size.x()).arg(size.y());
    jsonObject["position"] = QString("%1,%2").arg(position.x()).arg(position.y());
    jsonObject["timeWaitForSearchingElement"] = timeWaitForSearchingElement;
    jsonObject["timeWaitForLoadingPage"] = timeWaitForLoadingPage;
    jsonObject["proxy"] = proxy;
    jsonObject["typeProxy"] = typeProxy;
    jsonObject["disableSound"] = disableSound;
    jsonObject["app"] = appUrl;
    jsonObject["isUsePortable"] = isUsePortable;
    jsonObject["pathToPortableZip"] = pathToPortableZip;

    auto response =  sendRequest(url, jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}

QString ApiHandler::openBrowser(int instanceId)
{
    auto response = sendRequest(QString("/open/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}

QString ApiHandler::gotoUrl(int instanceId, const QString &url)
{
    QJsonObject jsonObject;
    jsonObject["url"] = url;
    auto response = sendRequest(QString("/goto_url/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}

QString ApiHandler::executeScript(int instanceId, const QString &script)
{
    QJsonObject jsonObject;
    jsonObject["script"] = script;
    auto response = sendRequest(QString("/execute_script/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}

void ApiHandler::checkChromeClose(int instanceId)
{
    sendRequest(QString("/check_chrome_close/%1").arg(instanceId));
}

QString ApiHandler::delayTime(int instanceId, int timeDelay)
{
    QJsonObject jsonObject;
    jsonObject["time_delay"] = timeDelay;
    auto response = sendRequest(QString("/delay_time/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}

QJsonObject ApiHandler::sendRequest(const QString &endpoint, const QJsonObject &jsonObject)
{
    QUrl url(QString("http://127.0.0.1:5000%1").arg(endpoint));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(jsonObject).toJson());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonObject responseJson;
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        responseJson = jsonResponse.object();
    }
    else
    {
        responseJson["error"] = reply->errorString();
    }

    reply->deleteLater();
    return responseJson;
}

QJsonObject ApiHandler::sendRequest(const QString &endpoint)
{
    QUrl url(QString("http://127.0.0.1:5000%1").arg(endpoint));
    QNetworkReply *reply = m_networkManager->get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonObject responseJson;
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        responseJson = jsonResponse.object();
    }
    else
    {
        responseJson["error"] = reply->errorString();
    }

    reply->deleteLater();
    return responseJson;
}


bool ApiHandler::isApiRunningExternally() const
{
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://127.0.0.1:5000/health")));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        reply->deleteLater();
        return jsonObject["status"].toString() == "OK";
    }

    reply->deleteLater();
    return false;
}

QString ApiHandler::GetPageSource(int instanceId){
    auto response = sendRequest(QString("/get_page_source/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["page_source"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}


QString ApiHandler::close(int instanceId){
    auto response = sendRequest(QString("/check_chrome_close/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["is_closed"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    else
    {
        return "Unexpected response format";
    }
}
