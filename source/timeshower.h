//此文件包含应用所有的常量、include、枚举、全局变量
#pragma once
//包含
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QPalette>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QMoveEvent>
#include <QPainter>
#include <QApplication>
#include <QIcon>
#include <QTimer>
#include <QLayout>
#include <QScreen>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


//常量
const int STD_SCR_WIDTH = 1366; //标准屏幕宽度(为了标题栏缩放)
const QString SETTINGS_FILE_NAME = "settings.txt";
const QString TIMETABLE_FILE_NAME = "timetable.json";
const short APP_VERSION = 2;

namespace DialogDefines {
const short STD_TITLE_HEIGHT = 25;    //标准标题栏高度
const short STD_MAX_WIDTH = 400;    //标准最大宽度
}
namespace DefaultSettings {
const double DEF_SIZE = 0.125;
const bool DEF_DO_AUTO_ALIGN = true;
const short TIMER_INTERVAL = 10;    //计时器更新频率（很长一段时间内将为常量）
}

//枚举
enum class LogType {info, warning, error};
enum class SideBarType {left, right};
enum class TimeEventAction {showMessage, shutDown, restart, show, hide, exit, null};
