#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QApplication>

#include <QDebug>

class Encoder : public QObject
{
    Q_OBJECT
public:
    Encoder(char shift, QObject * receiver, QObject* parent = 0);
protected:
    bool eventFilter(QObject* parent, QEvent* event);
private:
    char shift_;
    QObject* receiver_;
public slots:
    void shiftChanged(int new_shift);
};