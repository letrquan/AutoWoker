// apihandler.cpp
#include "apihandler.h"
#include "qeventloop.h"
#include "qjsonarray.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>
#include <QCoreApplication>
#include <QFile>
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
    if (!isApiRunningExternally()) {
        QString scriptPath = QCoreApplication::applicationDirPath() + "/autochrome.py";
        QString pythonPath = "C:/Users/letrq/AppData/Local/Programs/Python/Python312/python.exe";

        QFile scriptFile(scriptPath);
        if (!scriptFile.exists()) {
            qDebug() << "Script file does not exist:" << scriptPath;
            return;
        }

        // Prepare the process environment
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.remove("PYTHONHOME");
        env.remove("PYTHONPATH");

        m_apiProcess->setProcessEnvironment(env);

        // Debugging output to verify paths and environment
        qDebug() << "Starting script at path:" << scriptPath;
        qDebug() << "Using Python executable at path:" << pythonPath;

        m_apiProcess->start(pythonPath, QStringList() << scriptPath);

        if (!m_apiProcess->waitForStarted()) {
            qDebug() << "Failed to start the process";
            qDebug() << "Error:" << m_apiProcess->errorString();
            return;
        }

        // Optional: Set a timeout for the process to finish
        if (!m_apiProcess->waitForFinished(30000)) { // Wait for 30 seconds
            qDebug() << "Process timed out";
            m_apiProcess->kill(); // Kill the process if it times out
            return;
        }

        // Read the output
        QString output(m_apiProcess->readAllStandardOutput());
        QString errors(m_apiProcess->readAllStandardError());

        // Print the output and errors
        qDebug() << "Output:" << output;
        qDebug() << "Errors:" << errors;

        if (!errors.isEmpty()) {
            qDebug() << "Errors encountered while running the script:" << errors;
        }
    }
}


void ApiHandler::stopApiProcess()
{
    if (m_apiProcess->state() == QProcess::Running)
    {
        m_apiProcess->terminate();
        m_apiProcess->waitForFinished();
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
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
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
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
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
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
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
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::checkChromeClose(int instanceId)
{
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
    return "Unexpected response format";
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
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
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
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    responseJson = jsonResponse.object();

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
        responseJson["status"] = "error";
        responseJson["message"] = reply->errorString();
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
    return "Unexpected response format";
}

QString ApiHandler::GetUrl(int instanceId){
    auto response = sendRequest(QString("/get_url/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["url"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
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
    return "Unexpected response format";
}


QString ApiHandler::checkExistElement(int instanceId, QString cssSelectorsOrXpath, double timeWait_Second){
    QJsonObject jsonObject;
    jsonObject["selector"] = cssSelectorsOrXpath;
    jsonObject["time_wait"] = timeWait_Second;
    auto response = sendRequest(QString("/check_exist_element/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["is_exist"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::checkExistElements(int instanceId, double timeOut, const QStringList & lstCssSelectors){
    QJsonObject jsonObject;
    jsonObject["selectors"] = QJsonArray::fromStringList(lstCssSelectors);
    jsonObject["time_out"] = timeOut;
    auto response = sendRequest(QString("/check_exist_elements/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["is_exist"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::GetAttributeValue(int instanceId, QString cssSelectorsOrXpath, QString attributeName){
    QJsonObject jsonObject;
    jsonObject["selector"] = cssSelectorsOrXpath;
    jsonObject["attribute_name"] = attributeName;
    auto response = sendRequest(QString("/get_attribute_value/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["value"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::findAndClick(int instanceId, double timeWait_Second, int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QJsonObject jsonObject;
    jsonObject["time_wait_seconds"] = timeWait_Second;
    jsonObject["type_attribute"] = typeAttribute;
    jsonObject["attribute_value"] = attributeValue;
    jsonObject["index"] = index;
    jsonObject["sub_type_attribute"] = subTypeAttribute;
    jsonObject["sub_attribute_value"] = subAttributeValue;
    jsonObject["sub_index"] = subIndex;
    auto response = sendRequest(QString("/find_and_click/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::sendKeysWithSpeed(int instanceId, int tocDo, int typeAttribute, QString attributeValue, QString content, double timeDelay_Second, bool isClick, double timeDelayAfterClick){
    QJsonObject jsonObject;
    jsonObject["toc_do"] = tocDo;
    jsonObject["type_attribute"] = typeAttribute;
    jsonObject["attribute_value"] = attributeValue;
    jsonObject["content"] = content;
    jsonObject["time_delay_second"] = timeDelay_Second;
    jsonObject["is_click"] = isClick;
    jsonObject["time_delay_after_click"] = timeDelayAfterClick;
    auto response = sendRequest(QString("/send_keys_with_speed/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::click(int instanceId,int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex, int times){
    QJsonObject jsonObject;
    jsonObject["typeAttribute"] = typeAttribute;
    jsonObject["attributeValue"] = attributeValue;
    jsonObject["index"] = index;
    jsonObject["subTypeAttribute"] = subTypeAttribute;
    jsonObject["subAttributeValue"] = subAttributeValue;
    jsonObject["subIndex"] = subIndex;
    jsonObject["times"] = times;
    auto response = sendRequest(QString("/click/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::sendEnter(int instanceId,int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QJsonObject jsonObject;
    jsonObject["type_attribute"] = typeAttribute;
    jsonObject["attribute_value"] = attributeValue;
    jsonObject["index"] = index;
    jsonObject["sub_type_attribute"] = subTypeAttribute;
    jsonObject["sub_attribute_value"] = subAttributeValue;
    jsonObject["sub_index"] = subIndex;
    auto response = sendRequest(QString("/send_enter/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::sendKeys(int instanceId, int typeAttribute, QString attributeValue, QString content, bool isClick, double timeDelayAfterClick){
    QJsonObject jsonObject;
    jsonObject["type_attribute"] = typeAttribute;
    jsonObject["attribute_value"] = attributeValue;
    jsonObject["content"] = content;
    jsonObject["is_click"] = isClick;
    jsonObject["time_delay_after_click"] = timeDelayAfterClick;
    auto response = sendRequest(QString("/send_keys_without_time_delay_second/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::clickJs(int instanceId, int timeOut, const QStringList &lstCssSelectors){
    QJsonObject jsonObject;
    jsonObject["css_selectors"] = QJsonArray::fromStringList(lstCssSelectors);
    jsonObject["timeout"] = timeOut;
    auto response = sendRequest(QString("/click_js/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::clickJs(int instanceId, QString cssSelectorsOrXpath){
    QJsonObject jsonObject;
    jsonObject["selector"] = cssSelectorsOrXpath;
    auto response = sendRequest(QString("/click_js_single/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::CountElement(int instanceId, QString querySelector){
    QJsonObject jsonObject;
    jsonObject["selector"] = querySelector;
    auto response = sendRequest(QString("/count_element/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::ClickWithAction(int instanceId, int typeAttribute, QString attributeValue, int index, int subTypeAttribute, QString subAttributeValue, int subIndex){
    QJsonObject jsonObject;
    jsonObject["type_attribute"] = typeAttribute;
    jsonObject["attribute_value"] = attributeValue;
    jsonObject["index"] = index;
    jsonObject["sub_type_attribute"] = subTypeAttribute;
    jsonObject["sub_attribute_value"] = subAttributeValue;
    jsonObject["sub_index"] = subIndex;
    auto response = sendRequest(QString("/click_with_action/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::sendEnter(int instanceId, QString cssSelectorsOrXpath){
    QJsonObject jsonObject;
    jsonObject["selector"] = cssSelectorsOrXpath;
    auto response = sendRequest(QString("/send_enter_short/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::ScreenCapture(int instanceId, QString imagePath, QString fileName){
    QJsonObject jsonObject;
    jsonObject["image_path"] = imagePath;
    jsonObject["file_name"] = fileName;
    auto response = sendRequest(QString("/capture/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::GetUid(int instanceId){
    auto response = sendRequest(QString("/get_uid/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["uid"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::GetCookie(int instanceId, QString domain){
    auto response = sendRequest(QString("/get_cookie/%1?domain=%2").arg(instanceId).arg(domain));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return response["cookie"].toString();
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::ClickWithAction(int instanceId,QString cssSelectorsOrXpath){
    QJsonObject jsonObject;
    jsonObject["css_selectors_or_xpath"] = cssSelectorsOrXpath;
    auto response = sendRequest(QString("/click_with_action_single/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::click(int instanceId,QString cssSelectorsOrXpath){
    QJsonObject jsonObject;
    jsonObject["css_selectors_or_xpath"] = cssSelectorsOrXpath;
    auto response = sendRequest(QString("/click_single/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::GotoURLIfNotExist(int instanceId, QString url){
    QJsonObject jsonObject;
    jsonObject["url"] = url;
    auto response = sendRequest(QString("/goto_url_if_not_exist/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::AddCookieIntoChrome(int instanceId, QString cookie, QString domain){
    QJsonObject jsonObject;
    jsonObject["cookie"] = cookie;
    jsonObject["domain"] = domain;
    auto response = sendRequest(QString("/goto_url_if_not_exist/%1").arg(instanceId), jsonObject);
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}

QString ApiHandler::Refresh(int instanceId){
    auto response = sendRequest(QString("/refresh/%1").arg(instanceId));
    if (response.contains("status"))
    {
        QString status = response["status"].toString();
        if (status == "success")
        {
            return status;
        }
        else if (status == "error")
        {
            return "errorHandler:" + response["message"].toString();
        }
    }
    return "Unexpected response format";
}
