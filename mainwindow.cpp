#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <iostream>

#include "mainwindow.h"

const int board_size = 15;
const int board_margin = 30;
const int chess_r = 15;
const int chess_mark_size=6;
const int block_size = 40;
const int pos_delta = 20;
//int game_map [board_size][board_size] ={{0}};
bool chess_type = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    game_map.clear();
    for(int i = 0;i<board_size;i++)
    {
        std::vector<int> l;
        for(int j = 0;j<board_size;j++)
        {
            l.push_back(0);
        }
        game_map.push_back(l);

    }
    int size = board_margin *2 + block_size * board_size;
    setFixedSize(size,size);
    setMouseTracking(true);


}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //画出棋盘
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for (int i = 0; i < board_size+1; ++i) {
        painter.drawLine(board_margin+block_size*i,board_margin,board_margin+block_size*i,size().height()-board_margin);
        painter.drawLine(board_margin,board_margin+block_size*i,size().width()-board_margin,board_margin+block_size*i);
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    //画出落子标记
    if(click_r>0 && click_r<board_size &&
       click_c>0 && click_c<board_size &&
       game_map[click_r][click_c] == 0)
    {
        if(chess_type)
            brush.setColor(Qt::black);
        else {
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawRect(board_margin+block_size*click_c-chess_mark_size/2,board_margin+block_size*click_r -chess_mark_size/2,chess_mark_size,chess_mark_size);
    }
    for(int i = 0;i< board_size;i++)
    {
        for(int j = 0;j<board_size;j++)
        {
            if(game_map[i][j] == 1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(board_margin + block_size *j-chess_r,board_margin+block_size*i-chess_r,chess_r*2,chess_r*2);
            }
            else if(game_map[i][j] ==  -1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(board_margin + block_size *j-chess_r,board_margin+block_size*i-chess_r,chess_r*2,chess_r*2);
            }
        }
    }


}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    if(x>=board_margin+block_size/2 && x<size().width() - board_margin &&
       y>= board_margin+block_size/2 && y<size().height()-board_margin)
    {
        int c = x/block_size;
        int r = y/block_size;
        std::cout << "move:" << x << '\t' << y << '\t'<< r<< '\t' << c <<std::endl;



        int left_x = board_margin + block_size*c;
        int left_y = board_margin + block_size*r;

        click_c = -1;
        click_r = -1;
        int len = 0;
        len = sqrt((x-left_x)*(x-left_x) + (y-left_y*(y-left_y)));
        if(len < pos_delta)
        {
            click_r = r;
            click_c = c;
        }
        len = sqrt((x-left_x-block_size)*(x-left_x-block_size)+(y-left_y)*(y-left_y));
        if(len < pos_delta)
        {
            click_c = c+1;
            click_r = r;
        }
        len = sqrt((x-left_x)*(x-left_x)+(y-left_y-block_size)*(y-left_y-block_size));
        if(len < pos_delta)
        {
            click_c = c;
            click_r = r+1;
        }
        len = sqrt((x-left_x-block_size)*(x-left_x-block_size)+(y-left_y-block_size)*(y-left_y-block_size));
        if(len<pos_delta)
        {
            click_c = c+1;
            click_r = r+1;
        }
        update();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if( click_c >0 && click_c <board_size && click_r> 0 && click_r< board_size &&game_map[click_r][click_c] ==0)
    {
        if(chess_type)
        {
            game_map[click_r][click_c] = 1;
        }
        else {
            game_map[click_r][click_c] = -1;
        }
        chess_type = !chess_type;
        update();
#if 0
        for(int i = 0 ;i < board_size;++i)
        {
            for(int j = 0;j< board_size;++j)
            {
                std::cout << game_map[i][j] << '\t';
            }
            std::cout << std::endl;
        }
#endif
         std::cout << click_c <<'\t' << click_r <<std::endl;

    }
}
