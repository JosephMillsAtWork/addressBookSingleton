
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>
#include <QDebug>


#include "QQmlConstRefPropertyHelpers.h"
#include "QQmlVarPropertyHelpers.h"
#include "QQmlAutoPropertyHelpers.h"

#include "QQmlObjectListModel.h"
#include "QQmlPtrPropertyHelpers.h"

#include "addressmodel.h"
#include "mockmodel.h"


#ifndef JSONMOLDELCPP_H
#define JSONMOLDELCPP_H
class JsonMoldelCPP : public QObject
{
    Q_OBJECT
    QML_READONLY_CSTREF_PROPERTY(QString,errorString)
    QML_READONLY_PTR_PROPERTY(AddressModel, addressModel)
    QML_READONLY_PTR_PROPERTY(MockDataModel, mockModel)

    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(ModelType modelType READ modelType WRITE setModelType NOTIFY modelTypeChanged)
    Q_ENUMS(ModelType)
public:
    explicit JsonMoldelCPP(QObject *parent = 0);
    Q_INVOKABLE void getJson();

    bool isRunning()const;
    Q_INVOKABLE void reFill();
    Q_INVOKABLE void activeChanged(const int &modelIndex);

    enum ModelType{
        Address,
        MockData
    };
    ModelType modelType ()const;
    void setModelType(const ModelType &modelType);

signals:
    QString error(const QString&);
    void done();
    void running(bool);
    // qml
    void isRunningChanged();
    void modelTypeChanged();


public slots:
    void handelError(const QString &errStr);
    void replyFinished(QNetworkReply*);

    void handleRunning(const bool &running);

private :
    QNetworkAccessManager *m_pNetworkAccessManager;
    AddressModel mjsonModel;
    bool m_running;
    ModelType m_modelType;
    MockDataModel mMockModel;


};
Q_DECLARE_METATYPE(AddressModel*)
Q_DECLARE_METATYPE(MockDataModel*)

#endif // JSONMOLDELCPP_H
