#include <QObject>

#ifndef SCANWORKER_H
#define SCANWORKER_H


class ScanWorker : public QObject
{
    Q_OBJECT
public:
    ScanWorker();
    ~ScanWorker();

public slots:
    void start();
signals:
    void newDeviceFound(const QString &addr, const QString &name);
    void finished();
    void error(QString err);
};

#endif // SCANWORKER_H
