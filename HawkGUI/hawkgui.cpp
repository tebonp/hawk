#include <QtGui>

#include "hawkgui.h"
#include "geometrycontrol.h"
#include "imagedisplay.h"
#include "optionstree.h"
#include "processdisplay.h"
#include "processcontrol.h"
#include "imagecategory.h"
#include "imageview.h"
#include "plotdisplay.h"

HawkGUI::HawkGUI()
  :QMainWindow()
{
  createCategories();
  createGUI();
  createControls();
  connectGUIToControls();
  resize(1024,768);
}

HawkGUI::~HawkGUI(){
  int size = imageCategories.size();
  for(int i = 0;i<size;i++){
    delete imageCategories.at(i);
  }
}

void HawkGUI::createGUI(){

  QSplitter * splitter = new QSplitter(Qt::Horizontal,this);
  setCentralWidget(splitter);

  QWidget * leftPanel = createLeftPanel();
  QWidget * rightPanel = createRightPanel();
  
  splitter->addWidget(leftPanel);
  splitter->addWidget(rightPanel);
  splitter->setStretchFactor (0,0);
  splitter->setStretchFactor (1,1);

  createActions();
  createToolBars();
  createStatusBar();
}

QWidget * HawkGUI::createLeftPanel(){
  QWidget * leftPanel = new QWidget(this);
  
  /* Build left panel */
  //  optionsTree = new QLabel("Options Tree",centralWidget());
  optionsTree = new OptionsTree(this);
  //  processButtons = new QLabel("processButtons",centralWidget());
  processDisplay = new ProcessDisplay(this);
  
  QVBoxLayout *vlayout = new QVBoxLayout;
  vlayout->addWidget(optionsTree);
  vlayout->addWidget(processDisplay);
  
  leftPanel->setLayout(vlayout);
  return leftPanel;
}

QWidget * HawkGUI::createRightPanel(){
  imageDisplay = new ImageDisplay(this);
  imageDisplay->setImageCategories(&imageCategories);
  //  plotDisplay = new QLabel("Plot Display",centralWidget());
  plotDisplay = new PlotDisplay(this);
  /*    PlotDisplay::DatasetId id = plotDisplay->createDataset("Test");
    if(plotDisplay->appendData(id,1,1)){
    qDebug("Failled to append data");
  }
  if(plotDisplay->appendData(id,2,10)){
    qDebug("Failled to append data");
    }*/
  
  QSplitter * rightPanel = new QSplitter(Qt::Vertical,centralWidget());
  rightPanel->addWidget(imageDisplay);
  rightPanel->addWidget(plotDisplay);
  return rightPanel;
}


void HawkGUI::createToolBars(){
  processToolBar = addToolBar(tr("Process"));
  processToolBar->addAction(runProcess);
  processToolBar->addAction(deleteOutput);
  processToolBar->setIconSize(QSize(32,32));
  plotToolBar = addToolBar(tr("Plot"));
  plotToolBar->addAction(loadLog);
  plotToolBar->setIconSize(QSize(32,32));

  imageDisplayToolBar = addToolBar(tr("Image Display"));
  // Make decent sized icons
  QWidget * stretcher = new QWidget(imageDisplayToolBar);
  stretcher->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred));
  imageDisplayToolBar->addWidget(stretcher);
  imageDisplayToolBar->setIconSize(QSize(32,32));
  imageDisplayToolBar->addAction(lockTransformation);
  imageDisplayToolBar->addAction(lockBrowse);
  imageDisplayToolBar->addAction(autoUpdateView);
  imageDisplayToolBar->addSeparator();
  imageDisplayToolBar->addAction(loadImage);
  imageDisplayToolBar->addAction(shiftImage);
  imageDisplayToolBar->addAction(maxContrastImage);
  imageDisplayToolBar->addAction(logScaleImage);

  displayBox = new QComboBox;  
  displayBox->addItem("Amplitudes",0);
  displayBox->addItem("Phases",COLOR_PHASE);
  displayBox->addItem("Mask",COLOR_MASK);

  stretcher = new QWidget(imageDisplayToolBar);
  stretcher->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred));
  imageDisplayToolBar->addWidget(displayBox);
  
  /*  
      imageDisplayToolBar->addAction(displayAmplitudes);
      imageDisplayToolBar->addAction(displayPhases);
      imageDisplayToolBar->addAction(displayMask);
  */
      
  colorBox = new QComboBox;
  colorBox->addItem("Gray",COLOR_GRAYSCALE);
  colorBox->addItem("Jet",COLOR_JET);
  colorBox->addItem("Hot",COLOR_HOT);
  colorBox->addItem("Rainbow",COLOR_RAINBOW);
  colorBox->addItem("Traditional",COLOR_TRADITIONAL);
  colorBox->addItem("Wheel",COLOR_WHEEL);

  imageDisplayToolBar->addWidget(colorBox);

  imageDisplayToolBar->addWidget(stretcher);

    /*
  imageDisplayToolBar->addAction(colorGray);
  imageDisplayToolBar->addAction(colorJet);

  imageDisplayToolBar->addAction(colorHot);
  imageDisplayToolBar->addAction(colorRainbow);
  imageDisplayToolBar->addAction(colorTraditional);
  imageDisplayToolBar->addAction(colorWheel);
    */

}

void HawkGUI::createStatusBar(){
  statusBar()->showMessage(tr("Ready"));
}

void HawkGUI::createActions(){
  lockTransformation = new QAction(QIcon(":/images/lock_zoom.png"), tr("&Lock Transformation"), this);
  lockTransformation->setStatusTip(tr("Translates and zooms all images as one."));

  lockTransformation->setCheckable(true);

  lockTransformation->setChecked(true);
  imageDisplay->setLockedTransformation(true);
  
  connect(lockTransformation,SIGNAL(toggled(bool)),this,SLOT(onLockTransformationToggled(bool)));


  lockBrowse = new QAction(QIcon(":/images/lock_browse.png"), tr("&Lock Browse"), this);
  lockBrowse->setStatusTip(tr("Keep all images in the same iteration."));

  lockBrowse->setCheckable(true);
  connect(lockBrowse,SIGNAL(toggled(bool)),this,SLOT(onLockBrowseToggled(bool)));
  lockBrowse->setChecked(true);  

  autoUpdateView = new QAction(QIcon(":images/image_autoupdate.png"),tr("&Auto Reload"), this);
  autoUpdateView->setStatusTip(tr("Automatically loads the last image created."));
  autoUpdateView->setCheckable(true);
  connect(autoUpdateView,SIGNAL(toggled(bool)),imageDisplay,SLOT(setAutoUpdate(bool)));
  autoUpdateView->setChecked(true);


  loadImage = new QAction(QIcon(":images/image_open.png"),tr("&Load Image"), this);
  loadImage->setStatusTip(tr("Load image file."));
  connect(loadImage,SIGNAL(triggered(bool)),imageDisplay,SLOT(loadUserSelectedImage()));
  shiftImage = new QAction(QIcon(":images/image_shift.png"),tr("&Shift Image"), this);
  shiftImage->setStatusTip(tr("Shifts the quadrants of the selected image."));
  connect(shiftImage,SIGNAL(triggered(bool)),imageDisplay,SLOT(shiftSelectedImage()));
  maxContrastImage = new QAction(QIcon(":images/bricontrast.png"),tr("&Maximize Contrast"), this);
  maxContrastImage->setStatusTip(tr("Maximizes the contrast of the selected image."));
  connect(maxContrastImage,SIGNAL(triggered(bool)),imageDisplay,SLOT(maxContrastSelectedImage()));
  logScaleImage = new QAction(QIcon(":images/log_scale.png"),tr("&Log Scale"), this);
  logScaleImage->setStatusTip(tr("Toggles log scale on the selected image."));
  logScaleImage->setCheckable(true);
  connect(logScaleImage,SIGNAL(toggled(bool)),imageDisplay,SLOT(logScaleSelectedImage(bool)));

  displayGroup = new QActionGroup(this);
  displayAmplitudes = new QAction(tr("&Amplitudes"), this);
  displayAmplitudes->setCheckable(true);
  displayAmplitudes->setChecked(true);
  displayPhases = new QAction(tr("&Phases"), this);
  displayPhases->setCheckable(true);
  displayMask = new QAction(tr("&Mask"), this);
  displayMask->setCheckable(true);
  displayGroup->addAction(displayAmplitudes);
  displayGroup->addAction(displayPhases);
  displayGroup->addAction(displayMask);


  colorGroup = new QActionGroup(this);
  colorGray = new QAction(tr("Gray"),this);
  colorGray->setCheckable(true);
  colorGroup->addAction(colorGray);
  colorJet = new QAction(tr("Jet"),this);
  colorJet->setCheckable(true);
  colorJet->setChecked(true);
  colorGroup->addAction(colorJet);
  colorHot = new QAction(tr("Hot"),this);
  colorHot->setCheckable(true);
  colorGroup->addAction(colorHot);
  colorRainbow = new QAction(tr("Rainbow"),this);
  colorRainbow->setCheckable(true);
  colorGroup->addAction(colorRainbow);
  colorTraditional = new QAction(tr("Traditional"),this);
  colorTraditional->setCheckable(true);
  colorGroup->addAction(colorTraditional);
  colorWheel = new QAction(tr("Wheel"),this);
  colorWheel->setCheckable(true);
  colorGroup->addAction(colorWheel);


  loadLog = new QAction(QIcon(":images/log_open.png"),tr("&Load Log"), this);
  loadLog->setStatusTip(tr("Load log file."));
  connect(loadLog,SIGNAL(triggered(bool)),plotDisplay,SLOT(loadUserSelectedLogFile()));

  runProcess = new QAction(QIcon(":/images/exec.png"),tr("&Run"), this);
  runProcess->setCheckable(true);
  runProcess->setStatusTip(tr("Start reconstruction."));
  deleteOutput = new QAction(QIcon(":images/image_delete.png"),tr("&Delete Output"), this);
  deleteOutput->setStatusTip(tr("Delete output images from a directory."));

} 


void HawkGUI::createControls(){
  processControl = new ProcessControl(this);
}

void HawkGUI::connectGUIToControls(){
  connect(processDisplay,SIGNAL(runButtonToggled(bool)),runProcess,SLOT(setChecked(bool)));
  connect(runProcess,SIGNAL(toggled(bool)),this,SLOT(onRunProcessToggled(bool)));
  connect(optionsTree,SIGNAL(optionsTreeUpdated(Options *)),processControl,SLOT(setOptions(Options *)));
  connect(processControl,SIGNAL(processFinished()),this,SLOT(onProcessFinished()));
  connect(processControl,SIGNAL(processStarted(QString,QString,ProcessControl *)),imageDisplay,SLOT(onProcessStarted(QString,QString,ProcessControl *)));
  connect(processControl,SIGNAL(processStarted(QString,QString,ProcessControl *)),plotDisplay,SLOT(onProcessStarted(QString,QString,ProcessControl *)));

  connect(imageDisplay,SIGNAL(focusedViewChanged(ImageView *)),this,SLOT(onFocusedViewChanged(ImageView *)));

  connect(deleteOutput,SIGNAL(triggered()),this,SLOT(onDeleteOutputTriggered()));

  connect(displayAmplitudes,SIGNAL(triggered()),imageDisplay,SLOT(displayAmplitudes()));
  connect(displayPhases,SIGNAL(triggered()),imageDisplay,SLOT(displayPhases()));
  connect(displayMask,SIGNAL(triggered()),imageDisplay,SLOT(displayMask()));
  
  connect(colorGray,SIGNAL(triggered()),imageDisplay,SLOT(setColorGray()));
  connect(colorJet,SIGNAL(triggered()),imageDisplay,SLOT(setColorJet()));
  connect(colorHot,SIGNAL(triggered()),imageDisplay,SLOT(setColorHot()));
  connect(colorWheel,SIGNAL(triggered()),imageDisplay,SLOT(setColorWheel()));
  connect(colorRainbow,SIGNAL(triggered()),imageDisplay,SLOT(setColorRainbow()));
  connect(colorTraditional,SIGNAL(triggered()),imageDisplay,SLOT(setColorTraditional()));

  connect(colorBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onColorBoxChanged(int)));
  connect(displayBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onDisplayBoxChanged(int)));
  // force initial signal
  optionsTree->rebuildTree();
}


void HawkGUI::createCategories(){
  imageCategories.append(new ImageCategory("Calculated Pattern","pattern"));
  imageCategories.append(new ImageCategory("Object","real_out"));
  //  imageCategories.append(new ImageCategory("Phase Image","real_out_phase"));
  imageCategories.append(new ImageCategory("Support","support"));
  imageCategories.append(new ImageCategory("Experimental Pattern","amplitudes"));
  imageCategories.append(new ImageCategory("Autocorrelation","autocorrelation",false));
}

void HawkGUI::onFocusedViewChanged(ImageView * view){
  autoUpdateView->setChecked(view->getAutoUpdate());
  int color = view->colormap();
  int index = colorBox->findData(color);
  if(index >= 0){
    colorBox->setCurrentIndex(index);    
  }
  int display = view->display();
  index = displayBox->findData(display);
  if(index >= 0){
    displayBox->setCurrentIndex(index);    
  }
  if(color & COLOR_GRAYSCALE){
    colorGray->setChecked(true);
  }
  if(color & COLOR_JET){
    colorJet->setChecked(true);
  }
  if(color & COLOR_HOT){
    colorHot->setChecked(true);
  }
  if(color & COLOR_TRADITIONAL){
    colorTraditional->setChecked(true);
  }
  if(color & COLOR_RAINBOW){
    colorRainbow->setChecked(true);
  }
  if(color & COLOR_WHEEL){
    colorWheel->setChecked(true);
  }
  logScaleImage->blockSignals(true);
  if(color & LOG_SCALE){
    logScaleImage->setChecked(true);
  }else{
    logScaleImage->setChecked(false);
  }
  logScaleImage->blockSignals(false);

}


void HawkGUI::onRunProcessToggled(bool toggle){
  if(toggle){
    runProcess->setIcon(QIcon(":/images/stop.png"));
    processControl->startProcess();
  }else{
    runProcess->setIcon(QIcon(":/images/exec.png"));
    processControl->stopProcess();
  }
  processDisplay->toggleRunButton(toggle);
}

void HawkGUI::onProcessFinished(){
  runProcess->setChecked(false);
  imageDisplay->onProcessStopped();
  plotDisplay->onProcessStopped();
}

void HawkGUI::onDeleteOutputTriggered(){
  QString outputDir(processControl->getOptions()->work_dir);
  QString dir = QFileDialog::getExistingDirectory(this,"Delete output from Directory",outputDir,QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
  if(!dir.isEmpty()){
    processControl->deleteOutputFromDir(dir);
  }  
}

void HawkGUI::onColorBoxChanged(int index){
  int color = colorBox->itemData(index).toInt();
  imageDisplay->setColormap(color);
}


void HawkGUI::onDisplayBoxChanged(int index){
  int display = displayBox->itemData(index).toInt();
  imageDisplay->setDisplay(display);
}

void HawkGUI::onLockTransformationToggled(bool on){
  /*  if(on){
    lockTransformation->setIcon(QIcon(":/images/unlock_zoom.png"));
    lockTransformation->setText("Unlock Transformation");
  }else{
    lockTransformation->setIcon(QIcon(":/images/lock_zoom.png"));
  }
  */
  imageDisplay->setLockedTransformation(on);
}

void HawkGUI::onLockBrowseToggled(bool on){
  imageDisplay->setLockedBrowse(on);
}

void HawkGUI::closeEvent(QCloseEvent *event){
  // Check if there are processes running
  if(processControl){
    if(processControl->isRunning()){
      if(QMessageBox::question(this,"Reconstruction Still Running","There is at least one reconstruction still running. Do you really want to exit?",
			       QMessageBox::Yes|QMessageBox::No,QMessageBox::No) != QMessageBox::Yes){
	event->ignore();
	return;
      }
    }
  }
  event->accept();
}

