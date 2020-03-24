#pragma once

#include <QtWidgets/QMainWindow>
#include <string>
#include <vector>
#include "ui_IntersectGUI.h"
#define MAX_X 10  //表示画布中能显示的最大的x坐标
#define CANVAS_SIZE  (height()-40)
#define WINDOW_X  1000000 
#define RATIO  (WINDOW_X/MAX_X)
#define W_     (WINDOW_X/150)
#define TRANS(x)    ((x)*RATIO)
using namespace std;
//(0.5*RATIO)  
class IntersectGUI : public QMainWindow
{
	Q_OBJECT

public:
	IntersectGUI(QWidget *parent = Q_NULLPTR);
	vector<string> figures; //保存当前几何对象
	vector<std::pair<double, double>> points;//保存求解的交点
protected:
	void paintEvent(QPaintEvent*);
private:
	Ui::IntersectGUIClass ui;
	QString msg;//当前需要处理的信息
	QString filePath;

	void init_canvas();
	void draw_line(int x1, int y1, int x2, int y2, QColor const c = Qt::black);
	void draw_seg(int x1, int y1, int x2, int y2, QColor const c = Qt::green);
	void draw_ray(int x1, int y1, int x2, int y2, QColor const c = Qt::blue);
	void draw_circle(int x0, int y0, int r, QColor const c = Qt::black);
	void draw_points();
	void draw_figures_from_str(string str);

private slots:
	void on_infileButton_clicked();//读入文件内容到msg，并对msg解析，并呈现在当前几何图形的框中，更新figures
	void on_findFileButton_clicked();//从文件夹中选择文件并显示
	void on_addCButton_clicked();
	void on_addLineButton_clicked();
	void on_clearButton_clicked();
	void on_deleteButton_clicked();
	void on_drawFigureButton_clicked();
	int on_calcPButton_clicked();
};