#include "widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Task Manager");
    resize(700, 500);

    taskInput = new QLineEdit(this);
    taskInput->setPlaceholderText("Enter a new task...");

    addButton = new QPushButton("Add Task", this);
    moveToBinButton = new QPushButton("Move To Bin", this);
    restoreButton = new QPushButton("Restore Task", this);
    permanentDeleteButton = new QPushButton("Delete Permanently");

    mainLabel = new QLabel("Action Board Tracker", this);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    mainLabel->setFont(titleFont);
    mainLabel->setAlignment(Qt::AlignCenter);


    taskListLabel = new QLabel("To-Do Task", this);
    doneLabel = new QLabel("Completed Tasks", this);
    recyclingBinLabel = new QLabel("Recycling Bin", this);
    QFont labelFont;
    labelFont.setBold(true);
    taskListLabel->setFont(labelFont);
    doneLabel->setFont(labelFont);
    recyclingBinLabel->setFont(labelFont);

    taskList = new QListWidget(this);
    doneList = new QListWidget(this);
    recyclingBinList = new QListWidget(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    QHBoxLayout *hbox2 = new QHBoxLayout(this);

    hbox1->addWidget(taskInput);
    hbox1->addWidget(addButton);
    hbox2->addWidget(restoreButton);
    hbox2->addWidget(permanentDeleteButton);

    vbox->addWidget(mainLabel);
    vbox->addLayout(hbox1);
    vbox->addWidget(taskListLabel);
    vbox->addWidget(taskList);
    vbox->addWidget(doneLabel);
    vbox->addWidget(doneList);
    vbox->addWidget(moveToBinButton);
    vbox->addWidget(recyclingBinLabel);
    vbox->addWidget(recyclingBinList);
    vbox->addLayout(hbox2);


    setLayout(vbox);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addTask()));
    connect(taskInput, SIGNAL(returnPressed()), this, SLOT(addTask()));
    connect(moveToBinButton, SIGNAL(clicked(bool)), this, SLOT(moveToBin()));
    connect(taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveTaskToDone(QListWidgetItem*)));
    connect(doneList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveBackToTaskList(QListWidgetItem*)));
    connect(restoreButton, SIGNAL(clicked(bool)), this, SLOT(restore()));
    connect(permanentDeleteButton, SIGNAL(clicked(bool)), this, SLOT(deletePermanently()));
}

void Widget::addTask()
{
    QString task = taskInput->text().trimmed();
    if(task.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
        taskInput->setFocus();
        return;
    }

    // Check for duplicates in taskList
    for(int i = 0; i < taskList->count(); ++i) {
        QListWidgetItem *existingItem = taskList->item(i);
        if(existingItem->text().compare(task, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Duplicate Task", "This task already exist in the To-Do list.");
            taskInput->setFocus();
            return;
        }
    }

    // Check for duplicates in the doneList
    for(int i = 0; i < doneList->count(); ++i) {
        QListWidgetItem *existingItem = doneList->item(i);
        if(existingItem->text().compare(task, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Duplicate Task", "This task already exist in the Completed list.");
            taskInput->setFocus();
            return;
        }
    }

    QListWidgetItem *item = new QListWidgetItem(task);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    taskList->addItem(item);
    taskInput->clear();
    taskInput->setFocus();
}

void Widget::moveToBin()
{
    QListWidgetItem *taskItem = taskList->currentItem();
    QListWidgetItem *doneItem = doneList->currentItem();

    QListWidgetItem *selectedItem = taskItem ? taskItem : doneItem;

    if (!selectedItem) {
        QMessageBox::information(this, "No Selection", "Please select a task to move to bin");
        return;
    }

    QListWidgetItem *binItem = new QListWidgetItem(selectedItem->text());
    binItem->setFlags(binItem->flags() | Qt::ItemIsUserCheckable);
    binItem->setCheckState(selectedItem->checkState());
    // Save source as Metadata
    if (taskItem) {
        binItem->setData(Qt::UserRole, "taskItem");
    } else if (doneItem) {
        binItem->setData(Qt::UserRole, "doneItem");
    }

    recyclingBinList->addItem(binItem);

    if (taskItem) {
        delete taskItem;
    } else if (doneItem) {
        delete doneItem;
    }

}



void Widget::moveTaskToDone(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked) {
        // Transfer text to doneList as a new item
        QListWidgetItem *doneItem = new QListWidgetItem(item->text());
        doneItem->setFlags(doneItem->flags() | Qt::ItemIsUserCheckable);
        doneItem->setCheckState(Qt::Checked);
        doneList->addItem(doneItem);
        delete item;
    }

}

void Widget::moveBackToTaskList(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Unchecked) {
        QListWidgetItem *uncheckedItem = new QListWidgetItem(item->text());
        uncheckedItem->setFlags(uncheckedItem->flags() | Qt::ItemIsUserCheckable);
        uncheckedItem->setCheckState(Qt::Unchecked);
        taskList->addItem(uncheckedItem);

        delete item;
    }
}

void Widget::restore()
{
    QListWidgetItem *selectedItem = recyclingBinList->currentItem();

    if (!selectedItem) {
        QMessageBox::information(this, "No Selection", "Please select a task to restore.");
        return;
    }

    QString source = selectedItem->data(Qt::UserRole).toString(); // Getting MetaData

    QListWidgetItem *restoredItem = new QListWidgetItem(selectedItem->text());
    restoredItem->setFlags(restoredItem->flags() | Qt::ItemIsUserCheckable);
    restoredItem->setCheckState(restoredItem->checkState());

    if (source == "doneItem") {
        restoredItem->setCheckState(Qt::Checked);
        doneList->addItem(restoredItem);
    } else {
        restoredItem->setCheckState(Qt::Unchecked);
        taskList->addItem(restoredItem);
    }
    delete selectedItem;
}

void Widget::deletePermanently()
{
    QListWidgetItem *selectedItem = recyclingBinList->currentItem();

    if(selectedItem) {
        delete selectedItem;
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to delete.");
    }
}


Widget::~Widget() {}
