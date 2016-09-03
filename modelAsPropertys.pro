include(qmlsupermacros.pri)
TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/jsonmoldelcpp.cpp \
    src/addressmodel.cpp \
    src/mockmodel.cpp

HEADERS += \
    src/jsonmoldelcpp.h \
    src/addressmodel.h \
    src/mockmodel.h


RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =



