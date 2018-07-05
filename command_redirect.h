#ifndef CREDIRECT_H
#define CREDIRECT_H

#define BUFFER_SIZE 256

#include <QString>
#include <QObject>
#include "command_process.h"
#include "vector"

class CRedirect : public QObject
{
    Q_OBJECT
public:
        CRedirect();
        ~CRedirect();

        bool StartChildProcess(bool bShowChildWindow = false);
        bool IsChildRunning() const;
        void TerminateChildProcess();
        void WriteChildStdIn(QString szInput);
        QString GetLastCommand();
        QString GetNextCommand();
private:
        std::vector<QString> cmdHistory;
        int cmdHistoryPosition;
protected:

        CProcess *process;

        int ProcessThread();
private slots:
        void readyReadStandardOutput();
        void readyReadStandardError();
signals:
        void OnChildStarted();
        void OnChildStdOutWrite(QString szOutput);
        void OnChildStdErrWrite(QString szOutput);
        void OnChildTerminate();
};

#endif // REDIRECT_H
