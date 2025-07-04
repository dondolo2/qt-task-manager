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
    setWindowTitle("Action Board Tracker");
    resize(700, 500);

    taskInput = new QLineEdit(this);
    taskInput->setPlaceholderText("Enter a new task...");

    addButton = new QPushButton("Add Taks", this);
    deleteButton = new QPushButton("Delete Task", this);

    mainLabel = new QLabel("Action Board Tracker", this);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    mainLabel->setFont(titleFont);
    mainLabel->setAlignment(Qt::AlignCenter);


    taskListLabel = new QLabel("To-Do Task", this);
    doneLabel = new QLabel("Completed Tasks", this);
    QFont labelFont;
    labelFont.setBold(true);
    taskListLabel->setFont(labelFont);
    doneLabel->setFont(labelFont);

    taskList = new QListWidget(this);
    doneList = new QListWidget(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(taskInput);
    hbox->addWidget(addButton);

    vbox->addWidget(mainLabel);
    vbox->addLayout(hbox);
    vbox->addWidget(taskListLabel);
    vbox->addWidget(taskList);
    vbox->addWidget(doneLabel);
    vbox->addWidget(doneList);
    vbox->addWidget(deleteButton);

    setLayout(vbox);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addTask()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteTask()));
    // connect(taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveTaskToDone(QListWidgetItem*)));
    // connect(doneList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveBackToTaskList(QListWidgetItem*)));

    connect(taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(handleTaskListItemChanged(QListWidgetItem*)));
    connect(doneList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(handleDoneListItemChanged(QListWidgetItem*)));

}

// Add these new functions:

// Add these new functions:
void Widget::handleTaskListItemChanged(QListWidgetItem *item)
{
    // First handle checkbox changes
    moveTaskToDone(item);

    // Then check if this was an edit (you'll need to track edits)
    // This is more complex and might require subclassing QListWidgetItem
}

void Widget::handleDoneListItemChanged(QListWidgetItem *item)
{
    // First handle checkbox changes
    moveBackToTaskList(item);

    // Then check if this was an edit
}

void Widget::addTask()
{
    QString task = taskInput->text().trimmed();
    if(task.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
        return;
    }

    // Check for duplicates in taskList
    for(int i = 0; i < taskList->count(); ++i) {
        QListWidgetItem *existingItem = taskList->item(i);
        if(existingItem->text().compare(task, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Duplicate Task", "This task already exist in the To-Do list.");
            return;
        }
    }

    // Check for duplicates in the doneList
    for(int i = 0; i < doneList->count(); ++i) {
        QListWidgetItem *existingItem = doneList->item(i);
        if(existingItem->text().compare(task, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Duplicate Task", "This task already exist in the Completed list.");
            return;
        }
    }

    QListWidgetItem *item = new QListWidgetItem(task);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(Qt::Unchecked);
    taskList->addItem(item);
    taskInput->clear();


}

void Widget::deleteTask()
{
    QListWidgetItem *taskItem = taskList->currentItem();
    QListWidgetItem *doneItem = doneList->currentItem();

    if(taskItem) {
        delete taskItem;
    } else if(doneItem) {
        delete doneItem;
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to delete.");
    }

}

void Widget::moveTaskToDone(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked) {
        taskList->blockSignals(true); // blocks signal triggers during changes
        doneList->blockSignals(true);

        // Transfer text to doneList as a new item
        QListWidgetItem *doneItem = new QListWidgetItem(item->text());
        doneItem->setFlags(doneItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        doneItem->setCheckState(Qt::Checked);
        doneList->addItem(doneItem);
        delete item;

        taskList->blockSignals(false); // restore
        doneList->blockSignals(false);
    }

}

void Widget::moveBackToTaskList(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Unchecked) {
        taskList->blockSignals(true);
        doneList->blockSignals(true);

        QListWidgetItem *uncheckedItem = new QListWidgetItem(item->text());
        uncheckedItem->setFlags(uncheckedItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        uncheckedItem->setCheckState(Qt::Unchecked);
        taskList->addItem(uncheckedItem);

        delete item;

        taskList->blockSignals(false);
        doneList->blockSignals(false);
    }

}

void Widget::checkEditedItemForDuplicates(QListWidgetItem *item)
{
    // Get the current list widget
    QListWidget* listWidget = qobject_cast<QListWidget*>(sender());
    if (!listWidget) return;

    // Get the current text and compare with previous text
    QString newText = item->text();
    static QString lastText; // This should be a class member in reality

    if (newText == lastText) {
        // Probably a checkbox change
        return;
    }
    lastText = newText;

    QString text = item->text().trimmed();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Empty Task", "Task name cannot be empty.");
        item->setText("Unnamed Task");
        return;
    }

    // Count how many items have the same text across both lists
    int duplicateCount = 0;

    auto countDuplicates = [&](QListWidget *list) {
        for (int i = 0; i < list->count(); ++i) {
            QListWidgetItem *current = list->item(i);
            if (current == item) continue;
            if (current->text().compare(text, Qt::CaseInsensitive) == 0) {
                duplicateCount++;
            }
        }
    };

    countDuplicates(taskList);
    countDuplicates(doneList);

    if (duplicateCount > 0) {
        QMessageBox::warning(this, "Duplicate Edit", "Another task with this name already exists.");
        // Optional: revert to previous text (setText can't do that directly unless you store it)
        item->setText(text + " (edited)");
        // item->setText(lastEditedText);
    }
}



Widget::~Widget() {}
