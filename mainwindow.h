#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <CTools.hpp>
#include <qlistwidget.h>
#include <set>
#include <QtPlugin>
#include <QTreeWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static std::vector<CTools::Position> error_positions;
    static std::vector<std::string> error_msgs;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_ErrorList_itemClicked(QListWidgetItem *item);

private:
    ///Creates a DFA Machine
    void CreateMachine();
    ///processes the Input with the walker
    void walk();
    ///populates list with data
    void populateLists();

    QTreeWidgetItem* traverseTree(CTools::PNode* node, QTreeWidgetItem* item);

    CTools::MachineWalker* m_walker;
    CTools::IParser* m_parser;
    std::set<std::string> m_symbolSet;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
