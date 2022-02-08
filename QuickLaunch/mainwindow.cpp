#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file.setFileName("Applist.txt");
    setWindowIcon(QIcon("icon.png"));
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
    {
        QCoreApplication::quit();
    }
}


void MainWindow::on_AppKey_returnPressed()
{
    if (!this->path.isEmpty()) {
        if (this->path.startsWith("https://")) {
            QDesktopServices::openUrl(QUrl(this->path));
        }
        else {
            QProcess process;
            qDebug() << this->args;
            process.startDetached(this->path, this->args);
        }
    }
    QCoreApplication::quit();
}

void MainWindow::on_AppKey_textChanged()
{
    QString title;
    QString path;
    QString line;
    QStringList args;
    bool isFound = false;

    file.open(QIODevice::ReadOnly);

    ui->AppName->clear();
    this->path.clear();
    this->args.clear();

    while(!file.atEnd() && !isFound) {
        line = file.readLine();
        line.chop(2);
        if (line[0] == '#') {
            title = line.remove(0,1);
            line = file.readLine();
            line.chop(2);
            path = line;
            args.clear();
        }
        else if (line[0] == '-') {
            line.remove(0,1);
            args.append(line);
        }
        else if (line.startsWith(ui->AppKey->text(), Qt::CaseInsensitive) && !(ui->AppKey->text() == "")) {
            isFound = true;
            this->path = path;
            this->args = args;
            ui->AppName->setText(title);
        }
    }

    file.close();
}
