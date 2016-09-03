#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include <qqml.h>

#include "jsonmoldelcpp.h"



static QObject *modelAsProperty( QQmlEngine *engine, QJSEngine *scriptEngine )
{
  Q_UNUSED(engine)
  Q_UNUSED(scriptEngine)

  JsonMoldelCPP * s = new JsonMoldelCPP();
  return s;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qmlRegisterSingletonType<JsonMoldelCPP>(
      "org.joseph.awesome",1,0,                             // import name/ver
      "MiddleMan",                           // qml type name
      modelAsProperty );                           // provider

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
