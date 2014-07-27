#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recentfilesupervisor.h"
#include "cdtattributedockwidget.h"
#include "cdtdockwidget.h"
#include "log4qt/logger.h"

namespace Ui {
class MainWindow;
}
class QToolButton;
class QModelIndex;
class QTreeView;
class CDTSampleDockWidget;
class CDTExtractionDockWidget;
class CDTLayerInfoWidget;
class CDTUndoWidget;
class DialogConsole;
class CDTProjectWidget;
class QgsMapCanvas;
struct QUuid;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
    friend class RecentFileSupervisor;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();       

private:
    void initDockWidgets();

    /// onCurrentProjectChanged
    /// onProjectClosed
    /// onLayerChanged
    void registerDocks(Qt::DockWidgetArea area, CDTDockWidget* dock);

public:
    static MainWindow               *getMainWindow();
    static QTreeView                *getProjectTreeView();
    static CDTSampleDockWidget      *getSampleDockWidget();
    static CDTAttributeDockWidget   *getAttributesDockWidget();
    static CDTExtractionDockWidget  *getExtractionDockWidget();
    static CDTUndoWidget            *getUndoWidget();
    static CDTLayerInfoWidget       *getLayerInfoWidget();
    static CDTProjectWidget         *getCurrentProjectWidget();
    static QgsMapCanvas             *getCurrentMapCanvas();

signals:
    void loadSetting();
    void updateSetting();
    void beforeProjectClosed(CDTProject*);
public slots:
    void onCurrentTabChanged(int i);

private slots:
    void on_action_New_triggered();
    void on_treeViewProject_customContextMenuRequested(const QPoint &pos);
    void on_treeViewProject_clicked(const QModelIndex &index);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_All_triggered();
    void on_action_Save_As_triggered();
    void onRecentFileTriggered();

protected:
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    CDTAttributeDockWidget  *dockWidgetAttributes;
    CDTSampleDockWidget     *dockWidgetSample;
    CDTExtractionDockWidget *dockWidgetExtraction;
    CDTUndoWidget           *dockWidgetUndo;
    CDTLayerInfoWidget      *dockWidgetLayerInfo;

    RecentFileSupervisor *supervisor;
    int recentFileCount;
    QToolButton* recentFileToolButton;
    QStringList recentFilePaths;
    DialogConsole* dialogConsole;

    QList<CDTDockWidget*> docks;
    static MainWindow* mainWindow;
    static bool isLocked;
};

#endif // MAINWINDOW_H
