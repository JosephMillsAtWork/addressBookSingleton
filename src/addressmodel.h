
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
    QML_WRITABLE_CSTREF_PROPERTY(bool,active)

public:
    explicit AddressModellItem (
             const QString &ids
            ,const QString &fi
            ,const QString &la
            ,const QString &av
            ,const bool &active
            ) :
          m_ids(ids),
          m_first(fi),
          m_last(la),
          m_avatar(av),
          m_active(active)

    { }
};


class AddressModel : public QQmlObjectListModel<AddressModellItem> {};

