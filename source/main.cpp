#include <QObject>
#include <QtPlugin>
#include <QTextCodec>
#include <QApplication>
#include <QDesktopWidget>
#include "../source/graphical/mainwindow.h"

//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    /* 应用程序基本配置 */
    QApplication application(argc,argv);
    QFont font("Consolas",11);
    application.setFont(font); //设置应用显示字体
    /* 应用程序窗口配置 */
    MainWindow window;
    int x = (application.desktop()->width()-window.width())/2;
    int y = (application.desktop()->height()-window.height())/2-50;
    window.move(x,y); //设置窗口居中显示
    window.show();
    QObject::connect(&window,SIGNAL(quit()),&application,SLOT(quit()));

    return application.exec();
}
