#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<std::vector<int>> game_map;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int click_r,click_c;
};

#endif // MAINWINDOW_H
