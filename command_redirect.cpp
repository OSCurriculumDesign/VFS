#include "command_redirect.h"
#include "qdebug.h"

CRedirect::CRedirect()
{
}

CRedirect::~CRedirect()
{
    TerminateChildProcess();
}

bool CRedirect::StartChildProcess(bool bShowChildWindow)
{
    cmdHistoryPosition = -1;

    process = new CProcess();
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    emit OnChildStdOutWrite("$ ");
    return true;
}

bool CRedirect::IsChildRunning() const
{
    return true;
}

void CRedirect::TerminateChildProcess()
{

}

// Thread to monitoring the child process.

int CRedirect::ProcessThread()
{
    return 0;
}

// Function that write to the child stdin.

void CRedirect::WriteChildStdIn(QString command)
{
    //去掉开头空格
    command=command.replace(QRegExp("^[\\s]+"),"");
    //去除结尾空格
    command=command.replace(QRegExp("[\\s]+$"),"");
    //多个空格合并成一个
    command=command.replace(QRegExp("[\\s]+")," ");

    if(command != ""){
        cmdHistory.push_back(command);
        cmdHistoryPosition=cmdHistory.size()-1;
        process->write(command);
    }
    emit OnChildStdOutWrite("\n$ ");
}

QString CRedirect::GetLastCommand()
{
    if(cmdHistoryPosition < 0){
        cmdHistoryPosition = 0;
        return "";
    }
    if(cmdHistoryPosition >= cmdHistory.size()){
        cmdHistoryPosition = cmdHistory.size()-1;
        return "";
    }
    return cmdHistory[cmdHistoryPosition--];
}

QString CRedirect::GetNextCommand()
{
    if(cmdHistoryPosition >= cmdHistory.size()){
        cmdHistoryPosition = cmdHistory.size()-1;
        return "";
    }
    if(cmdHistoryPosition < 0){
        cmdHistoryPosition = -1;
        return "";
    }
    return cmdHistory[cmdHistoryPosition++];
}



 void CRedirect::readyReadStandardOutput()
 {
     emit OnChildStdOutWrite("\n"+process->readAllStandardOutput());
 }

 void CRedirect::readyReadStandardError()
 {
     emit OnChildStdErrWrite("\n"+process->readAllStandardError());
 }
