#include "widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCheckBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Task Manager");
    resize(700, 500);

    taskInput = new QLineEdit(this);
    taskInput->setPlaceholderText("Enter a new task...");

    addButton = new QPushButton("Add Taks", this);
    deleteButton = new QPushButton("Delete Task", this);

    taskList = new QListWidget(this);
    doneList = new QListWidget(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(taskInput);
    hbox->addWidget(addButton);

    vbox->addLayout(hbox);
    vbox->addWidget(taskList);
    vbox->addWidget(doneList);
    vbox->addWidget(deleteButton);

    setLayout(vbox);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addTask()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteTask()));
    connect(taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveTaskToDone(QListWidgetItem*)));
}

void Widget::addTask()
{
    QString task = taskInput->text().trimmed();
    if(!task.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
        return;
        // taskList->addItem(task);
        // taskInput->clear();
    } /*else {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
    }*/
    QListWidgetItem *item = new QListWidgetItem(item);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(Qt::Unchecked);
    taskList->addItem(item);
    taskInput->clear();

}

void Widget::deleteTask()
{
    QListWidgetItem *item = taskList->currentItem();
    if(item) {
        delete item;
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to delete.");
    }

}

// void Widget::moveTaskToDone(QListWidgetItem *item)
// {


// }


Widget::~Widget() {}
