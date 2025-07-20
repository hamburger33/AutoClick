#include "jsonhandler.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "defineConst.h"


JsonHandler::JsonHandler(QObject* parent)
    : QObject(parent)
{

}


JsonHandler::~JsonHandler() = default;

QString JsonHandler::GetJsonFileAsQString(QString filePath) const
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw std::runtime_error("JSON DECODING ERROR");
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QString fileData = stream.readAll();
    file.close();

    return fileData;
}

QJsonDocument JsonHandler::GetJsonDocFromQString(QString jsonFileData) const{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFileData.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !jsonDoc.isNull()) {
        throw std::runtime_error("JSON ��������");
    }
    return jsonDoc;
}

QJsonDocument JsonHandler::SetJsonDocFromOperationList(QJsonDocument jsonDoc, QList<OperationItem>& operationList, QString jsonDocName){
    QJsonObject rootObject = jsonDoc.object();
    QJsonArray jsonArray;
    for (const OperationItem& operation : operationList) {
        QJsonObject jsonObj;
        if (operation.actionType == OperationItem::ActionType::LaunchSoftware) {
            jsonObj.insert("type", "LaunchSoftware");
        }
        else if (operation.actionType == OperationItem::ActionType::ClickButton) {
            jsonObj.insert("type", "ClickButton");
        }
        jsonObj.insert("file", operation.filePath);
        jsonObj.insert("time", operation.timeInterval);
        jsonArray.append(jsonObj);
    }
    rootObject.insert(jsonDocName, jsonArray);
    jsonDoc.setObject(rootObject);
    return jsonDoc;
}

bool JsonHandler::WriteJsonDocToFilePath(const QJsonDocument& jsonDoc,const QString& filePath) const {
	QFile fileNew(filePath);
    if (!fileNew.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        return false;
	}

	QTextStream streamNew(&fileNew);
	streamNew.setEncoding(QStringConverter::Utf8);
	streamNew << jsonDoc.toJson();
	fileNew.close();
	return true;
}

