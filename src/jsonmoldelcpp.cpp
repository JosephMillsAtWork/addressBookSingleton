#include "jsonmoldelcpp.h"

JsonMoldelCPP::JsonMoldelCPP(QObject *parent) : QObject(parent)
  ,m_addressModel(&mjsonModel)
  ,mjsonModel{}
    ,m_running(false)

{
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
    connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    connect(this,SIGNAL(error(QString)),
            this,SLOT(handelError(QString)));

    connect(this,SIGNAL(running(bool)),
            this , SLOT(handleRunning(bool)));


    getJson();
}

/*!
 * \brief JsonMoldelCPP::getJson
    Init function to get the json when the class is called or when called from Qml
*/
void JsonMoldelCPP::getJson()
{
    QUrl url("http://addressbook-api.herokuapp.com/contacts");
    QNetworkRequest request;
    request.setUrl(url);
    //     set the raw headers maybe a api key ?
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    m_pNetworkAccessManager->get(request);
    running(true);
}

bool JsonMoldelCPP::isRunning() const
{
    return m_running;
}

void JsonMoldelCPP::handelError(const QString &errStr)
{
    seterrorString(errStr);
    emit running(false);
}

/*!
 \brief JsonMoldelCPP::replyFinished
  parse the json now that we have the reply from the server
 */
void JsonMoldelCPP::replyFinished(QNetworkReply *reply)
{
    QString json = reply->readAll();
    QJsonDocument jsonDocument  = QJsonDocument::fromJson(json.toUtf8());
    if( jsonDocument.isEmpty() )
    {
        error(QString("Some thing went wrong with creating the json document"));
        return;
    }
    else
    {
        // create the object
        QJsonObject jsonObject = jsonDocument.object();
        QJsonArray jsonArray = jsonObject["contacts"].toArray();
        // clear the model if it is not the 1st run
        if(m_addressModel->count() > 0 ){
            m_addressModel->clear();
        }
        // INFO
        // This is Descending would need a for for ascending
        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            m_addressModel->prepend(
                        new AddressModellItem (
                            obj["id"].toString(),
                        obj["first"].toString(),
                    obj["last"].toString(),
                    obj["avatar"].toString()
                    )
                    );
        }
    }
    emit done();
    emit running(false);
}

void JsonMoldelCPP::handleRunning(const bool &running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit isRunningChanged();
}

void JsonMoldelCPP::reFill()
{
    if(m_addressModel->isEmpty())
    {
        m_addressModel->clear();
    }
    getJson();
}
