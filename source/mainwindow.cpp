#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QKeyEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>

QFile file("AppList.txt");
QString Path;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("Launch.png"));
    this->setWindowTitle("Launch");
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
    if (!Path.isEmpty())
    {
        if (Path[0]=='h')
        {
            Path.chop(1);
            QDesktopServices::openUrl(QUrl(Path));
            QCoreApplication::quit();
        }
        else
        {
            QString program = Path;
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
            Path = string;
        }
        if (string.startsWith(ui->AppKey->text(), Qt::CaseInsensitive))
            isFound = true;
    }

    if (isFound == false || ui->AppKey->text().isEmpty())
    {
        Name.clear();
        Path.clear();
    }

    file.close();
    ui->AppName->setText(Name);


}
