#include "globals.h"

//全局变量
Settings* settings;
QSize scrSize;
QIcon appIcon;
QFile* logFile;
BackgroundWidget* bck;
TimeEventManager* evMgr;
SideBar* sideBar;
TimeWidget* timeWid;
SettingsWidget* settingsWid;

//全局函数
//写日志
void write_log(const QString &text)
{
    QString tmp = "[";
	tmp.append(QTime::currentTime().toString() + '.' + QString::number(QTime::currentTime().msec()));
    tmp.append("] ").append(text).append('\n');
    logFile->open(QFile::ReadWrite | QFile::Append);
    logFile->write(tmp.toUtf8());
    logFile->close();
}

//画圆角
void round_corner(QWidget* wid, QColor col)
{
    QPainter ptr(wid);

    ptr.setRenderHint(QPainter::Antialiasing);
    QPen pen(QColor(160, 160, 160));
    QBrush brush(col);
    ptr.setPen(pen);
    ptr.setBrush(brush);
    ptr.drawRoundedRect(wid->rect(), 10, 10);
}

//缩放
QSize scale(const QSize origin)
{
	double rate = (double)scrSize.width() / (double)STD_SCR_WIDTH;
	return origin * rate;
}
int scale(const int origin)
{
	double rate = (double)scrSize.width() / (double)STD_SCR_WIDTH;
	return origin * rate;
}
