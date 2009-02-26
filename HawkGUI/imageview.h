#ifndef _IMAGEVIEW_H_
#define _IMAGEVIEW_H_ 1
#if defined __cplusplus || defined Q_MOC_RUN

#include <QWidget>
#include <QPointF>
#include <QList>
#include <QGraphicsView>

class ImageItem;
class QGraphicsScene;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class QFocusFrame;
class QMainWindow;
class ImageLoader;

class ImageView: public QGraphicsView
{
  Q_OBJECT
    public:
  ImageView(QWidget * parent = NULL);
  ~ImageView();
  void setImage(ImageItem * item);
  void scaleItems(qreal scale);
  void translateItems(QPointF mov);
  void setup();
  void setAutoUpdate(bool update);  
  bool getAutoUpdate();
  QPointF getPos();
  QTransform getTransform();
  QString getFilename();
  QString scheduledFilename();
  QString currentlyLoadingFilename();
  QString getScheduledFilename();
  void shiftImage();
  void setColormap(int color);
  int colormap();
  void setDisplay(int display);
  int display();
  QString newestFilename();
  QString getCurrentIteration();
  void maxContrast();
  void logScale(bool on);
 public slots:
  void scheduleImageLoad(QString file);
  bool loadImage(QString file);
  void loadImage(QPixmap pix);
  void setPos(QPointF pos);
  void setTransform(QTransform t);
 signals:
  void focusedIn(ImageView * focused);
  void scaleBy(qreal scale);
  void translateBy(QPointF r);
  void imageLoaded(QString file);
 protected:
  void focusInEvent ( QFocusEvent * event );
  void mouseMoveEvent(QMouseEvent * event);
  void wheelEvent ( QWheelEvent * event );
  void mousePressEvent(QMouseEvent * event);
  void mouseReleaseEvent( QMouseEvent * mouseEvent );
  void keyPressEvent ( QKeyEvent * event );
  private slots:
  void finishLoadImage();
  void loadScheduledImage();
 private:
  QPointF mouseLastScenePos;
  QGraphicsScene * graphicsScene;
  ImageItem * dragged;
  QPointF draggedInitialPos;
  QPointF itemsScale;
  ImageItem * imageItem;
  bool mouseInsideImage;
  QFocusFrame * focusFrame;
  QString displayType;
  bool autoUpdate;
  QString filename;
  QString fileToRetry;
  QMainWindow * mainWindow;
  ImageLoader * loader;
  QTimer * delayedLoader;
  QString scheduledImage;
  QString currentlyLoading;
  QString currentIteration;
};

#else
#error "Someone is including " __FILE__ " from a C file!"
#endif
#endif
