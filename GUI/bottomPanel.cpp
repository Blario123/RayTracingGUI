#include "bottomPanel.h"

BottomPanel::BottomPanel(QWidget *parent) : QWidget(parent),
                                            layout(new QGridLayout),
                                            groupBoxLayout(new QGridLayout),
                                            groupBox(new QGroupBox("BottomPanel")),
                                            tabWidget(new QTabWidget),
                                            cameraTab(new QWidget),
                                            renderTab(new QWidget),
                                            structureTab(new QWidget),
                                            brdfTab(new QWidget),
                                            cameraLayout(new QGridLayout),
                                            renderLayout(new QGridLayout),
                                            structureLayout(new QGridLayout),
                                            brdfLayout(new QGridLayout),
                                            cameraCameraPositionLabel(new QLabel("Camera Position")),
                                            cameraCameraXPositionSpinBox(new QDoubleSpinBox),
                                            cameraCameraYPositionSpinBox(new QDoubleSpinBox),
                                            cameraCameraZPositionSpinBox(new QDoubleSpinBox),
                                            cameraCameraDirectionLabel(new QLabel("Camera Direction")),
                                            cameraCameraXDirectionSpinBox(new QDoubleSpinBox),
                                            cameraCameraYDirectionSpinBox(new QDoubleSpinBox),
                                            cameraCameraZDirectionSpinBox(new QDoubleSpinBox),
                                            cameraUpwardDirectionLabel(new QLabel("Upward Direction")),
                                            cameraUpwardXDirectionSpinBox(new QDoubleSpinBox),
                                            cameraUpwardYDirectionSpinBox(new QDoubleSpinBox),
                                            cameraUpwardZDirectionSpinBox(new QDoubleSpinBox),
                                            cameraHzFOVAngleLabel(new QLabel("Horizontal FOV Angle")),
                                            cameraHzFOVAngleSpinBox(new QDoubleSpinBox),
                                            cameraFocalDistanceLabel(new QLabel("Focal Distance")),
                                            cameraFocalDistanceSpinBox(new QDoubleSpinBox),
                                            cameraLensRadiusLabel(new QLabel("Lens Radius")),
                                            cameraLensRadiusSpinBox(new QDoubleSpinBox),
                                            cameraResolutionLabel(new QLabel("Camera Resolution")),
                                            cameraXResolutionSpinBox(new QSpinBox),
                                            cameraYResolutionSpinBox(new QSpinBox),
                                            cameraFollowResolutionLabel(new QLabel("Use window resolution?")),
                                            cameraFollowResolutionCheckBox(new QCheckBox),
                                            renderNBouncesLabel(new QLabel("Number of Bounces")),
                                            renderNBouncesSpinBox(new QSpinBox),
                                            renderNRandomSamplesLabel(new QLabel("Number of Random Samples")),
                                            renderNRandomSamplesSpinBox(new QSpinBox),
                                            renderThresholdIntersectionDistanceLabel(new QLabel("Threshold Intersection Distance")),
                                            renderThresholdIntersectionDistanceSpinBox(new QDoubleSpinBox),
                                            renderThresholdNoIntersectionDistanceLabel(new QLabel("Threshold No Intersection Distance")),
                                            renderThresholdNoIntersectionDistanceSpinBox(new  QDoubleSpinBox),
                                            renderFiniteDifferenceSizeLabel(new QLabel("Finite Difference Size")),
                                            renderFiniteDifferenceSizeSpinBox(new QDoubleSpinBox),
                                            renderSupersamplingValueLabel(new QLabel("Supersampling Value")),
                                            renderSupersamplingValueSpinBox(new QSpinBox),
                                            renderIsSilentLabel(new QLabel("Silent Render?")),
                                            renderIsSilentCheckBox(new QCheckBox),
                                            renderRenderModeLabel(new QLabel("Render Mode")),
                                            renderRenderModeComboBox(new QComboBox),
                                            renderRenderPushButton(new QPushButton("Render")),
                                            structureFloorBRDFLabel(new QLabel("Floor")),
                                            structureFloorBRDFComboBox(new QComboBox),
                                            structureCeilingBRDFLabel(new QLabel("Ceiling")),
                                            structureCeilingBRDFComboBox(new QComboBox),
                                            structureLeftBRDFLabel(new QLabel("Left")),
                                            structureLeftBRDFComboBox(new QComboBox),
                                            structureRightBRDFLabel(new QLabel("Right")),
                                            structureRightBRDFComboBox(new QComboBox),
                                            structureBackBRDFLabel(new QLabel("Back")),
                                            structureBackBRDFComboBox(new QComboBox),
                                            brdfTreeWidget(new BRDFItemTree),
                                            brdfAddBRDFPushButton(new QPushButton("Add")),
                                            brdfDelBRDFPushButton(new QPushButton("Delete")),
                                            brdfItemDialog(new BRDFItemDialog)
                                            {
    viewWidth = screen()->size().width() / 2;
    viewHeight = screen()->size().height() / 2;

    cameraCameraXPositionSpinBox->setValue(0.0);
    cameraCameraYPositionSpinBox->setValue(0.0);
    cameraCameraZPositionSpinBox->setValue(1.0);

    cameraCameraXDirectionSpinBox->setValue(1.0);
    cameraCameraYDirectionSpinBox->setValue(0.0);
    cameraCameraZDirectionSpinBox->setValue(0.0);

    cameraUpwardXDirectionSpinBox->setValue(0.0);
    cameraUpwardYDirectionSpinBox->setValue(0.0);
    cameraUpwardZDirectionSpinBox->setValue(1.0);

    cameraHzFOVAngleSpinBox->setValue(M_PI / 2.5);

    cameraLensRadiusSpinBox->setValue(0.0);

    cameraXResolutionSpinBox->setRange(1, 10000);
    cameraXResolutionSpinBox->setValue(viewWidth);
    cameraYResolutionSpinBox->setRange(1, 10000);
    cameraYResolutionSpinBox->setValue(viewHeight);

    brdfTreeWidget->setList(brdfList);
    brdfTreeWidget->setFixedHeight(100);

    updateList();

    renderRenderModeComboBox->addItems(QStringList() << "RenderImage" <<  "RenderImagePerThread" << "RenderImageMultithreaded" << "RenderImageRussian" << "RenderImageRussianPerThread" << "RenderImageRussianMultithreaded");

    structureFloorBRDFComboBox->addItems(brdfNameList);
    structureFloorBRDFComboBox->setCurrentIndex(2);
    structureCeilingBRDFComboBox->addItems(brdfNameList);
    structureCeilingBRDFComboBox->setCurrentIndex(2);
    structureLeftBRDFComboBox->addItems(brdfNameList);
    structureLeftBRDFComboBox->setCurrentIndex(0);
    structureRightBRDFComboBox->addItems(brdfNameList);
    structureRightBRDFComboBox->setCurrentIndex(1);
    structureBackBRDFComboBox->addItems(brdfNameList);
    structureBackBRDFComboBox->setCurrentIndex(2);

    renderNBouncesSpinBox->setValue(10);
    renderNRandomSamplesSpinBox->setValue(10);
    renderThresholdIntersectionDistanceSpinBox->setRange(0, 1);
    renderThresholdIntersectionDistanceSpinBox->setDecimals(9);
    renderThresholdIntersectionDistanceSpinBox->setValue(1.0e-8);
    renderThresholdNoIntersectionDistanceSpinBox->setRange(0, 200);
    renderThresholdNoIntersectionDistanceSpinBox->setDecimals(3);
    renderThresholdNoIntersectionDistanceSpinBox->setValue(100.0);
    renderFiniteDifferenceSizeSpinBox->setRange(0, 1);
    renderFiniteDifferenceSizeSpinBox->setDecimals(9);
    renderFiniteDifferenceSizeSpinBox->setValue(1.0e-8);

    cameraLayout->addWidget(cameraCameraPositionLabel, 0, 0);
    cameraLayout->addWidget(cameraCameraXPositionSpinBox, 1, 0);
    cameraLayout->addWidget(cameraCameraYPositionSpinBox, 2, 0);
    cameraLayout->addWidget(cameraCameraZPositionSpinBox, 3, 0);
    cameraLayout->addWidget(cameraCameraDirectionLabel, 0, 1);
    cameraLayout->addWidget(cameraCameraXDirectionSpinBox, 1, 1);
    cameraLayout->addWidget(cameraCameraYDirectionSpinBox, 2, 1);
    cameraLayout->addWidget(cameraCameraZDirectionSpinBox, 3, 1);
    cameraLayout->addWidget(cameraUpwardDirectionLabel, 0, 2);
    cameraLayout->addWidget(cameraUpwardXDirectionSpinBox, 1, 2);
    cameraLayout->addWidget(cameraUpwardYDirectionSpinBox, 2, 2);
    cameraLayout->addWidget(cameraUpwardZDirectionSpinBox, 3, 2);
    cameraLayout->addWidget(cameraHzFOVAngleLabel, 0, 3);
    cameraLayout->addWidget(cameraHzFOVAngleSpinBox, 1, 3);
    cameraLayout->addWidget(cameraFocalDistanceLabel, 0, 4);
    cameraLayout->addWidget(cameraFocalDistanceSpinBox, 1, 4);
    cameraLayout->addWidget(cameraLensRadiusLabel, 2, 4);
    cameraLayout->addWidget(cameraLensRadiusSpinBox, 3, 4);
    cameraLayout->addWidget(cameraResolutionLabel, 0, 5, 1, 2);
    cameraLayout->addWidget(cameraXResolutionSpinBox, 1, 5, 1, 2);
    cameraLayout->addWidget(cameraYResolutionSpinBox, 2, 5, 1, 2);
    cameraLayout->addWidget(cameraFollowResolutionLabel, 3, 5);
    cameraLayout->addWidget(cameraFollowResolutionCheckBox, 3, 6);

    renderLayout->addWidget(renderNBouncesLabel, 0, 0);
    renderLayout->addWidget(renderNBouncesSpinBox, 1, 0);
    renderLayout->addWidget(renderNRandomSamplesLabel, 2, 0);
    renderLayout->addWidget(renderNRandomSamplesSpinBox, 3, 0);
    renderLayout->addWidget(renderThresholdIntersectionDistanceLabel, 0, 1);
    renderLayout->addWidget(renderThresholdIntersectionDistanceSpinBox, 1, 1);
    renderLayout->addWidget(renderThresholdNoIntersectionDistanceLabel, 2, 1);
    renderLayout->addWidget(renderThresholdNoIntersectionDistanceSpinBox, 3, 1);
    renderLayout->addWidget(renderFiniteDifferenceSizeLabel, 0, 2);
    renderLayout->addWidget(renderFiniteDifferenceSizeSpinBox, 1, 2 );
    renderLayout->addWidget(renderSupersamplingValueLabel, 2, 2);
    renderLayout->addWidget(renderSupersamplingValueSpinBox, 3, 2);
    renderLayout->addWidget(renderRenderModeLabel, 0, 3, 1, 2);
    renderLayout->addWidget(renderRenderModeComboBox, 1, 3, 1, 2);
    renderLayout->addWidget(renderIsSilentLabel, 2, 3, 1, 2);
    renderLayout->addWidget(renderIsSilentCheckBox, 3, 3);
    renderLayout->addWidget(renderRenderPushButton, 3, 4);

    brdfLayout->addWidget(brdfTreeWidget, 0, 0, 1, 2);
    brdfLayout->addWidget(brdfAddBRDFPushButton, 1, 0);
    brdfLayout->addWidget(brdfDelBRDFPushButton, 1, 1);

    structureLayout->addWidget(structureFloorBRDFLabel, 0, 0);
    structureLayout->addWidget(structureFloorBRDFComboBox, 1, 0);
    structureLayout->addWidget(structureCeilingBRDFLabel, 2, 0);
    structureLayout->addWidget(structureCeilingBRDFComboBox, 3, 0);
    structureLayout->addWidget(structureLeftBRDFLabel, 0, 1);
    structureLayout->addWidget(structureLeftBRDFComboBox, 1, 1);
    structureLayout->addWidget(structureRightBRDFLabel, 2, 1);
    structureLayout->addWidget(structureRightBRDFComboBox, 3, 1);
    structureLayout->addWidget(structureBackBRDFLabel, 0, 2);
    structureLayout->addWidget(structureBackBRDFComboBox, 1, 2);

    cameraTab->setLayout(cameraLayout);
    structureTab->setLayout(structureLayout);
    brdfTab->setLayout(brdfLayout);
    renderTab->setLayout(renderLayout);

    tabWidget->addTab(cameraTab, "Camera");
    tabWidget->addTab(structureTab, "Structure");
    tabWidget->addTab(brdfTab, "BRDF");
    tabWidget->addTab(renderTab, "Render");

    groupBoxLayout->addWidget(tabWidget);
    groupBox->setLayout(groupBoxLayout);

    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(groupBox);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Preferred,  QSizePolicy::Fixed);

    connect(renderRenderPushButton, &QPushButton::pressed, this, &BottomPanel::onRenderListPushButtonPressed);
    connect(cameraFollowResolutionCheckBox, &QCheckBox::toggled, this, &BottomPanel::toggleFollowResolution);
    connect(brdfAddBRDFPushButton, &QPushButton::pressed, this, &BottomPanel::onAddPushButtonPressed);
    connect(brdfDelBRDFPushButton, &QPushButton::pressed, brdfTreeWidget, &BRDFItemTree::delItem);
    connect(brdfTreeWidget, &BRDFItemTree::deleteAt, this, &BottomPanel::delItem);

}

void BottomPanel::onRenderListPushButtonPressed() {

}

void BottomPanel::onViewSizeChanged(int w, int h) {
    if(followResolution) {
        cameraXResolutionSpinBox->setValue(w);
        cameraYResolutionSpinBox->setValue(h);
    }
}

void BottomPanel::toggleFollowResolution(bool state) {
    followResolution = state;
}

void BottomPanel::onAddPushButtonPressed() {
    brdfItemDialog = new BRDFItemDialog;
    connect(brdfItemDialog, &BRDFItemDialog::itemAdded, this, &BottomPanel::addItem);
    connect(this, &BottomPanel::destroyed, brdfItemDialog, &BRDFItemDialog::deleteLater);
    brdfItemDialog->show();
}

void BottomPanel::addItem(QTreeWidgetItem *item) {
    BRDF tempItem(item->data(1, 0).toDouble(), item->data(2, 0).toDouble(), item->data(3, 0).toDouble(), item->data(0, 0).toString());
    brdfList << tempItem;
    brdfTreeWidget->addItem(item);
    updateList();
}

void BottomPanel::delItem(int index) {
    brdfList.removeAt(index);
    updateList();
}

void BottomPanel::updateList() {
    brdfNameList.clear();
    if(brdfLayout->count()) {
        for(auto & i: brdfList) {
            brdfNameList << i.name();
        }
    }
    QList<QComboBox*> comboBoxList = structureTab->findChildren<QComboBox*>();
    for(QList<QComboBox*>::iterator i = comboBoxList.begin(); i != comboBoxList.end(); i++) {
        i.operator*()->clear();
        i.operator*()->addItems(brdfNameList);
    }
}
