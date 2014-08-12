#include <QCoreApplication>
#include <manipulator.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    Manipulator manipulator;

    return a.exec();
}
