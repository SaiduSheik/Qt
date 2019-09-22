#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "demosource.h"
#include "demomodel.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
     QGuiApplication app(argc, argv);

     qmlRegisterType<DemoModel>("Demo", 1, 0, "DemoModel");
     qmlRegisterUncreatableType<DemoSource>("Demo", 1, 0, "DemoSource",
         QStringLiteral("DemoSource should not be created in QML"));

     DemoSource source;

     QQmlApplicationEngine engine;
     engine.rootContext()->setContextProperty(QStringLiteral("source"), &source);
     engine.load(QUrl(QLatin1String("qrc:/main.qml")));
     if (engine.rootObjects().isEmpty())
         return -1;

     return app.exec();
}
