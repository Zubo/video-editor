#include <cstdlib>
#include <ctime>

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

    QString currentPath = QDir::currentPath();
    std::string currentPathStdStr;
    currentPathStdStr.resize(currentPath.size());
    std::memcpy(currentPathStdStr.data(), currentPath.toStdString().c_str(), currentPath.size());

    std::srand(std::time(0));

    BLLContext bllContext(currentPathStdStr);
    bllContext.init();

    engine.rootContext()->setContextProperty("rawVideosDirectoryPath", QString(bllContext.RawVideosDirectoryPath.c_str()));
    engine.rootContext()->setContextProperty("editedVideosDirectoryPath", QString(bllContext.EditedVideosDirectoryPath.c_str()));

	engine.addImageProvider("circle-effect", new VideoEffectImageProvider(bllContext._CircleEffect));
	engine.addImageProvider("number-effect", new VideoEffectImageProvider(bllContext._NumericalEffect));
	engine.addImageProvider("progressbar-effect", new VideoEffectImageProvider(bllContext._ProgressBarEffect));

    float constexpr timerIntervalMs = 30.0F;
    DelegateTimer circleEffectTimer(timerIntervalMs, [&bllContext, timerIntervalMs]() { bllContext._CircleEffect.update(timerIntervalMs); });
	engine.rootContext()->setContextProperty("circleEffectTimer", &circleEffectTimer);
    DelegateTimer numericalEffectTimer(timerIntervalMs, [&bllContext, timerIntervalMs]() { bllContext._NumericalEffect.update(timerIntervalMs); });
	engine.rootContext()->setContextProperty("numberEffectTimer", &numericalEffectTimer);
	DelegateTimer progressBareffectTimer(timerIntervalMs, [&bllContext, timerIntervalMs]() { bllContext._ProgressBarEffect.update(timerIntervalMs); });
	engine.rootContext()->setContextProperty("progressEffectTimer", &progressBareffectTimer);

    VideoProcessorInterface videoProcessorInterface(bllContext);
    engine.rootContext()->setContextProperty("videoProcessorInterface", &videoProcessorInterface);

    videoProcessorInterface.requestThumbnailGeneration();

    return app.exec();
}
