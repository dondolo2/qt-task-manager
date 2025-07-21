#include "widget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QApplication>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Task Manager");
    resize(700, 500);
    this->setWindowIcon(QIcon(":/list.png"));
    this->setObjectName("MainContainer");


    taskInput = new QLineEdit(this);
    taskInput->setPlaceholderText("Enter a new task...");

    addButton = new QPushButton("Add Task", this);
    moveTaskToBinButton = new QPushButton("Move Task To Bin", this);
    moveDoneToBinButton = new QPushButton("Move Completed To Bin", this);
    restoreButton = new QPushButton("Restore Task", this);
    permanentDeleteButton = new QPushButton("Delete Permanently");
    loadButton = new QPushButton("Load from File", this);
    saveButton = new QPushButton("Save to File", this);
    loadButton->setObjectName("loadBtn");

    addButton->setToolTip("Click to add a new task");
    addButton->setObjectName("addBtn");


    mainLabel = new QLabel("📝 Action Board Tracker", this);
    QFont titleFont;
    titleFont.setPointSize(25);
    titleFont.setBold(true);
    mainLabel->setFont(titleFont);
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setOffset(2, 2);
    mainLabel->setGraphicsEffect(shadow);



    taskListLabel = new QLabel("📋 To-Do Tasks", this);
    doneLabel = new QLabel("✅ Completed Tasks", this);
    recyclingBinLabel = new QLabel("🗑️ Recycling Bin", this);

    QFont sectionFont;
    sectionFont.setPointSize(14);
    sectionFont.setBold(true);

    QFont listFont;
    sectionFont.setPointSize(16);
    sectionFont.setBold(true);

    taskListLabel->setFont(sectionFont);
    doneLabel->setFont(sectionFont);
    recyclingBinLabel->setFont(sectionFont);

    taskList = new QListWidget(this);
    taskList->setFont(listFont);
    doneList = new QListWidget(this);
    doneList->setFont(listFont);
    recyclingBinList = new QListWidget(this);
    recyclingBinList->setFont(listFont);

    // Theme toggle button
    themeToggleBtn = new QPushButton("☀️", this); // 🌙 = dark mode, ☀️ = light mode
    themeToggleBtn->setFixedSize(60, 35);
    themeToggleBtn->move(width() - themeToggleBtn->width() - 10, 10); // Top-right corner
    themeToggleBtn->setToolTip("Click to change theme");


    // Create scroll area and content widget
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollContent = new QWidget();
    scrollContent->setObjectName("MainContainer");

    QVBoxLayout *vbox = new QVBoxLayout(scrollContent);
    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();

    vbox->setContentsMargins(50, 50, 50, 50);
    vbox->setSpacing(12);

    hbox1->addWidget(taskInput);
    hbox1->addWidget(addButton);
    hbox2->addWidget(restoreButton);
    hbox2->addWidget(permanentDeleteButton);
    hbox2->addWidget(saveButton);
    hbox3->addWidget(loadButton);
    hbox3->addWidget(themeToggleBtn);

    vbox->addLayout(hbox3);
    vbox->addWidget(mainLabel);
    vbox->addLayout(hbox1);
    vbox->addWidget(taskListLabel);
    vbox->addWidget(taskList);
    vbox->addWidget(moveTaskToBinButton);
    vbox->addWidget(doneLabel);
    vbox->addWidget(doneList);
    vbox->addWidget(moveDoneToBinButton);
    vbox->addWidget(recyclingBinLabel);
    vbox->addWidget(recyclingBinList);
    vbox->addLayout(hbox2);


    // Set scroll content and layout
    scrollArea->setWidget(scrollContent);

    // Outer layout for scroll area
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    // outerLayout->addWidget(themeToggleBtn); // Keeps toggle on top-level (not scrollable)
    setLayout(outerLayout);


    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addTask()));
    connect(taskInput, SIGNAL(returnPressed()), this, SLOT(addTask()));
    connect(moveTaskToBinButton, SIGNAL(clicked(bool)), this, SLOT(moveTaskToBin()));
    connect(moveDoneToBinButton, SIGNAL(clicked(bool)), this, SLOT(moveDoneToBin()));
    connect(taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveTaskToDone(QListWidgetItem*)));
    connect(doneList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(moveBackToTaskList(QListWidgetItem*)));
    connect(restoreButton, SIGNAL(clicked(bool)), this, SLOT(restore()));
    connect(permanentDeleteButton, SIGNAL(clicked(bool)), this, SLOT(deletePermanently()));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveToFile()));
    // connect(themeToggleBtn, &QPushButton::clicked, this, &Widget::toggleTheme);

    bool isDarkMode = true; // Start with dark mode

    connect(themeToggleBtn, &QPushButton::clicked, this, [=]() mutable {
        if (isDarkMode) {
            QFile file(":/light.qss");
            if (file.open(QFile::ReadOnly)) {
                QString style = QLatin1String(file.readAll());
                this->setStyleSheet(style);
                themeToggleBtn->setText("🌙");
            }
        } else {
            QFile file(":/dark.qss");
            if (file.open(QFile::ReadOnly)) {
                QString style = QLatin1String(file.readAll());
                this->setStyleSheet(style);
                themeToggleBtn->setText("☀️");
            }
        }
        isDarkMode = !isDarkMode;
    });

    applyTheme(":/light.qss");
    applyTheme(":/dark.qss");

}

bool Widget::isDuplicate(QListWidget *list, const QString &text)
{
    for (int i = 0; i < list->count(); i++) {
        if (list->item(i)->text().compare(text, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }
    return false;
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

void Widget::moveTaskToBin()
{
    QListWidgetItem *taskItem = taskList->currentItem();
    if (!taskItem) {
        QMessageBox::information(this, "No Selection", "Please select a task to move to bin");
        return;
    }

    QListWidgetItem *binItem = new QListWidgetItem(taskItem->text());
    binItem->setFlags(binItem->flags() | Qt::ItemIsUserCheckable);
    binItem->setCheckState(taskItem->checkState());
    binItem->setData(Qt::UserRole, "todo");

    recyclingBinList->addItem(binItem);
    delete taskItem;

}

void Widget::moveDoneToBin()
{
    QListWidgetItem *doneItem = doneList->currentItem();
    if (!doneItem) {
        QMessageBox::information(this, "No Selection", "Please select a completed task to move to bin");
        return;
    }

    QListWidgetItem *binItem = new QListWidgetItem(doneItem->text());
    binItem->setFlags(binItem->flags() | Qt::ItemIsUserCheckable);
    binItem->setCheckState(doneItem->checkState());
    binItem->setData(Qt::UserRole, "done");

    recyclingBinList->addItem(binItem);
    delete doneItem;
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

    if (source == "done") {
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

void Widget::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Tasks", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Could not open the file for reading.");
        return;
    }

    QTextStream in(&file);
    QString line;
    enum Section { None, Todo, Done, Recycle } currentSection = None;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();

        if (line == "To-Do Tasks:") {
            currentSection = Todo;
        }
        else if (line == "Completed Tasks:") {
            currentSection = Done;
        }
        else if (line == "Recycling Bin:") {
            currentSection = Recycle;
        }
        else if (line.startsWith("- ")) {
            QString task = line.mid(2); // Start after "- "

            switch (currentSection) {
            case Todo:
                if (!isDuplicate(taskList, task)) {
                    QListWidgetItem *item = new QListWidgetItem(task);
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                    item->setCheckState(Qt::Unchecked);
                    taskList->addItem(item);
                }
                break;
            case Done:
                if (!isDuplicate(doneList, task)) {
                    QListWidgetItem *item = new QListWidgetItem(task);
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                    item->setCheckState(Qt::Checked);
                    doneList->addItem(item);
                }
                break;
            case Recycle:
                if (!isDuplicate(recyclingBinList, task)) {
                    QListWidgetItem *item = new QListWidgetItem(task);
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                    item->setCheckState(Qt::Unchecked);
                    recyclingBinList->addItem(item);
                }
                break;
            default:
                break;
            }
        }
    }
    file.close();
    QMessageBox::information(this, "Loaded", "Tasks successfully merged with existing lists!");
}

void Widget::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Tasks", "", "Text Files (*.txt)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Could not open file for writing.");
        return;
    }

    QTextStream out(&file);

    // ---- To-Do Section ----
    out << "To-Do Tasks:\n";
    for (int i = 0; i < taskList->count(); i++) {
        QListWidgetItem *item = taskList->item(i);
        out << "- " << item->text() << "\n";
    }
    out << "\n";

    // ---- Completed Section ----
    out << "Completed Tasks:\n";
    for  (int i = 0; i < doneList->count(); i++) {
        QListWidgetItem *item = doneList->item(i);
        out << "- " << item->text() << "\n";
    }
    out << "\n";

    // ---- Recycle Bin Section ----
    out << "Recycling Bin:\n";
    for (int i = 0; i < recyclingBinList->count(); i++) {
        QListWidgetItem *item = recyclingBinList->item(i);
        out << "- " << item->text() << "\n";
    }

    file.close();
    QMessageBox::information(this, "Saved", "Tasks saved successfully!");
}

void Widget::toggleTheme()
{
    if (currentTheme == "light") {
        applyTheme(":/dark.qss");
        currentTheme = "dark";
        themeToggleBtn->setText("☀️");
    } else {
        applyTheme(":/light.qss");
        currentTheme = "light";
        themeToggleBtn->setText("🌙");
    }
}

void Widget::applyTheme(const QString &resourcePath)
{
    QFile file(resourcePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        qApp->setStyleSheet(styleSheet);
    } else {
        qDebug() << "Failed to theme:" << resourcePath;
    }
}



Widget::~Widget() {}
