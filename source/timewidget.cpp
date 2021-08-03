#include "timewidget.h"
#include "ui_timewidget.h"

TimeWidget::TimeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TimeWidget)
{
    ui->setupUi(this);

    //初始化变量
    settings->write_log("正在初始化时间表");
    evMgr = new TimeEventManager;
    evMgr->connect_events(this);

    //以下3行将会修改
    scrWid = scrSize.width();
    scrHei = scrSize.height();
    settings->write_log(QString("成功获取屏幕宽高:")+ QString::number(scrWid) + ", " + QString::number(scrHei));

    movable = false;
    settings->write_log("设置为不可移动");

    fstPos = QPoint();
    curTime = QTime();

    mainTimer = new QTimer(this);
    settings->write_log("计时器已创建");

    bck = new BackgroundWidget(scrWid, scrHei);

    sideBar = nullptr;

    trayIcon = nullptr;
    actionExit = new QAction("退出");
    actionShow = new QAction("显示主界面");
    actionHide = new QAction("隐藏");
    trayMenu = new QMenu(this);
    settings->write_log("系统托盘相关变量初始化完成");

    //窗口效果
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    settings->write_log("主窗口特效设置完毕");

    //设置界面元素显示效果
    ui->timeLabel->setStyleSheet("color:#E0E0E0");
    ui->currentLabel->setStyleSheet("color:#F7F7F7");
    ui->eventLabel->setStyleSheet("color:yellow");
    settings->write_log("字体颜色设置完毕");

    //移动及改变大小
    move(0, 0);
    resize(scrWid * settings->size(), scrHei * settings->size());
    settings->write_log("主窗口大小及位置初始化完毕");

    //处理侧边栏
    sideBar = new SideBar(size(), this);

    //处理计时器
    mainTimer->setInterval(settings->timerInterval());
    mainTimer->start();
    settings->write_log("计时器已开启");

    //创建托盘图标
    add_tray_icon();

    //关联信号和槽
    connect(mainTimer, &QTimer::timeout, this, &TimeWidget::on_mainTimer_timeOut);
    connect(bck, &BackgroundWidget::stpMoving, this, &TimeWidget::on_bck_stpMoving);
    connect(sideBar, &SideBar::signalHide, this, &TimeWidget::slotHide);
    connect(actionShow, &QAction::triggered, this, &TimeWidget::slotShow);
    connect(actionExit, &QAction::triggered, this, &TimeWidget::slotExit);
    connect(actionHide, &QAction::triggered, this, &TimeWidget::slotHide);
    settings->write_log("信号和槽关联成功，初始化结束");

    actionShow->trigger();
}

//创建系统托盘图标
void TimeWidget::add_tray_icon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(APP_ICON);
    trayIcon->setToolTip("时间显示器");

    //创建右键菜单
    trayMenu->addAction(actionShow);
    trayMenu->addAction(actionHide);
    trayMenu->addSeparator();
    trayMenu->addAction(actionExit);
    trayIcon->setContextMenu(trayMenu);
    settings->write_log("托盘右键菜单设置成功");

    trayIcon->show();
    settings->write_log("系统托盘图标创建成功");

    //测试
    trayIcon->showMessage("A Test", "测试消息", APP_ICON);
}

//从托盘中唤起
void TimeWidget::slotShow()
{
    show();
    actionShow->setDisabled(true);
    actionHide->setEnabled(true);
    settings->write_log("主界面已显示");
}

//最小化
void TimeWidget::slotHide()
{
    movable = false;
    hide();
    bck->hide();
    sideBar->hide();
    actionShow->setEnabled(true);
    actionHide->setDisabled(true);
    settings->write_log("已最小化");
}


//关机槽函数
void TimeWidget::slotShutDown()
{
    settings->write_log("关机事件触发");
    system("shutdown -s -t 600");
}

//重启槽函数
void TimeWidget::slotRestart()
{
    settings->write_log("重启事件触发");
    system("shutdown -r -t 600");
}

//显示消息槽函数
void TimeWidget::slotShowMessage(QString msg)
{
    trayIcon->showMessage("来自\"TimeShower\"的消息", msg, APP_ICON);
    settings->write_log("已显示消息\"" + msg + "\"");
}

//退出槽函数
void TimeWidget::slotExit()
{
    settings->write_log("退出事件触发");
    delete trayIcon;
    delete trayMenu;
    delete sideBar;
    delete bck;
    QApplication::quit();
}

void TimeWidget::mousePressEvent(QMouseEvent* e)
{
    if(movable)
    {
        fstPos = e->globalPosition().toPoint();
        settings->write_log("鼠标按下");
    }
}

void TimeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(movable)
    {
        QPoint dP = e->globalPosition().toPoint() - fstPos;
        move(pos() + dP);
        fstPos = e->globalPosition().toPoint();
    }
}

void TimeWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    if(!movable)
    {
        sideBar->show();
        bck->show();
    }
}

void TimeWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if(!bck->isHidden())
    {
        movable = true;
        //自动对齐
        if(settings->doAutoAlign())
        {
            auto_align(e->globalPosition().toPoint());
        }

        //调整侧边栏位置
        if(x() + width() + sideBar->width() > scrWid)
        {
            sideBar->setType(SideBarType::left);
        }
        else if(x() - sideBar->width() < 0)
        {
            sideBar->setType(SideBarType::right);
        }
        sideBar->auto_move(pos(), size());
    }
}

void TimeWidget::moveEvent(QMoveEvent* e)
{
    Q_UNUSED(e);

    if(sideBar != nullptr)
    {
        //移动侧边栏
        sideBar->auto_move(pos(), size());
    }
}

void TimeWidget::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    //绘制背景
    QPixmap tmp(":/resources/background.png");
    painter.setOpacity(0.3);
    painter.drawPixmap(QRect(0, 0, width(), height()), tmp);
}

void TimeWidget::on_mainTimer_timeOut()
{
    mainTimer->start();
    curTime = QTime::currentTime();
    ui->timeLabel->setText(curTime.toString());
    evMgr->trigger();
}

void TimeWidget::on_bck_stpMoving()
{
    bck->hide();
    sideBar->hide();
    movable = false;
    settings->write_log("接收到停止移动信号，移动结束");
}


//自动对齐
void TimeWidget::auto_align(QPoint pos)
{
    //获取网格宽度和高度
    double gridWid = scrWid * settings->size();
    double gridHei = scrHei * settings->size();

    int gridX = pos.x() / gridWid;
    int gridY = pos.y() / gridHei;
    move(width() * gridX, height() * gridY);
    settings->write_log("已自动对齐至网格");
}

TimeWidget::~TimeWidget()
{
    delete ui;
    settings->write_log("主窗口被析构");
}
