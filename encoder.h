#pragma once
#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QApplication>

//In fact thit is just Event Filter that retranslate encoded input to choosen object

class Encoder : public QObject
{
    Q_OBJECT
public:
    Encoder(char shift, QObject * receiver, QObject* parent = 0);
protected:
    bool eventFilter(QObject* parent, QEvent* event);  //Override of QObject method
private:
    char shift_;  //Shift of code, for example if shift = 1 a -> b, c -> d, etc.
    QObject* receiver_;  //Object, that will recieve encoded input
public slots:
    void shiftChanged(int new_shift);  //Slot that changes shift after it's done from UI by user
};