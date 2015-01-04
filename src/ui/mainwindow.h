#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSignalMapper>
#include <QModelIndex>
#include <QStringList>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QPoint>
#include <QTimer>
#include <QElapsedTimer>
#include <QTranslator>

#include "gesturehandler.h"
#include "widgets/dimdialog.h"
#include "updatedialog.h"

namespace Ui {
class MainWindow;
}

class BakaEngine;
class MpvHandler;
class Settings;

class MainWindow : public QMainWindow
{
friend class BakaEngine;
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Load(QString f = QString());

protected:
    void LoadSettings();
    void SaveSettings();

    void dragEnterEvent(QDragEnterEvent *event);    // drag file into
    void dropEvent(QDropEvent *event);              // drop file into
    void mousePressEvent(QMouseEvent *event);       // pressed mouse down
    void mouseReleaseEvent(QMouseEvent *event);     // released mouse up
    void mouseMoveEvent(QMouseEvent *event);        // moved mouse on the form
    void mouseDoubleClickEvent(QMouseEvent *event); // double clicked the form
    bool eventFilter(QObject *obj, QEvent *event);  // event filter (get mouse move events from mpvFrame)
    void wheelEvent(QWheelEvent *event);            // the mouse wheel is used
    void keyPressEvent(QKeyEvent *event);
    void SetPlaybackControls(bool enable);          // macro to enable/disable playback controls
    void TogglePlaylist();                          // toggles playlist visibility
    void TogglePlay();                              // play/pause
    void ToggleSubtitles();                         // play/pause
    bool isPlaylistVisible();                       // is the playlist visible?

private slots:
    void FullScreen(bool fs);                       // makes window fullscreen
    void ShowPlaylist(bool visible);                // sets the playlist visibility
    void HideAlbumArt(bool hide);                   // hides the album art
    void FitWindow(int percent, bool msg = false);  // fit the window the the specified percent
    void SetAspectRatio(QString aspect);            // set the aspect ratio to specified proportions
    void DimLights(bool dim);                       // grays out the rest of the screen with LightDialog
    void TakeScreenshot(bool subs);                 // take a screenshot
    void ShowScreenshotMessage(bool subs);          // show the screenshot status message
    void UpdateRecentFiles();                       // populate recentFiles menu
    void OpenFile();                                // open file dialog

private:
    Ui::MainWindow  *ui;
    BakaEngine      *baka;

    Settings        *settings;
    MpvHandler      *mpv;
    GestureHandler  *gesture;
    QTranslator     *translator     = nullptr,
                    *qtTranslator   = nullptr;

    bool            pathChanged,
                    menuVisible,
                    firstItem       = false,
                    init            = false;
    QTimer          *autohide       = nullptr;

    QSystemTrayIcon *sysTrayIcon;
    QMenu           *trayIconMenu;
    DimDialog       *dimDialog;
    UpdateDialog    *updateDialog;

    // variables
    QStringList recent;
    QString lang,
            onTop;
    int autoFit,
        maxRecent;
    bool hidePopup,
         remaining,
         screenshotDialog,
         debug,
         gestures;

public slots:
    void setLang(QString s)          { emit langChanged(lang = s); }
    void setOnTop(QString s)         { emit onTopChanged(onTop = s); }
    void setAutoFit(int b)           { emit autoFitChanged(autoFit = b); }
    void setHidePopup(bool b)        { emit hidePopupChanged(hidePopup = b); }
    void setRemaining(bool b)        { emit remainingChanged(remaining = b); }
    void setScreenshotDialog(bool b) { emit screenshotDialogChanged(screenshotDialog = b); }
    void setDebug(bool b)            { emit debugChanged(debug = b); }
signals:
    void langChanged(QString);
    void onTopChanged(QString);
    void autoFitChanged(int);
    void hidePopupChanged(bool);
    void remainingChanged(bool);
    void screenshotDialogChanged(bool);
    void debugChanged(bool);
};

#endif // MAINWINDOW_H
