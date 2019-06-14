//#include <QApplication>
#include <QDialog>

#include "ui_SettingsDialog.h"

int main(int argc, char * argv[]) {

    QApplication app(argc, argv);

    Ui::SettingsDialog ui;
    QDialog * dialog = new QDialog;
    ui.setupUi(dialog);

    dialog->show();

    return app.exec();

}