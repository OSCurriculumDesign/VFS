#include "qconsolewidget.h"

#include <QKeyEvent>

QConsoleWidget::QConsoleWidget(QWidget *parent) : QTextEdit(parent)
{
    //设置禁止ctrl-z
    setUndoRedoEnabled(false);

    //设置颜色
    setTextColor(QColor("white"));
    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor("#252525"));
    this->setPalette(p);

    //$ 的位置
    fixedPosition = 0;
    redirect = new CRedirect();
    connect(redirect, SIGNAL(OnChildStdOutWrite(QString)), this, SLOT(OnChildStdOutWrite(QString)));
    connect(redirect, SIGNAL(OnChildStarted()), this, SLOT(OnChildStarted()));
    connect(redirect, SIGNAL(OnChildStdErrWrite(QString)), this, SLOT(OnChildStdErrWrite(QString)));
    connect(redirect, SIGNAL(OnChildTerminate()), this, SLOT(OnChildTerminate()));

    redirect->StartChildProcess(false);
}

QConsoleWidget::~QConsoleWidget()
{
    delete redirect;
}

void QConsoleWidget::OnChildStarted()
{
}

void QConsoleWidget::OnChildStdOutWrite(QString szOutput)
{
    insertPlainText(szOutput);
    fixedPosition = textCursor().position();

    //滑动到底部
    QTextCursor cursor =  this->textCursor();
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}

void QConsoleWidget::OnChildStdErrWrite(QString szOutput)
{
    append(szOutput);
    fixedPosition = textCursor().position();
}

void QConsoleWidget::OnChildTerminate()
{
    //exit(1);
}

void QConsoleWidget::keyPressEvent(QKeyEvent *event)
{
    bool accept;
    int count;
    QString cmd;

    int key = event->key();
    if (key == Qt::Key_Backspace || event->key() == Qt::Key_Left) {
        accept = textCursor().position() > fixedPosition;
    } else if (key == Qt::Key_Return) {
        accept = false;
        count= toPlainText().count() - fixedPosition;
        cmd = toPlainText().right(count);
        redirect->WriteChildStdIn(cmd);
    } else if (key == Qt::Key_Up) {
        //TODO 取上条指令
        accept = false;
        count = toPlainText().count() - fixedPosition;
        //删除当前指令
        for(int i=0;i<count;i++) textCursor().deletePreviousChar();
        insertPlainText(redirect->GetLastCommand());
    } else if (key == Qt::Key_Down) {
        //TODO 取下条指令
        accept = false;
        count = toPlainText().count() - fixedPosition;
        //删除当前指令
        for(int i=0;i<count;i++) textCursor().deletePreviousChar();
        insertPlainText(redirect->GetNextCommand());
    } else {
        accept = textCursor().position() >= fixedPosition;
    }

    if (accept) {
        QTextEdit::keyPressEvent(event);
    }
}

void QConsoleWidget::cursorPositionChanged()
{
    if (textCursor().position() < fixedPosition) {
        textCursor().setPosition(fixedPosition);
    }
}
