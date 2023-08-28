#include "encoder.h"


Encoder::Encoder(char shift, QObject * receiver, QObject* parent/*= 0*/)
  : QObject(parent),
    shift_(shift) ,
    receiver_(receiver)
{}

bool Encoder::eventFilter(QObject* parent, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent * key_event = dynamic_cast<QKeyEvent *> (event);
        int key_number = key_event->key();
        static const int alphabet_length = (Qt::Key_Z - Qt::Key_A + 1);
        if((key_number >= Qt::Key_A && key_number <= Qt::Key_Z))
        {
            key_number = (key_number - Qt::Key_A + this->shift_) % alphabet_length + Qt::Key_A;
            QString key_string;
            if(key_event->modifiers() && Qt::ShiftModifier)
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
        }
    }
    return false;
}

void Encoder::shiftChanged(int new_shift)
{
    this->shift_ = new_shift;
}