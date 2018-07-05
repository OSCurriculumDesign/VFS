#include "widget.h"
#include "ui_widget.h"
#include "qconsolewidget.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // init console tabs
    QConsoleWidget *console = new QConsoleWidget(this);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(console,"tab1");
    tabNum = 1;
    connect(ui->tabWidget,
            SIGNAL(tabCloseRequested(int)),this,
            SLOT(tabCloseRequested(int)));
    //init tree widget
    QTreeWidget *tree = ui->treeWidget;
    QTreeWidgetItem *items1 = new QTreeWidgetItem(tree,
                                QStringList(QString("num_1")));
    QTreeWidgetItem *items2 = new QTreeWidgetItem(items1,
                                QStringList(QString("num_1")));
    QTreeWidgetItem *items3 = new QTreeWidgetItem(tree,
                                QStringList(QString("num_3")));
}

void Widget::tabCloseRequested(int index){
    ui->tabWidget->removeTab(index);
}

void Widget::AddTab(){
    ui->tabWidget->addTab(new QConsoleWidget(this),
                          QString("tab%1").arg(++tabNum));
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_T:
        {
            if (event->modifiers() & Qt::ControlModifier)
            {
//                QMessageBox::about(NULL, "add a tab", "add a tab");
                AddTab();
            }
            break;
        }
        default:
        {
        }
    }
}

Widget::~Widget()
{
    delete ui;
}


