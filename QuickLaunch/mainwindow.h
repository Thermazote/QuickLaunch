#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFIle>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *);

    void on_AppKey_returnPressed();

    void on_AppKey_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QFile file;
    QString path;
};
#endif // MAINWINDOW_H
