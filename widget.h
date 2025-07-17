#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>

class QLineEdit;
class QPushButton;
class QListWidget;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *taskInput;
    QPushButton *addButton;
    QPushButton *moveToBinButton;
    QPushButton *restoreButton;
    QPushButton *permanentDeleteButton;
    QListWidget *taskList;
    QListWidget *doneList;
    QListWidget *recyclingBinList;
    QLabel *mainLabel;
    QLabel *taskListLabel;
    QLabel *doneLabel;
    QLabel *recyclingBinLabel;

private slots:
    void addTask();
    void moveToBin();
    void moveTaskToDone(QListWidgetItem *item);
    void moveBackToTaskList(QListWidgetItem *item);
    void restore();
    void deletePermanently();


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
