#ifndef CPROCESS_H
#define CPROCESS_H

#include <QString>
#include <QObject>

class CProcess: public QObject
{
    Q_OBJECT

public:
    CProcess();
    ~CProcess();
    void write(QString command);
    QString readAllStandardOutput();
    QString readAllStandardError();

signals:
    void readyReadStandardOutput();
    void readyReadStandardError();
};

#endif // CPROCESS_H
