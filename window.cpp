#include "window.h"
#include "encoder.h"

Window::Window(QWidget* parent /*= nullptr*/)
  : QWidget(parent),
    window_layout_(new QVBoxLayout),
    shift_layout_(new QHBoxLayout),
    shift_label_(new QLabel("&Shift")),
    shift_spin_box_(new QSpinBox),
    source_text_label_(new QLabel("&Original text")),
    source_text_edit_(new QPlainTextEdit),
    encoded_text_label_(new QLabel("&Encoded text")),
    encoded_text_edit_(new QPlainTextEdit)
{
    shift_label_->setBuddy(shift_spin_box_);
    shift_layout_->addWidget(shift_label_);
    shift_layout_->addWidget(shift_spin_box_);
    window_layout_->addLayout(shift_layout_);

    source_text_label_->setBuddy(source_text_edit_);

    Encoder * ceasar_encoder = new Encoder(shift_spin_box_->value(), encoded_text_edit_);
    source_text_edit_->installEventFilter(ceasar_encoder);
    window_layout_->addWidget(source_text_label_);
    window_layout_->addWidget(source_text_edit_);

    encoded_text_label_->setBuddy(encoded_text_edit_);

    window_layout_->addWidget(encoded_text_label_);
    window_layout_->addWidget(encoded_text_edit_);

    this->setLayout(window_layout_);

    QObject::connect(shift_spin_box_, SIGNAL(valueChanged(int)), ceasar_encoder, SLOT(shiftChanged(int)));
    shift_spin_box_->setValue(3);
    //QObject::connect(source_text_edit_, SIGNAL(cursorPositionChanged()), encoded_text_edit_, SLOT(setCursor()));
}