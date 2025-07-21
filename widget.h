#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>

class QLineEdit;
class QPushButton;
class QListWidget;
class QLabel;
class QScrollBar;

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
    QPushButton *themeToggleBtn;
    // List Sections
    QListWidget *taskList;
    QListWidget *doneList;
    QListWidget *recyclingBinList;
    // Labels
    QLabel *mainLabel;
    QLabel *taskListLabel;
    QLabel *doneLabel;
    QLabel *recyclingBinLabel;

    QString currentTheme = "light";
    QWidget *central;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QGraphicsDropShadowEffect* shadow;

    bool isDuplicate(QListWidget *list, const QString &text);


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
    void toggleTheme();

    void applyTheme(const QString &resourcePath);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
