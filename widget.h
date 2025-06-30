#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QListWidget;

class Widget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *taskInput;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QListWidget *taskList;

private slots:
    void addTask();
    void deleteTask();


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
