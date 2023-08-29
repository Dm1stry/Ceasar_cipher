#include "encoder.h"


Encoder::Encoder(char shift, QObject * receiver, QObject* parent/*= 0*/)
  : QObject(parent),
    shift_(shift) ,
    receiver_(receiver)
{}

bool Encoder::eventFilter(QObject* parent, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)  //gets only Keyboard inputs
    {
        QKeyEvent * key_event = dynamic_cast<QKeyEvent *> (event);  //cast to key_event to use it's methods
        int key_number = key_event->key();
        constexpr int alphabet_length = (Qt::Key_Z - Qt::Key_A + 1);
        if((key_number >= Qt::Key_A && key_number <= Qt::Key_Z))  //Handle letters only
        {
            key_number = (key_number - Qt::Key_A + this->shift_) % alphabet_length + Qt::Key_A;  //Gets correct new key code, that is still letter
            QString key_string;
            if(key_event->modifiers() & Qt::ShiftModifier)
            {
                key_string = QChar(key_number).toUpper();
            }
            else
            {
                key_string = QChar(key_number).toLower();
            }
            QKeyEvent keyPress (
                QEvent::KeyPress,
                key_number,
                key_event->modifiers(),
                key_string
            );

            QApplication::sendEvent(receiver_, &keyPress);

            QKeyEvent keyRelease (
                QEvent::KeyRelease,
                key_number,
                key_event->modifiers(),
                key_string
            );

            QApplication::sendEvent(receiver_, &keyRelease);  
        }  //if((key_number >= Qt::Key_A && key_number <= Qt::Key_Z))
    }  //if(event->type() == QEvent::KeyPress)
    return false;  //Anyway says that event wasn't processed to source widget could get event too
}

void Encoder::shiftChanged(int new_shift)
{
    this->shift_ = new_shift;
}