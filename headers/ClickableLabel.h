/**
 * \file ClickableLabel.h
 * \author David Thompson
 * \brief A QLabel that emits a clicked signal when it is clicked. Almost
 * identical to the example from the Qt website:
 * https://wiki.qt.io/Clickable_QLabel
 * \date 2019-09-5
 */

#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

#include <iostream>

#include <QLabel>

class ClickableLabel : public QLabel {

    Q_OBJECT

public:
    explicit ClickableLabel(QWidget * parent = nullptr,
        Qt::WindowFlags f = Qt::WindowFlags()) :
        QLabel(parent) {}

    ~ClickableLabel() {}

signals:
    void released();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) {
        emit released();
    }

};

#endif // CLICKABLE_LABEL_H