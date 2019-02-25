#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "myglitem.h"
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QTranslator translator;
    if(translator.load("testmmp2018p1_de.qm", ":/translations"))
    {
        app.installTranslator(&translator);
    }

    QQmlApplicationEngine engine;



    qmlRegisterType<MyGlItem>("GlComponents", 1, 0,"MyGlItem" );

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
