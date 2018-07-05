#include "widget.h"
#include "ui_widget.h"
#include "qconsolewidget.h"
#include "qdebug.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QConsoleWidget *console = new QConsoleWidget(this);
    QConsoleWidget *console2 = new QConsoleWidget(this);
    QConsoleWidget *console3 = new QConsoleWidget(this);

    ui->tabWidget->addTab(console,"tab1");
    ui->tabWidget->addTab(console2,"tab2");
    ui->tabWidget->addTab(console3,"tab3");

    QTextEdit *t = new QTextEdit("123",this);

//    QTextEdit *text = new QTextEdit("123",this);
//    ui->verticalLayoutLeft->addWidget(console);
//    ui->verticalLayoutRight->addWidget(console);

    QAction *actionA = new QAction(this);
    actionA->setShortcut(QKeySequence(tr("Ctrl+t")));
    connect(actionA, &QAction::triggered, this, &Widget::AddTab);

}

void Widget::AddTab(){
    qDebug()<<"123";
}

void Widget::keyPressEvent(QKeyEvent *event)
{
//    switch (event->key())
//    {
//        case Qt::Key_A:// 被窗口button占用，失效，不能处理
//        {
//            if (event->modifiers() & Qt::ControlModifier)
//            {
//                QMessageBox::about(NULL, "Ctr+A", "Ctr+A");
//            }
//            break;
//        }
//        default:
//        {
//            qDebug() << event->key();
//        }
//    }
}


Widget::~Widget()
{
    delete ui;
}


