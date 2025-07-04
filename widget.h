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
    QPushButton *deleteButton;
    QListWidget *taskList;
    QListWidget *doneList;
    QLabel *mainLabel;
    QLabel *taskListLabel;
    QLabel *doneLabel;
    QString m_lastTaskText;
    QString m_lastDoneText;

private slots:
    void addTask();
    void deleteTask();
    void moveTaskToDone(QListWidgetItem *item);
    void moveBackToTaskList(QListWidgetItem *item);
    void checkEditedItemForDuplicates(QListWidgetItem *item);
    void handleTaskListItemChanged(QListWidgetItem *item);
    void handleDoneListItemChanged(QListWidgetItem *item);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
