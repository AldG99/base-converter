#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Convertidor de Sistemas Numéricos");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Proyecto Educativo");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}