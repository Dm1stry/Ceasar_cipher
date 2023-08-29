#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPlainTextEdit>


class Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget* parent = nullptr);
private:
    QVBoxLayout* window_layout_;
    QHBoxLayout* shift_layout_;  //layout that keeps shift setting
    QLabel* shift_label_;
    QSpinBox* shift_spin_box_;
    QLabel* source_text_label_;
    QPlainTextEdit* source_text_edit_;
    QLabel* encoded_text_label_;
    QPlainTextEdit* encoded_text_edit_;
};