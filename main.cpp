#include "my_word.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    My_Word w;
    w.show();
    return a.exec();
}
