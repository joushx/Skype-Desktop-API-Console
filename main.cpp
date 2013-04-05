#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);
    QTextStream cin(stdin);

    if (QDBusConnection::sessionBus().isConnected()) {
        QString skypeServiceName("com.Skype.API");
        QDBusInterface iface(skypeServiceName, "/com/Skype", "com.Skype.API", QDBusConnection::sessionBus());

        if (iface.isValid()) {

            cout << "OK: Connected to DBus" << endl;
            cout << "Enter Application Name:" << endl;

            QDBusReply<QString> reply = iface.call("Invoke", "NAME " + cin.readLine());

            if (reply.isValid()) {

                if(reply.value() == "OK"){

                    cout << "OK: Connection successfull" << endl;

                    cout << "Enter Protocol Version (1-8) eg. 5:" << endl;

                    // specify the protocol
                    reply = iface.call("Invoke", "PROTOCOL " + cin.readLine());

                    if (reply.isValid()) {

                        cout << "OK: Setting protocol version" << endl;

                        cout << "Enter command(s):" << endl;

                        while(true){

                            reply = iface.call("Invoke", cin.readLine());
                            cout << "\033[0;32m" + reply.value() + "\033[0;0m" << endl;

                        }
                    }
                }
                else{
                    cout << "Error: Connection rejected" << endl;
                }
            }
            else{
                cout << "Error: Connection failed" << endl;
            }
        }
    }
    else{
        cout << "Error: Cannot establish DBus connection!" << endl;
    }
    
    return a.exec();
}
