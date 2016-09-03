
#include <QObject>

#include "QQmlConstRefPropertyHelpers.h"
#include "QQmlVarPropertyHelpers.h"
#include "QQmlAutoPropertyHelpers.h"

#include "QQmlObjectListModel.h"
#include "QQmlPtrPropertyHelpers.h"



class AddressModellItem : public QObject {
    Q_OBJECT
    QML_CONSTANT_CSTREF_PROPERTY (QString, ids)
    QML_CONSTANT_CSTREF_PROPERTY (QString, first)
    QML_CONSTANT_CSTREF_PROPERTY (QString, last)
    QML_CONSTANT_CSTREF_PROPERTY (QString, avatar)

public:
    explicit AddressModellItem (
             const QString &ids
            ,const QString &fi
            ,const QString &la
            ,const QString &av
            ) :
          m_ids(ids),
          m_first(fi),
          m_last(la),
          m_avatar(av)
    { }
};


class AddressModel : public QQmlObjectListModel<AddressModellItem> {};

