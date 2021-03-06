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

#ifndef _phasetypeselectionfilterparameter_h_
#define _phasetypeselectionfilterparameter_h_

#include <QtCore/QJsonObject>

#include "SIMPLib/DataContainers/AttributeMatrix.h"
#include "SIMPLib/DataContainers/DataArrayPath.h"
#include "SIMPLib/FilterParameters/FilterParameter.h"
#include "SIMPLib/Geometry/IGeometry.h"

// FP: Documentation incomplete because there isn't currently a way to instantiate this filter parameter
//     in one line.
/**
* @brief SIMPL_NEW_PHASETYPE_SELECTION_FP This macro is a short-form way of instantiating an instance of
* PhaseTypeSelectionFilterParameter. There are 8 required parameters and 1 optional parameter
* that are always passed to this macro in the following order: HumanLabel, PropertyName, Category,
* FilterName (class name), PhaseTypesArrayName, PhaseTypeCountProperty, AttributeMatrixProperty, GroupIndex (optional).
*/
#define SIMPL_NEW_PHASETYPE_SELECTION_FP(...)                                                                                                                                                          \
  SIMPL_EXPAND(_FP_GET_OVERRIDE(__VA_ARGS__, SIMPL_NEW_FP_9, SIMPL_NEW_FP_8, SIMPL_NEW_FP_7, SIMPL_NEW_FP_6, SIMPL_NEW_FP_5, SIMPL_NEW_FP_4)(PhaseTypeSelectionFilterParameter, __VA_ARGS__))

/**
* @brief The PhaseTypeSelectionFilterParameter class is used by filters to instantiate an PhaseTypeSelectionWidget.  By instantiating an instance of
* this class in a filter's setupFilterParameters() method, a PhaseTypeSelectionWidget will appear in the filter's "filter input" section in the DREAM3D GUI.
*/
class SIMPLib_EXPORT PhaseTypeSelectionFilterParameter : public FilterParameter
{
public:
  SIMPL_SHARED_POINTERS(PhaseTypeSelectionFilterParameter)
  SIMPL_STATIC_NEW_MACRO(PhaseTypeSelectionFilterParameter)
  SIMPL_TYPE_MACRO_SUPER(PhaseTypeSelectionFilterParameter, FilterParameter)

  typedef std::function<void(UInt32Vector_t)> SetterCallbackType;
  typedef std::function<UInt32Vector_t(void)> GetterCallbackType;

  /**
  * @brief New This function instantiates an instance of the PhaseTypeSelectionFilterParameter. Although this function is available to be used,
  * the preferable way to instantiate an instance of this class is to use the SIMPL_NEW_PHASETYPE_SELECTION_FP(...) macro at the top of this file.

  * @param humanLabel The name that the users of DREAM.3D see for this filter parameter
  * @param propertyName The internal property name for this filter parameter.
  * @param defaultValue The value that this filter parameter will be initialized to by default.
  * @param category The category for the filter parameter in the DREAM.3D user interface.  There
  * are three categories: Parameter, Required Arrays, and Created Arrays.
  * @param setterCallback The method in the AbstractFilter subclass that <i>sets</i> the value of the property
  * that this FilterParameter subclass represents.
  * @param getterCallback The method in the AbstractFilter subclass that <i>gets</i> the value of the property
  * that this FilterParameter subclass represents.
  * @param PhaseTypesArrayName
  * @param phaseTypeCountProperty
  * @param attributeMatrixProperty
  * @param phaseListChoices
  * @param groupIndex Integer that specifies the group that this filter parameter will be placed in.
  * @return
  */
  static Pointer New(const QString& humanLabel, const QString& phaseTypeDataProperty, const DataArrayPath attributeMatrixDefault, Category category, SetterCallbackType setterCallback,
                     GetterCallbackType getterCallback, const QString& PhaseTypesArrayName, const QString& phaseTypeCountProperty, const QString& attributeMatrixProperty,
                     const QStringList phaseListChoices, int groupIndex = -1);

  virtual ~PhaseTypeSelectionFilterParameter();

  SIMPL_INSTANCE_PROPERTY(QString, PhaseTypeCountProperty)
  SIMPL_INSTANCE_PROPERTY(QString, PhaseTypeDataProperty)
  SIMPL_INSTANCE_PROPERTY(QString, AttributeMatrixPathProperty)
  SIMPL_INSTANCE_PROPERTY(DataArrayPath, AttributeMatrixPathDefault)
  SIMPL_INSTANCE_PROPERTY(QStringList, PhaseListChoices)

  /**
  * @brief getWidgetType Returns the type of widget that displays and controls
  * this FilterParameter subclass
  * @return
  */
  QString getWidgetType();

  /**
  * @brief readJson Reads this filter parameter's corresponding property out of a QJsonObject.
  * @param json The QJsonObject that the filter parameter reads from.
  */
  void readJson(const QJsonObject& json);

  /**
  * @brief writeJson Writes this filter parameter's corresponding property to a QJsonObject.
  * @param json The QJsonObject that the filter parameter writes to.
  */
  void writeJson(QJsonObject& json);

  SIMPL_INSTANCE_PROPERTY(IGeometry::Types, DefaultGeometryTypes)
  SIMPL_INSTANCE_PROPERTY(AttributeMatrix::Types, DefaultAttributeMatrixTypes)

  /**
  * @param SetterCallback The method in the AbstractFilter subclass that <i>sets</i> the value of the property
  * that this FilterParameter subclass represents.
  * @return The SetterCallback
  */
  SIMPL_INSTANCE_PROPERTY(SetterCallbackType, SetterCallback)

  /**
  * @param GetterCallback The method in the AbstractFilter subclass that <i>gets</i> the value of the property
  * that this FilterParameter subclass represents.
  * @return The GetterCallback
  */
  SIMPL_INSTANCE_PROPERTY(GetterCallbackType, GetterCallback)

protected:
  /**
  * @brief PhaseTypeSelectionFilterParameter The default constructor.  It is protected because this
  * filter parameter should only be instantiated using its New(...) function or short-form macro.
  */
  PhaseTypeSelectionFilterParameter();

private:
  PhaseTypeSelectionFilterParameter(const PhaseTypeSelectionFilterParameter&); // Copy Constructor Not Implemented
  void operator=(const PhaseTypeSelectionFilterParameter&);                    // Operator '=' Not Implemented
};

#endif /* _PhaseTypeSelectionFilterParameter_H_ */
