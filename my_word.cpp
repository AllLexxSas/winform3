#include "my_word.h"
#include "ui_my_word.h"
#include <regex>
#include <string>
#include <vector>



My_Word::My_Word(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::My_Word)
{
    ui->setupUi(this);
}

My_Word::~My_Word()
{
    delete ui;
}


void My_Word::on_openFile_clicked()
{
   OpenFile();
}

void My_Word::OpenFile()
{
    QFile openFile (GetFilePath('w'));
    auto extension = openFile.fileName().split('.',QString::SkipEmptyParts).constLast();


    QByteArray textfile;
    if (openFile.open(QIODevice::ReadOnly))
    {
        textfile = openFile.readAll();
    }
    openFile.close();
    QString txtTemp = textfile.data();
    if (extension == "txt")
        ReadTextFile(txtTemp);
    else
        ReadHTMLFile(txtTemp);
}


void My_Word::on_saveFile_clicked()
{
    QFile saveFile(GetFilePath('s'));
    if (saveFile.exists())
        saveFile.remove();
    if(saveFile.open(QIODevice::WriteOnly))
           saveFile.write( ui->textEdit->toPlainText().toUtf8());
    saveFile.close();
}

QString My_Word::GetFilePath(char mode)
{
    auto workDir = QDir::current().path();
    if(mode == 'w')
     return QFileDialog::getOpenFileName(this,"открыть текстовый файл",
                                         workDir
                                         ,tr("text (*.txt) ;; html (*.html)"));
    else if (mode == 's')
        return QFileDialog::getSaveFileName(this,"сохранить текстовый файл",
                                            workDir,
                                            "text (*.txt)");
    else return nullptr;

}

void My_Word::ReadTextFile(QString &txt)
{
    WriteTextEdit(txt);
}

//Работал в C#, с регуляркой проблем не было.
//Тут ерунда какая то. Все редакторы показывают, что я
//правильно составил регулярное выражени (скрин приложу к заданию)
//в коде на выходе ерунда полная, что в Qt, что в C++
QString GetDataWeather(QString &weather)
{
    std::string test = weather.toStdString();
    QRegularExpression r (".+?([а-яА-Я]+)");
    //QRegularExpression reg{"\"city\":\"(\\w+)\".*?temp\":\"(-?\\d).+?\":\".+?description\":\"(.+?)\""};
    QRegularExpressionMatch m {r.match(weather)};
    std::smatch ma;
    //auto reg = std::regex(R"(.*?\"city\":\"(\w+)\".*?temp\":\"(-?\d).+?\":\".+?description\":\"(.+?)\")");
    auto reg = std::regex(R"(.+?([а-я А-Я]+).+?:\"(-?\d{1,3}))");
    std::regex_search(test, ma,reg );

    std::string ggg;
    for(int i = 0 ; ma.size() <=0 ; i++)
    {
        ggg += ma.str(i) + "\n";
    }
    //try {
        //std::vector <std::smatch> data{ std::sregex_iterator(std::cbegin(test), std::cend(test) , reg) ,
          //           std::sregex_iterator()};
          //qDebug() << QString::fromStdString( data[0].str());
    //}  catch (std::exception &ex) {

     return (QString::fromStdString(ggg));



    //}



   // qDebug() << QString::fromStdString( data[0].str());

    return QString::fromStdString(ggg);
}

void My_Word::ReadHTMLFile(QString &html)
{
    auto f = html.indexOf(tr("\"weather\""))+10;


    QString tempString;

    int count = 0;
    do{
        if (html.at(f) == '{' )
            ++count;
        if (html.at(f) == '}')
            --count;
        //ui->textEdit->append( html.at(f++));
        tempString += html.at(f++);
    }while(count != 0);

    auto fff = GetDataWeather( tempString);

    WriteTextEdit(fff);
}

void My_Word::WriteTextEdit(QString &str)
{
    ui->textEdit->setText(str);
}


void My_Word::on_helpButton_clicked()
{

    QResource::registerResource("./resmy.rcc");

      //Q_INIT_RESOURCE(resources);

     QFile file(":/Resources/help.txt");
     QString help;
     if (file.open(QIODevice::ReadOnly))
     {
         QTextStream str(&file);
         help = str.readAll();

     }

    QMessageBox* pmbx =
                        new QMessageBox("MessageBox",
                        help,
                        QMessageBox::Information,
                        QMessageBox::Yes,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
    int n = pmbx->exec();
    delete pmbx;
}

