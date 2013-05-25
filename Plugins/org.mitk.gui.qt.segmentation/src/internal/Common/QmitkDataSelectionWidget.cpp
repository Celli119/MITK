/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "QmitkDataSelectionWidget.h"
#include <berryPlatform.h>
#include <mitkIDataStorageService.h>
#include <mitkImage.h>
#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateProperty.h>
#include <mitkProperties.h>
#include <mitkSurface.h>
#include <QmitkDataStorageComboBox.h>
#include <QLabel>
#include <cassert>

static mitk::NodePredicateBase::Pointer CreatePredicate(QmitkDataSelectionWidget::Predicate predicate)
{
  switch(predicate)
  {
    case QmitkDataSelectionWidget::ImagePredicate:
      return mitk::NodePredicateAnd::New(
        mitk::TNodePredicateDataType<mitk::Image>::New(),
        mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object"))).GetPointer();

    case QmitkDataSelectionWidget::SegmentationPredicate:
      return mitk::NodePredicateAnd::New(
        mitk::NodePredicateProperty::New("binary", mitk::BoolProperty::New(true)),
        mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object"))).GetPointer();

    case QmitkDataSelectionWidget::SurfacePredicate:
      return mitk::NodePredicateAnd::New(
        mitk::TNodePredicateDataType<mitk::Surface>::New(),
        mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object"))).GetPointer();

    default:
      assert(false && "Unknown predefined predicate!");
      return NULL;
  }
}

static mitk::DataStorage::Pointer GetDataStorage()
{
  mitk::IDataStorageService::Pointer service =
    berry::Platform::GetServiceRegistry().GetServiceById<mitk::IDataStorageService>(mitk::IDataStorageService::ID);

  assert(service.IsNotNull());

  return service->GetDefaultDataStorage()->GetDataStorage();
}

QmitkDataSelectionWidget::QmitkDataSelectionWidget(QWidget* parent)
  : QWidget(parent)
{
  m_Controls.setupUi(this);
  m_Controls.helpLabel->hide();
}

QmitkDataSelectionWidget::~QmitkDataSelectionWidget()
{
}

unsigned int QmitkDataSelectionWidget::AddDataStorageComboBox(QmitkDataSelectionWidget::Predicate predicate)
{
  return this->AddDataStorageComboBox("", predicate);
}

unsigned int QmitkDataSelectionWidget::AddDataStorageComboBox(mitk::NodePredicateBase* predicate)
{
  return this->AddDataStorageComboBox("", predicate);
}

unsigned int QmitkDataSelectionWidget::AddDataStorageComboBox(const QString &labelText, QmitkDataSelectionWidget::Predicate predicate)
{
  return this->AddDataStorageComboBox(labelText, CreatePredicate(predicate));
}

unsigned int QmitkDataSelectionWidget::AddDataStorageComboBox(const QString &labelText, mitk::NodePredicateBase* predicate)
{
  int row = m_Controls.gridLayout->rowCount();

  if (!labelText.isEmpty())
  {
    QLabel* label = new QLabel(labelText, m_Controls.dataSelectionWidget);
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    m_Controls.gridLayout->addWidget(label, row, 0);
  }

  QmitkDataStorageComboBox* comboBox = new QmitkDataStorageComboBox(GetDataStorage(), predicate, m_Controls.dataSelectionWidget);
  connect(comboBox, SIGNAL(OnSelectionChanged(const mitk::DataNode *)), this, SLOT(OnSelectionChanged(const mitk::DataNode *)));
  m_Controls.gridLayout->addWidget(comboBox, row, 1);

  return static_cast<unsigned int>(row);
}

mitk::DataNode::Pointer QmitkDataSelectionWidget::GetSelection(unsigned int id)
{
  assert(id < m_Controls.gridLayout->rowCount());

  QWidget* widget = m_Controls.gridLayout->itemAtPosition(id, 1)->widget();
  assert(widget != NULL);

  QmitkDataStorageComboBox* comboBox = dynamic_cast<QmitkDataStorageComboBox*>(widget);
  assert(comboBox != NULL);

  return comboBox->GetSelectedNode();
}

void QmitkDataSelectionWidget::SetHelpText(const QString& text)
{
  if (!text.isEmpty())
  {
    m_Controls.helpLabel->setText(text);

    if (!m_Controls.helpLabel->isVisible())
      m_Controls.helpLabel->show();
  }
  else
  {
    m_Controls.helpLabel->hide();
  }
}

void QmitkDataSelectionWidget::OnSelectionChanged(const mitk::DataNode* selection)
{
  int rowCount = m_Controls.gridLayout->rowCount();

  for (int row = 1; row < rowCount; ++row)
  {
    if (m_Controls.gridLayout->itemAtPosition(row, 1)->widget() == sender())
    {
      emit SelectionChanged(row, selection);
      return;
    }
  }

  assert(false);
}
