#include <QtCore>
#include <QtHttpServer/QHttpServer>

static inline QString host(const QHttpServerRequest &request)
{
    return request.headers()[QStringLiteral("Host")].toString();
}

QString brap(const int url){
#ifdef MY_RC_PATH
#define MY_RC_PATH_ MY_RC_PATH
    QDir dir = QString(MY_RC_PATH_);
#endif
    QFile file(dir.absoluteFilePath("test.html"));
    file.open(QIODevice::ReadOnly);
    qDebug() << file.errorString();
    QString data = QString(file.readAll());
    file.close();
    QThread::sleep(20);
    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QHttpServer httpServer;
    httpServer.route("/", []() {
        return "Hello world";
    });

    httpServer.route("/query", [] (const QHttpServerRequest &request) {
        return QString("%1/query/").arg(host(request));
    });

    httpServer.route("/brick", &brap);

    httpServer.route("/brick/", &brap);

    httpServer.route("/query/", [] (qint32 id, const QHttpServerRequest &request) {
        return QString("%1/query/%2").arg(host(request)).arg(id);
    });

    httpServer.route("/query/<arg>/log", [] (qint32 id, const QHttpServerRequest &request) {
        return QString("%1/query/%2/log").arg(host(request)).arg(id);
    });

    httpServer.route("/query/<arg>/log/", [] (qint32 id, float threshold,
                                             const QHttpServerRequest &request) {
        return QString("%1/query/%2/log/%3").arg(host(request)).arg(id).arg(double(threshold));
    });

    httpServer.route("/user/", [] (const qint32 id) {
        return QString("User %1").arg(id);
    });

    httpServer.route("/user/<arg>/detail", [] (const qint32 id) {
        return QString("User %1 detail").arg(id);
    });

    httpServer.route("/user/<arg>/detail/", [] (const qint32 id, const qint32 year) {
        return QString("User %1 detail year - %2").arg(id).arg(year);
    });

    httpServer.route("/json/", [] {
        auto ret = QJsonObject{
            {
                {"key1", "1"},
                {"key2", "2"},
                {"key3", "3"}
            }
        };
        QThread::sleep(5);
        return ret;
    });

    httpServer.route("/assets/<arg>", [] (const QUrl &url) {
        return QHttpServerResponse::fromFile(QStringLiteral(":/assets/%1").arg(url.path()));
    });

    httpServer.route("/remote_address", [](const QHttpServerRequest &request) {
        return request.remoteAddress().toString();
    });

    const auto port = httpServer.listen(QHostAddress::Any, 58025);
    if (port == -1) {
        qDebug() << QCoreApplication::translate(
                        "QHttpServerExample", "Could not run on http://127.0.0.1:%1/").arg(port);
        return 0;
    }

    qDebug() << QCoreApplication::translate(
                    "QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

    return app.exec();
}
