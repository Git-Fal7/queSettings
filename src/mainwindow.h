#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void itemTriggered(QTreeWidgetItem *it, int col);
    QStringList readFile(QString filepath);
    void loadSettings();
    void loadItems();

signals:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
