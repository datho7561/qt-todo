/**
 * \file AboutQtTodoWidget.h
 * \brief 
 * \author David Thompson
 * \date 2019-09-03
 */

#ifndef ABOUT_QT_TODO_DIALOG_H
#define ABOUT_QT_TODO_DIALOG_H

#include "ui_AboutQtTodoWidget.h"

#include <QDialog>

class AboutQtTodoDialog : public QDialog, public Ui::AboutQtTodoDialog {

public:
    AboutQtTodoDialog(QWidget * parent = nullptr):
        QDialog(parent) {
        
        setupUi(this);
    }

};

#endif // ABOUT_QT_TODO_DIALOG_H
