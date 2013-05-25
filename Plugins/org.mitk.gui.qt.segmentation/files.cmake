set(SRC_CPP_FILES
  QmitkSegmentationPreferencePage.cpp
)

set(INTERNAL_CPP_FILES
  mitkPluginActivator.cpp
  QmitkSegmentationView.cpp
  QmitkSegmentationPostProcessing.cpp
  QmitkThresholdAction.cpp
  QmitkCreatePolygonModelAction.cpp
  QmitkStatisticsAction.cpp
  QmitkAutocropAction.cpp
  QmitkBooleanOperationsView.cpp
  QmitkDeformableClippingPlaneView.cpp
  regiongrowing/QmitkRegionGrowingView.cpp
  QmitkOtsuAction.cpp
  QmitkSegmentationUtilitiesView.cpp
  Common/QmitkDataSelectionWidget.cpp
  SegmentationUtilities/QmitkSegmentationUtilities2View.cpp
  SegmentationUtilities/BooleanOperations/QmitkBooleanOperationsWidget.cpp
  SegmentationUtilities/ImageMasking/QmitkImageMaskingWidget.cpp
  SegmentationUtilities/MorphologicalOperations/QmitkMorphologicalOperationsWidget.cpp
)

set(UI_FILES
  src/internal/QmitkSegmentationControls.ui
  src/internal/QmitkBooleanOperationsView.ui
  src/internal/QmitkDeformableClippingPlaneViewControls.ui
  src/internal/regiongrowing/QmitkRegionGrowingViewControls.ui
  src/internal/QmitkSegmentationUtilitiesViewControls.ui
  src/internal/Common/QmitkDataSelectionWidgetControls.ui
  src/internal/SegmentationUtilities/QmitkSegmentationUtilities2ViewControls.ui
  src/internal/SegmentationUtilities/BooleanOperations/QmitkBooleanOperationsWidgetControls.ui
  src/internal/SegmentationUtilities/ImageMasking/QmitkImageMaskingWidgetControls.ui
  src/internal/SegmentationUtilities/MorphologicalOperations/QmitkMorphologicalOperationsWidgetControls.ui
)

set(MOC_H_FILES
  src/QmitkSegmentationPreferencePage.h
  src/internal/mitkPluginActivator.h
  src/internal/QmitkSegmentationView.h
  src/internal/QmitkSegmentationPostProcessing.h
  src/internal/QmitkThresholdAction.h
  src/internal/QmitkCreatePolygonModelAction.h
  src/internal/QmitkStatisticsAction.h
  src/internal/QmitkAutocropAction.h
  src/internal/QmitkBooleanOperationsView.h
  src/internal/QmitkDeformableClippingPlaneView.h
  src/internal/regiongrowing/QmitkRegionGrowingView.h
  src/internal/QmitkOtsuAction.h
  src/internal/QmitkSegmentationUtilitiesView.h
  src/internal/Common/QmitkDataSelectionWidget.h
  src/internal/SegmentationUtilities/QmitkSegmentationUtilities2View.h
  src/internal/SegmentationUtilities/BooleanOperations/QmitkBooleanOperationsWidget.h
  src/internal/SegmentationUtilities/ImageMasking/QmitkImageMaskingWidget.h
  src/internal/SegmentationUtilities/MorphologicalOperations/QmitkMorphologicalOperationsWidget.h
)

set(CACHED_RESOURCE_FILES
  resources/segmentation.png
  resources/boolean.png
  resources/deformablePlane.png
  resources/regiongrowing.xpm
  resources/segmentationUtilities.png
  resources/SegmentationUtilities_48x48.png
  plugin.xml
)

set(QRC_FILES
  resources/segmentation.qrc
  resources/boolean.qrc
  resources/regiongrowing.qrc
  resources/utilities.qrc
  resources/SegmentationUtilities2.qrc
)

set(CPP_FILES)

foreach(file ${SRC_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
