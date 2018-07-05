#include "command_process.h"
#include "qdebug.h"

CProcess::CProcess()
{

}

CProcess::~CProcess()
{

}

void CProcess::write(QString command){

    if(command != ""){
        qDebug()<<command;
        QStringList commands = command.split(" ");
        if(commands[0] == "clear"){

        }else if(commands[0] == "cd"){

        }else if(commands[0] == "pwd"){

        }else if(commands[0] == "mkdir"){

        }else if(commands[0] == "touch"){

        }else if(commands[0] == "ls"){

        }

        outputStr = commands[0];
        emit readyReadStandardOutput();
    }
}

QString CProcess::readAllStandardOutput()
{
    return outputStr;
}

QString CProcess::readAllStandardError()
{
    return "error";
}
