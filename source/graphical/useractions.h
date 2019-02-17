#ifndef USERACTIONS_H
#define USERACTIONS_H

#include <QObject>
#include <QAction>

class UserActions : public QObject
{
    Q_OBJECT
public:
    UserActions();
    ~UserActions();
    QAction* actionCreateServer() {return createServerAction;}
    void setCreateServerEnabled(bool ok) {createServerAction->setEnabled(ok);}
    QAction* actionEditServer() {return editServerAction;}
    void setEditServerEnabled(bool ok) {editServerAction->setEnabled(ok);}
    QAction* actionStartServer() {return startServerAction;}
    void setStartServerEnabled(bool ok) {startServerAction->setEnabled(ok);}
    QAction* actionSuspendServer() {return suspendServerAction;}
    void setSuspendServerEnabled(bool ok) {suspendServerAction->setEnabled(ok);}
    QAction* actionDeleteServer() {return deleteServerAction;}
    void setDeleteServerEnabled(bool ok) {deleteServerAction->setEnabled(ok);}
    QAction* actionAddSerDevice() {return addSerDeviceAction;}
    void setAddSerDeviceEnabled(bool ok) {addSerDeviceAction->setEnabled(ok);}
    QAction* actionEditSerDevice() {return editSerDeviceAction;}
    void setEditSerDeviceEnabled(bool ok) {editSerDeviceAction->setEnabled(ok);}
    QAction* actionDelSerDevice() {return delSerDeviceAction;}
    void setDelSerDeviceEnabled(bool ok) {delSerDeviceAction->setEnabled(ok);}

    QAction* actionCreateClient() {return createClientAction;}
    void setCreateClientEnabled(bool ok) {createClientAction->setEnabled(ok);}
    QAction* actionEditClient() {return editClientAction;}
    void setEditClientEnabled(bool ok) {editClientAction->setEnabled(ok);}
    QAction* actionStartClient() {return startClientAction;}
    void setStartClientEnabled(bool ok) {startClientAction->setEnabled(ok);}
    QAction* actionSuspendClient() {return suspendClientAction;}
    void setSuspendClientEnabled(bool ok) {suspendClientAction->setEnabled(ok);}
    QAction* actionDeleteClient() {return deleteClientAction;}
    void setDeleteClientEnabled(bool ok) {deleteClientAction->setEnabled(ok);}

    QAction* actionRestore() {return restoreAction;}
    QAction* actionQuit() {return quitAction;}
    QAction* actionAbout() {return aboutAction;}

    void setServerEnabled(bool ok);
    void setClientEnabled(bool ok);
public slots:

signals:
    void serverActionsTriggered(int);
    void clientActionsTriggered(int);
    void otherActionsTriggered(int);
private:
    QAction *createServerAction;
    QAction *editServerAction;
    QAction *startServerAction;
    QAction *suspendServerAction;
    QAction *deleteServerAction;
    QAction *addSerDeviceAction;
    QAction *editSerDeviceAction;
    QAction *delSerDeviceAction;

    QAction *createClientAction;
    QAction *editClientAction;
    QAction *startClientAction;
    QAction *suspendClientAction;
    QAction *deleteClientAction;

    QAction *restoreAction;
    QAction *quitAction;
    QAction *aboutAction;
private slots:
    void createServer();
    void editServer();
    void startServer();
    void suspendServer();
    void deleteServer();
    void addSerDevice();
    void editSerDevice();
    void delSerDevice();
    void createClient();
    void editClient();
    void startClient();
    void suspendClient();
    void deleteClient();
    void restore();
    void quit();
    void about();
};

#endif // USERACTIONS_H
