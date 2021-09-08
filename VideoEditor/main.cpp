#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include <BLLContext.h>
#include <VideoEffectImageProvider.h>
#include <DelegateTimer.h>
#include <VideoProcessorInterface.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    engine.rootContext()->setContextProperty("executableRoot", QDir::currentPath());
    QString currentPath = QDir::currentPath();
    std::string currentPathStdStr;
    currentPathStdStr.resize(currentPath.size());
    std::memcpy(currentPathStdStr.data(), currentPath.toStdString().c_str(), currentPath.size());

    BLLContext bllContext(currentPathStdStr);

	engine.addImageProvider("circle-effect", new VideoEffectImageProvider(bllContext._CircleEffect));
	engine.addImageProvider("number-effect", new VideoEffectImageProvider(bllContext._NumericalEffect));

    DelegateTimer circleEffectTimer(1000, [&bllContext]() { bllContext._CircleEffect.randomize(); });
	engine.rootContext()->setContextProperty("circleEffectTimer", &circleEffectTimer);
    DelegateTimer numericalEffectTimer(400, [&bllContext]() { bllContext._NumericalEffect.randomize(); });
	engine.rootContext()->setContextProperty("numberEffectTimer", &numericalEffectTimer);

    VideoProcessorInterface videoProcessorInterface(bllContext);
    engine.rootContext()->setContextProperty("videoProcessorInterface", &videoProcessorInterface);

    return app.exec();
}
