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

#include "DataArraySelectionFilterParameter.h"
#include "SIMPLib/Common/Constants.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionFilterParameter::DataArraySelectionFilterParameter()
: FilterParameter()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionFilterParameter::~DataArraySelectionFilterParameter()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionFilterParameter::Pointer DataArraySelectionFilterParameter::New(const QString& humanLabel, const QString& propertyName, const DataArrayPath& defaultValue, Category category,
                                                                                  SetterCallbackType setterCallback, GetterCallbackType getterCallback, const RequirementType req, int groupIndex)
{

  DataArraySelectionFilterParameter::Pointer ptr = DataArraySelectionFilterParameter::New();
  ptr->setHumanLabel(humanLabel);
  ptr->setPropertyName(propertyName);
  QVariant v;
  v.setValue(defaultValue);
  ptr->setDefaultValue(v);
  ptr->setCategory(category);
  ptr->setDefaultGeometryTypes(req.dcGeometryTypes);
  ptr->setDefaultAttributeMatrixTypes(req.amTypes);
  ptr->setDefaultAttributeArrayTypes(req.daTypes);
  ptr->setDefaultComponentDimensions(req.componentDimensions);
  ptr->setGroupIndex(groupIndex);
  ptr->setSetterCallback(setterCallback);
  ptr->setGetterCallback(getterCallback);

  return ptr;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString DataArraySelectionFilterParameter::getWidgetType()
{
  return QString("DataArraySelectionWidget");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionFilterParameter::RequirementType DataArraySelectionFilterParameter::CreateCategoryRequirement(const QString& primitiveType, size_t allowedCompDim,
                                                                                                                unsigned int attributeMatrixCategory)
{
  typedef QVector<size_t> QVectorOfSizeType;
  DataArraySelectionFilterParameter::RequirementType req;
  QVector<unsigned int> amTypes;
  if(attributeMatrixCategory == SIMPL::AttributeMatrixObjectType::Element)
  {
    amTypes.push_back(SIMPL::AttributeMatrixType::Cell);
    amTypes.push_back(SIMPL::AttributeMatrixType::Face);
    amTypes.push_back(SIMPL::AttributeMatrixType::Edge);
    amTypes.push_back(SIMPL::AttributeMatrixType::Vertex);
  }
  else if(attributeMatrixCategory == SIMPL::AttributeMatrixObjectType::Feature)
  {
    amTypes.push_back(SIMPL::AttributeMatrixType::CellFeature);
    amTypes.push_back(SIMPL::AttributeMatrixType::FaceFeature);
    amTypes.push_back(SIMPL::AttributeMatrixType::EdgeFeature);
    amTypes.push_back(SIMPL::AttributeMatrixType::VertexFeature);
  }
  else if(attributeMatrixCategory == SIMPL::AttributeMatrixObjectType::Ensemble)
  {
    amTypes.push_back(SIMPL::AttributeMatrixType::CellEnsemble);
    amTypes.push_back(SIMPL::AttributeMatrixType::FaceEnsemble);
    amTypes.push_back(SIMPL::AttributeMatrixType::EdgeEnsemble);
    amTypes.push_back(SIMPL::AttributeMatrixType::VertexEnsemble);
  }
  req.amTypes = amTypes;
  if(primitiveType.compare(SIMPL::Defaults::AnyPrimitive) != 0)
  {
    req.daTypes = QVector<QString>(1, primitiveType);
  }
  if(SIMPL::Defaults::AnyComponentSize != allowedCompDim)
  {
    req.componentDimensions = QVector<QVectorOfSizeType>(1, QVectorOfSizeType(1, allowedCompDim));
  }
  //  if(SIMPL::GeometryType::UnknownGeometry != geometryType)
  //  {
  //    req.dcGeometryTypes = QVector<unsigned int>(1, geometryType);
  //  }
  return req;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArraySelectionFilterParameter::RequirementType DataArraySelectionFilterParameter::CreateRequirement(const QString& primitiveType, size_t allowedCompDim, unsigned int attributeMatrixType,
                                                                                                        unsigned int geometryType)
{
  typedef QVector<size_t> QVectorOfSizeType;
  DataArraySelectionFilterParameter::RequirementType req;
  if(primitiveType.compare(SIMPL::Defaults::AnyPrimitive) != 0)
  {
    req.daTypes = QVector<QString>(1, primitiveType);
  }
  if(SIMPL::Defaults::AnyComponentSize != allowedCompDim)
  {
    req.componentDimensions = QVector<QVectorOfSizeType>(1, QVectorOfSizeType(1, allowedCompDim));
  }
  if(SIMPL::Defaults::AnyAttributeMatrix != attributeMatrixType)
  {
    QVector<unsigned int> amTypes(1, attributeMatrixType);
    req.amTypes = amTypes;
  }
  if(SIMPL::Defaults::AnyGeometry != geometryType)
  {
    req.dcGeometryTypes = QVector<unsigned int>(1, geometryType);
  }
  return req;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionFilterParameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[getPropertyName()];
  if(!jsonValue.isUndefined())
  {
    QJsonObject obj = jsonValue.toObject();
    DataArrayPath dap;
    dap.readJson(obj);
    m_SetterCallback(dap);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArraySelectionFilterParameter::writeJson(QJsonObject& json)
{
  DataArrayPath dap = m_GetterCallback();
  QJsonObject obj;
  dap.writeJson(obj);
  json[getPropertyName()] = obj;
}
