#ifndef BOTTOMPANEL_H
#define BOTTOMPANEL_H

#include <QBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QSpinBox>
#include <QTabWidget>
#include <QTreeWidgetItem>
#include <QWidget>

#include "brdfItemTree.h"
#include "brdfItemDialog.h"

class BottomPanel : public QWidget {
    Q_OBJECT
public:
    explicit BottomPanel(QWidget *parent = nullptr);
    ~BottomPanel() override = default;
private:
    QGridLayout *layout;

    QGridLayout *groupBoxLayout;
    QGroupBox *groupBox;

    QTabWidget *tabWidget;

    QWidget *cameraTab;
    QWidget *renderTab;
    QWidget *structureTab;
    QWidget *brdfTab;

    QGridLayout *cameraLayout;
    QGridLayout *renderLayout;
    QGridLayout *structureLayout;
    QGridLayout *brdfLayout;

    QList<BRDF> brdfList;
    QStringList brdfNameList;

    QLabel *cameraCameraPositionLabel;
    QDoubleSpinBox *cameraCameraXPositionSpinBox;
    QDoubleSpinBox *cameraCameraYPositionSpinBox;
    QDoubleSpinBox *cameraCameraZPositionSpinBox;
    QLabel *cameraCameraDirectionLabel;
    QDoubleSpinBox *cameraCameraXDirectionSpinBox;
    QDoubleSpinBox *cameraCameraYDirectionSpinBox;
    QDoubleSpinBox *cameraCameraZDirectionSpinBox;
    QLabel *cameraUpwardDirectionLabel;
    QDoubleSpinBox *cameraUpwardXDirectionSpinBox;
    QDoubleSpinBox *cameraUpwardYDirectionSpinBox;
    QDoubleSpinBox *cameraUpwardZDirectionSpinBox;
    QLabel *cameraHzFOVAngleLabel;
    QDoubleSpinBox *cameraHzFOVAngleSpinBox;
    QLabel *cameraFocalDistanceLabel;
    QDoubleSpinBox *cameraFocalDistanceSpinBox;
    QLabel *cameraLensRadiusLabel;
    QDoubleSpinBox *cameraLensRadiusSpinBox;
    QLabel *cameraResolutionLabel;
    QSpinBox *cameraXResolutionSpinBox;
    QSpinBox *cameraYResolutionSpinBox;
    QLabel *cameraFollowResolutionLabel;
    QCheckBox *cameraFollowResolutionCheckBox;

    QLabel *renderNBouncesLabel;
    QSpinBox *renderNBouncesSpinBox;
    QLabel *renderNRandomSamplesLabel;
    QSpinBox *renderNRandomSamplesSpinBox;
    QLabel *renderThresholdIntersectionDistanceLabel;
    QDoubleSpinBox *renderThresholdIntersectionDistanceSpinBox;
    QLabel *renderThresholdNoIntersectionDistanceLabel;
    QDoubleSpinBox *renderThresholdNoIntersectionDistanceSpinBox;
    QLabel *renderFiniteDifferenceSizeLabel;
    QDoubleSpinBox *renderFiniteDifferenceSizeSpinBox;
    QLabel *renderSupersamplingValueLabel;
    QSpinBox *renderSupersamplingValueSpinBox;
    QLabel *renderIsSilentLabel;
    QCheckBox *renderIsSilentCheckBox;
    QLabel *renderRenderModeLabel;
    QComboBox *renderRenderModeComboBox;
    QPushButton *renderRenderPushButton;

    QLabel *structureFloorBRDFLabel;
    QComboBox *structureFloorBRDFComboBox;
    QLabel *structureCeilingBRDFLabel;
    QComboBox *structureCeilingBRDFComboBox;
    QLabel *structureLeftBRDFLabel;
    QComboBox *structureLeftBRDFComboBox;
    QLabel *structureRightBRDFLabel;
    QComboBox *structureRightBRDFComboBox;
    QLabel *structureBackBRDFLabel;
    QComboBox *structureBackBRDFComboBox;

    BRDFItemTree *brdfTreeWidget;
    QPushButton *brdfAddBRDFPushButton;
    QPushButton *brdfDelBRDFPushButton;
    bool followResolution = false;
    BRDFItemDialog *brdfItemDialog;

    int viewWidth, viewHeight = 0;
public slots:
    void updateList();
    void onRenderListPushButtonPressed();
    void onViewSizeChanged(int, int);
    void toggleFollowResolution(bool);
    void onAddPushButtonPressed();
    void addItem(QTreeWidgetItem *);
    void delItem(int);
};

#endif //BOTTOMPANEL_H
