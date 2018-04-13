#ifndef ACTIVITYLOG_H
#define ACTIVITYLOG_H

#include <QMainWindow>

namespace Ui {
class ActivityLog;
}

class ActivityLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityLog(QWidget *parent = 0);
    ~ActivityLog();

public slots:
    void addActivity(const QString &msg);

private:
    Ui::ActivityLog *ui;
};

#endif // ACTIVITYLOG_H
