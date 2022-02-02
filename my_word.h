#pragma once
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QResource>
#include <QtCore>
#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class My_Word; }
QT_END_NAMESPACE

class My_Word : public QMainWindow
{
    Q_OBJECT

public:
    My_Word(QWidget *parent = nullptr);
    ~My_Word();

private slots:
    void on_openFile_clicked();

    void on_saveFile_clicked();

    void on_helpButton_clicked();

private:
    Ui::My_Word *ui;
    void OpenFile();
    QString GetFilePath(char);
    void ReadTextFile(QString&);
    void ReadHTMLFile(QString&);
    void WriteTextEdit(QString&);
};
