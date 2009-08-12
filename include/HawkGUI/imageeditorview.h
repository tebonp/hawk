#ifndef _IMAGEEDITORVIEW_H_
#define _IMAGEEDITORVIEW_H_
#if defined __cplusplus || defined Q_MOC_RUN

#include "imageview.h"
#include <spimage.h>

#include <QPointF>
class QMouseEvent;

typedef enum{EditorDefaultMode = 0,EditorBlurMode = 1} EditorMode;

class ImageEditorView: public ImageView
{
  Q_OBJECT
    Q_PROPERTY(QPointF HawkImage_imageCenter READ imageCenter WRITE setImageCenter)
  Q_PROPERTY(QSize HawkImage_imageSize READ imageSize WRITE setImageSize)
    Q_PROPERTY(QSize HawkImage_pixelSize READ pixelSize WRITE setPixelSize)
  Q_PROPERTY(bool HawkImage_phased READ phased WRITE setPhased)
  Q_PROPERTY(bool HawkImage_scaled READ scaled WRITE setScaled)
  Q_PROPERTY(bool HawkImage_shifted READ shifted WRITE setShifted)
  Q_PROPERTY(double HawkImage_detectorDistance READ detectorDistance WRITE setDetectorDistance)    
  Q_PROPERTY(double HawkImage_wavelength READ wavelength WRITE setWavelength)
    public:
  ImageEditorView(QWidget * parent = 0);
  void setImageCenter(QPointF center);
  QPointF imageCenter() const;
  QSize imageSize() const;
  void setImageSize(QSize imageSize);
  QString propertyNameToDisplayName(QString propertyName);
  bool phased() const;
  void setPhased(bool p);
  bool scaled() const;
  void setScaled(bool p);
  bool shifted() const;
  void setShifted(bool p);
  double wavelength() const;
  void setWavelength(double w);
  double detectorDistance() const;
  void setDetectorDistance(double p);
  QSize pixelSize() const;
  void setPixelSize(QSize pixelSize);
  EditorMode editorMode();
  double getDropBrushRadius();
  double getDropBlurRadius();

 public slots:
  void setBlurMode();
  void setDefaultMode();
  void setDropBrushRadius(double d);
  void setDropBlurRadius(double d);
 protected:
  void mouseReleaseEvent(QMouseEvent * e);
  void mousePressEvent(QMouseEvent * e);
  void mouseMoveEvent(QMouseEvent * e);
  void wheelEvent(QWheelEvent * e);
 private:
  Image * getBlurKernel();
  void generateDropCursor();
  void applyDrop(QPointF pos,Image * image,Image * kernel);
  EditorMode mode;
  double dropBrushRadius;
  double dropBlurRadius;
  QPixmap dropCursor;

};

#else
#error "Someone is including " __FILE__ " from a C file!"
#endif
#endif
