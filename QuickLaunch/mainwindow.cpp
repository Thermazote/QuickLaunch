#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QKeyEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file.setFileName("Applist.txt");
    setWindowIcon(QIcon("icon.png"));
    this->setWindowTitle("Quick launch");
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "Error opening file", file.errorString());
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
    {;
        QCoreApplication::quit();
    }
}


void MainWindow::on_AppKey_returnPressed()
{
    if (!path.isEmpty())
    {
        if (path.contains("http"))
        {
            path.chop(1);
            path.remove("\"");
            QDesktopServices::openUrl(QUrl(path));
            QCoreApplication::quit();
        }
        else
        {
            QString program = path;
            QProcess *myProcess = new QProcess(this);
            myProcess->startDetached(program);
            QCoreApplication::quit();
        }
    }
    else
        QCoreApplication::quit();
}

void MainWindow::on_AppKey_textChanged(const QString &arg1)
{
    QString Name;
    QStringList list;
    QString string;
    bool isFound = false;
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd() && !isFound)
    {
        string = file.readLine();
        string.chop(1);
        if (string[0] == '#')
        {
            Name = string.remove(0,1);
            string = file.readLine();
            string.chop(1);
            path = string;
        }
        if (string.startsWith(ui->AppKey->text(), Qt::CaseInsensitive))
            isFound = true;
    }

    if (isFound == false || ui->AppKey->text().isEmpty())
    {
        Name.clear();
        path.clear();
    }

    file.close();
    ui->AppName->setText(Name);


}
