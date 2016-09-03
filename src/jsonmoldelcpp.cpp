#include "jsonmoldelcpp.h"

JsonMoldelCPP::JsonMoldelCPP(QObject *parent) : QObject(parent)
  ,m_addressModel(&mjsonModel)
  ,mjsonModel{}
    ,m_running(false)
  ,m_modelType(Address)
  , m_mockModel(&mMockModel)
  ,mMockModel{}

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

    QUrl add_url("http://addressbook-api.herokuapp.com/contacts");
    QUrl mock_url("https://raw.githubusercontent.com/JosephMillsAtWork/addressBookSingleton/master/MOCK_DATA.json");

    QNetworkRequest request;

    if (m_modelType == Address){
        request.setUrl(add_url);
    }else{
        request.setUrl(mock_url);
    }
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

        if (m_modelType == Address ){
            QJsonObject jsonObject = jsonDocument.object();

            QJsonArray jsonArray = jsonObject["contacts"].toArray();
            // clear the model if it is not the 1st run
            if(m_addressModel->count() > 0 ){
                m_addressModel->clear();
            }
            // INFO
            // This is Descending
            foreach (const QJsonValue & value, jsonArray) {
                QJsonObject obj = value.toObject();
                m_addressModel->prepend(
                            new AddressModellItem (
                                obj["id"].toString(),
                                obj["first"].toString(),
                                obj["last"].toString(),
                                obj["avatar"].toString(),
                                false
                            )
                        );
            }
        }
        else
        {

            QJsonArray jsonArray = jsonDocument.array();
            if( ! m_mockModel->isEmpty() )
            {
                m_mockModel->clear();
            }
            // INFO
            // This is Ascending
            for (QJsonValue it : jsonArray){
                  QJsonObject obj = it.toObject();
                  m_mockModel->append(
                              new MockDataItems (
                                    obj["id"].toInt(),
                                    obj["mac_address"].toString(),
                                    obj["user_name"].toString(),
                                    obj["btn_address"].toString(),
                                    obj["cc_number"].toString(),
                                    obj["cc_type"].toString()
                            )
                          );
               }
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

void JsonMoldelCPP::activeChanged(const int &modelIndex)
{
    qDebug() << "Here We should do Something with another class or whatever at this index  " << modelIndex ;
}

JsonMoldelCPP::ModelType JsonMoldelCPP::modelType() const{
    return m_modelType;
}

void JsonMoldelCPP::setModelType(const JsonMoldelCPP::ModelType &modelType)
{
    if(m_modelType == modelType)
        return;
    m_modelType = modelType;
    emit modelTypeChanged();

}
