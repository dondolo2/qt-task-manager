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
    // Buttons
    QPushButton *addButton;
    QPushButton *moveTaskToBinButton;
    QPushButton *moveDoneToBinButton;
    QPushButton *restoreButton;
    QPushButton *permanentDeleteButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    // List Sections
    QListWidget *taskList;
    QListWidget *doneList;
    QListWidget *recyclingBinList;
    // Labels
    QLabel *mainLabel;
    QLabel *taskListLabel;
    QLabel *doneLabel;
    QLabel *recyclingBinLabel;

private slots:
    void addTask();
    void moveTaskToBin();
    void moveDoneToBin();
    void moveTaskToDone(QListWidgetItem *item);
    void moveBackToTaskList(QListWidgetItem *item);
    void restore();
    void deletePermanently();
    void loadFromFile();
    void saveToFile();


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
