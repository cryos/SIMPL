/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "DataArraySelectionWidget.h"

#include <QtCore/QMimeData>
#include <QtCore/QList>
#include <QtCore/QMetaProperty>
#include <QtCore/QSignalMapper>
#include <QtGui/QPainter>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QAction>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMenu>

#include "SIMPLib/Common/AbstractFilter.h"
#include "SIMPLib/DataContainers/DataArrayPath.h"
#include "SIMPLib/FilterParameters/FilterParameter.h"

#include "SVWidgetsLib/Core/SVWidgetsLibConstants.h"
#include "SVWidgetsLib/QtSupport/QtSStyles.h"
#include "SVWidgetsLib/Widgets/DataContainerArrayWidget.h"

#include "FilterParameterWidgetUtils.hpp"
#include "FilterParameterWidgetsDialogs.h"

// Include the MOC generated file for this class
#include "moc_DataArraySelectionWidget.cpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionWidget::DataArraySelectionWidget(FilterParameter* parameter, AbstractFilter* filter, QWidget* parent)
: FilterParameterWidget(parameter, filter, parent)
, m_DidCausePreflight(false)
{
  m_FilterParameter = dynamic_cast<DataArraySelectionFilterParameter*>(parameter);
  Q_ASSERT_X(m_FilterParameter != nullptr, "NULL Pointer", "DataArraySelectionWidget can ONLY be used with a DataArraySelectionFilterParameter object");

  setupUi(this);
  setupGui();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionWidget::DataArraySelectionWidget(QWidget* parent)
: FilterParameterWidget(nullptr, nullptr, parent)
, m_DidCausePreflight(false)
{
  setupUi(this);
  setupGui();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionWidget::~DataArraySelectionWidget()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::initializeWidget(FilterParameter* parameter, AbstractFilter* filter)
{
  setFilter(filter);
  setFilterParameter(parameter);
  setupGui();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::setupGui()
{
  // Sanity Check the filter and the filter parameter
  if(getFilter() == nullptr)
  {
    return;
  }
  if(getFilterParameter() == nullptr)
  {
    return;
  }

  // m_SelectedDataArrayPath->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));

  // Generate the text for the QLabel
  label->setText(getFilterParameter()->getHumanLabel());

  m_MenuMapper = new QSignalMapper(this);
  connect(m_MenuMapper, SIGNAL(mapped(QString)), this, SLOT(dataArraySelected(QString)));

  // Lastly, hook up the filter's signals and slots to our own signals and slots
  // Catch when the filter is about to execute the preflight
  connect(getFilter(), SIGNAL(preflightAboutToExecute()), this, SLOT(beforePreflight()));

  // Catch when the filter is finished running the preflight
  connect(getFilter(), SIGNAL(preflightExecuted()), this, SLOT(afterPreflight()));

  // Catch when the filter wants its values updated
  connect(getFilter(), SIGNAL(updateFilterParameters(AbstractFilter*)), this, SLOT(filterNeedsInputParameters(AbstractFilter*)));

  DataArrayPath defaultPath = getFilter()->property(PROPERTY_NAME_AS_CHAR).value<DataArrayPath>();
  //m_SelectedDataArrayPath->setText(defaultPath.serialize(Detail::Delimiter));

  dcLabel->setText(defaultPath.getDataContainerName());
  amLabel->setText(defaultPath.getAttributeMatrixName());
  daLabel->setText(defaultPath.getDataArrayName());

//  setStyleSheet(dcLabel, QColor(0, 77, 245));
//  setStyleSheet(amLabel, QColor(0, 142, 30));
//  setStyleSheet(daLabel, QColor(215, 104, 0));

//  dcLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//  amLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//  daLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::setStyleSheet2(QLabel* label, QColor color)
{
  QFont font;
  font.setBold(true);
  font.setItalic(true);
  font.setWeight(QFont::Bold);
  font.setStyleStrategy(QFont::PreferAntialias);
  font.setFamily(QtSStyles::GetUIFont());

  QString fontString;
  QTextStream in(&fontString);

#if defined(Q_OS_MAC)
  font.setPointSize(12);
#elif defined(Q_OS_WIN)
  font.setPointSize(10);
#else
  font.setPointSize(10);
  in << "font-weight:bold;";
#endif

  in << "font: " << font.weight() << " " << font.pointSize() << "pt \"" << font.family()  << "\";";
  QString str;
  QTextStream ss(&str);
  ss << "QLabel {\n";
  ss << " background-color: rgb(" << color.name(QColor::HexRgb) << ");\n";
  ss << fontString;
  ss << "}";
  label->setStyleSheet(str);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::createSelectionMenu()
{

  // Now get the DataContainerArray from the Filter instance
  // We are going to use this to get all the current DataContainers
  DataContainerArray::Pointer dca = getFilter()->getDataContainerArray();
  if(nullptr == dca.get())
  {
    return;
  }

  // Get the menu and clear it out
  QMenu* menu = m_SelectedDataArrayPath->menu();
  if(!menu)
  {
    menu = new QMenu();
    m_SelectedDataArrayPath->setMenu(menu);
    menu->installEventFilter(this);
  }
  if(menu)
  {
    menu->clear();
  }

  // Get the DataContainerArray object
  // Loop over the data containers until we find the proper data container
  QList<DataContainer::Pointer> containers = dca->getDataContainers();
  QVector<QString> daTypes = m_FilterParameter->getDefaultAttributeArrayTypes();
  QVector<QVector<size_t>> cDims = m_FilterParameter->getDefaultComponentDimensions();
  QVector<AttributeMatrix::Type> amTypes = m_FilterParameter->getDefaultAttributeMatrixTypes();
  IGeometry::Types geomTypes = m_FilterParameter->getDefaultGeometryTypes();

  QListIterator<DataContainer::Pointer> containerIter(containers);
  while(containerIter.hasNext())
  {
    DataContainer::Pointer dc = containerIter.next();

    IGeometry::Pointer geom = IGeometry::NullPointer();
    IGeometry::Type geomType = IGeometry::Type::Unknown;
    if(nullptr != dc.get())
    {
      geom = dc->getGeometry();
    }
    if(nullptr != geom.get())
    {
      geomType = geom->getGeometryType();
    }

    QMenu* dcMenu = new QMenu(dc->getName());
    dcMenu->setDisabled(false);
    menu->addMenu(dcMenu);
    if(geomTypes.isEmpty() == false && geomTypes.contains(geomType) == false)
    {
      dcMenu->setDisabled(true);
    }
    if (dc->getAttributeMatrixNames().size() == 0)
    {
      dcMenu->setDisabled(true);
    }

    bool validAmFound = false;

    // We found the proper Data Container, now populate the AttributeMatrix List
    DataContainer::AttributeMatrixMap_t attrMats = dc->getAttributeMatrices();
    QMapIterator<QString, AttributeMatrix::Pointer> attrMatsIter(attrMats);
    while(attrMatsIter.hasNext())
    {
      attrMatsIter.next();
      QString amName = attrMatsIter.key();
      AttributeMatrix::Pointer am = attrMatsIter.value();

      QMenu* amMenu = new QMenu(amName);
      dcMenu->addMenu(amMenu);

      if(nullptr != am.get() && amTypes.isEmpty() == false && amTypes.contains(am->getType()) == false)
      {
        amMenu->setDisabled(true);
      }

      bool validDaFound = false;

      // We found the selected AttributeMatrix, so loop over this attribute matrix arrays and populate the menus
      QList<QString> attrArrayNames = am->getAttributeArrayNames();
      QListIterator<QString> dataArraysIter(attrArrayNames);
      while(dataArraysIter.hasNext())
      {
        QString attrArrayName = dataArraysIter.next();
        IDataArray::Pointer da = am->getAttributeArray(attrArrayName);
        QAction* action = new QAction(attrArrayName, amMenu);
        DataArrayPath daPath(dc->getName(), amName, attrArrayName);
        QString path = daPath.serialize(Detail::Delimiter);
        action->setData(path);

        connect(action, SIGNAL(triggered(bool)), m_MenuMapper, SLOT(map()));
        m_MenuMapper->setMapping(action, path);
        amMenu->addAction(action);

        bool daIsNotNull = (nullptr != da.get()) ? true : false;
        bool daValidType = (daTypes.isEmpty() == false && daTypes.contains(da->getTypeAsString()) == false) ? true : false;
        bool daValidDims = (cDims.isEmpty() == false && cDims.contains(da->getComponentDimensions()) == false) ? true : false;

        if(daIsNotNull && (daValidType || daValidDims))
        {
          action->setDisabled(true);
        }
        else
        {
          validDaFound = true;
        }
      }

      // Disable AttributeMatrix menu if no valid DataArray found
      if(validDaFound)
      {
        validAmFound = true;
      }
      if(!validAmFound)
      {
        amMenu->setDisabled(true);
      }
    }

    // Disable DataContainer menu if no valid AttributeMatrixes found
    if(!validAmFound)
    {
      dcMenu->setDisabled(true);
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArraySelectionWidget::eventFilter(QObject* obj, QEvent* event)
{
  if(event->type() == QEvent::Show && obj == m_SelectedDataArrayPath->menu())
  {
    QPoint pos = adjustedMenuPosition(m_SelectedDataArrayPath);
    m_SelectedDataArrayPath->menu()->move(pos);
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::dataArraySelected(QString path)
{
  setSelectedPath(path);

  m_DidCausePreflight = true;
  emit parametersChanged();
  m_DidCausePreflight = false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::setSelectedPath(QString path)
{
  DataArrayPath daPath = DataArrayPath::Deserialize(path, Detail::Delimiter);
  setSelectedPath(daPath);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::setSelectedPath(DataArrayPath daPath)
{
  if(daPath.isEmpty())
  {
    m_SelectedDataArrayPath->setToolTip(wrapStringInHtml("DataArrayPath is empty."));
    //// m_SelectedDataArrayPath->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//    dcLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//    amLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//    daLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
    return;
  }

  DataContainerArray::Pointer dca = getFilter()->getDataContainerArray();
  if(nullptr == dca.get())
  {
    //m_SelectedDataArrayPath->setText(daPath.serialize(Detail::Delimiter));
    //// m_SelectedDataArrayPath->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
    m_SelectedDataArrayPath->setText("");
    dcLabel->setText(daPath.getDataContainerName());
    amLabel->setText(daPath.getAttributeMatrixName());
    daLabel->setText(daPath.getDataArrayName());

//    dcLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//    amLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
//    daLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));

    m_SelectedDataArrayPath->setToolTip(wrapStringInHtml("DataContainerArray is not available to verify path."));
    return;
  }

  if(dca->doesAttributeArrayExist(daPath))
  {
    AttributeMatrix::Pointer attMat = dca->getAttributeMatrix(daPath);
    IDataArray::Pointer attrArray = attMat->getAttributeArray(daPath.getDataArrayName());
    QString html = attrArray->getInfoString(SIMPL::HtmlFormat);
    m_SelectedDataArrayPath->setToolTip(html);
    //m_SelectedDataArrayPath->setText(daPath.serialize(Detail::Delimiter));
    m_SelectedDataArrayPath->setText("");
    //// m_SelectedDataArrayPath->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(true));


    dcLabel->setText(daPath.getDataContainerName());
    amLabel->setText(daPath.getAttributeMatrixName());
    daLabel->setText(daPath.getDataArrayName());

//    dcLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(true));
//    amLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(true));
//    daLabel->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(true));


    dcLabel->setToolTip(dca->getDataContainer(daPath.getDataContainerName())->getInfoString(SIMPL::HtmlFormat));
    amLabel->setToolTip(attMat->getInfoString(SIMPL::HtmlFormat));
    daLabel->setToolTip(html);

  }
  else
  {
    m_SelectedDataArrayPath->setToolTip(wrapStringInHtml("DataArrayPath does not exist."));
    // m_SelectedDataArrayPath->setStyleSheet(QtSStyles::QToolSelectionButtonStyle(false));
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString DataArraySelectionWidget::checkStringValues(QString curDcName, QString filtDcName)
{
  ////qDebug() << "    checkStringValues(...)" << curDcName << "  " << filtDcName;
  if(curDcName.isEmpty() == true && filtDcName.isEmpty() == false)
  {
    return filtDcName;
  }
  else if(curDcName.isEmpty() == false && filtDcName.isEmpty() == true)
  {
    return curDcName;
  }
  else if(curDcName.isEmpty() == false && filtDcName.isEmpty() == false && m_DidCausePreflight == true)
  {
    return curDcName;
  }

  return filtDcName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::beforePreflight()
{
  if(nullptr == getFilter())
  {
    return;
  }
  if(m_DidCausePreflight == true)
  {
    // std::cout << "***  DataArraySelectionWidget already caused a preflight, just returning" << std::endl;
    return;
  }

  createSelectionMenu();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::afterPreflight()
{
  DataArrayPath path(dcLabel->text(), amLabel->text(), daLabel->text());
  //DataArrayPath daPath = DataArrayPath::Deserialize(m_SelectedDataArrayPath->text(), Detail::Delimiter);
  setSelectedPath(path);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::filterNeedsInputParameters(AbstractFilter* filter)
{
  // Generate the path to the AttributeArray
//  DataArrayPath selectedPath = DataArrayPath::Deserialize(m_SelectedDataArrayPath->text(), Detail::Delimiter);
//  QString dc = selectedPath.getDataContainerName();
//  QString am = selectedPath.getAttributeMatrixName();
//  QString da = selectedPath.getDataArrayName();

  DataArrayPath path(dcLabel->text(), amLabel->text(), daLabel->text());
  QVariant var;
  var.setValue(path);
  bool ok = false;
  // Set the value into the Filter
  ok = filter->setProperty(PROPERTY_NAME_AS_CHAR, var);
  if(false == ok)
  {
    FilterParameterWidgetsDialogs::ShowCouldNotSetFilterParameter(getFilter(), getFilterParameter());
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::changeStyleSheet(int style)
{
  QString styleSheet;
  QTextStream ss(&styleSheet);

  ss << "QFrame {";
#if 0
#if defined(Q_OS_WIN)
  ss << "font: italic 9 pt \"" << QtSStyles::GetUIFont() << "\";";
#elif defined(Q_OS_MAC)
  ss << "font: italic 12 pt \"" << QtSStyles::GetUIFont() << "\";";
#else
  ss << "font: italic 10 pt \"" << QtSStyles::GetUIFont() << "\";";
#endif
#endif

  if(style == FS_STANDARD_STYLE)
  {
  }
  else if(style == FS_DRAGGING_STYLE)
  {
    ss << "border: 2px solid rgb(34, 120, 46);";
    ss << "border-radius: 10px;";
  }
  else if(style == FS_DOESNOTEXIST_STYLE)
  {
    ss << "color: rgb(200, 50, 50); font: bold;";
  }
  else if(style == FS_WARNING_STYLE)
  {
    ss << "color: rgb(255, 140, 0); font: bold;";
  }

  ss << "}";

  ss << "QLabel#label { border: 0px solid rgb(255, 120, 46); }";

  setStyleSheet(styleSheet);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::dragEnterEvent(QDragEnterEvent* event)
{
  qDebug() << "DataArraySelectionWidget::dragEnterEvent";
  changeStyleSheet(FS_DRAGGING_STYLE);
  event->acceptProposedAction();

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
  qDebug() << "DataArraySelectionWidget::dragLeaveEvent";
  changeStyleSheet(FS_STANDARD_STYLE);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionWidget::dropEvent(QDropEvent* event)
{
  qDebug() << "DataArraySelectionWidget::dropEvent";
  if(event->mimeData()->hasText())
  {
    QByteArray dropData = event->mimeData()->data("text/plain");
    QString name(dropData);
    qDebug() << name;
  }
  changeStyleSheet(FS_STANDARD_STYLE);

}
