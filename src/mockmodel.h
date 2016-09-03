#include <QObject>

#include "QQmlConstRefPropertyHelpers.h"
#include "QQmlVarPropertyHelpers.h"
#include "QQmlAutoPropertyHelpers.h"

#include "QQmlObjectListModel.h"


class MockDataItems:public QObject{
    Q_OBJECT
    QML_CONSTANT_CSTREF_PROPERTY (int, cId)
    QML_CONSTANT_CSTREF_PROPERTY (QString, macAddress)
    QML_CONSTANT_CSTREF_PROPERTY (QString, uname)
    QML_CONSTANT_CSTREF_PROPERTY (QString,  bitcoinAddress)
    QML_WRITABLE_CSTREF_PROPERTY( QString,ccName)
    QML_CONSTANT_CSTREF_PROPERTY(QString , ccNumber)

public:
    explicit MockDataItems (
             const int &cId
            ,const QString &macAddress
            ,const QString &uname
            ,const QString &bitcoinAddress
            ,const QString &ccName
            , const QString &ccNumber
            ) :
          m_cId(cId),
          m_macAddress(macAddress),
          m_uname(uname),
          m_bitcoinAddress(bitcoinAddress),
          m_ccName(ccName ),
          m_ccNumber(ccNumber)
    { }
};




class MockDataModel : public QQmlObjectListModel<MockDataItems>{};
