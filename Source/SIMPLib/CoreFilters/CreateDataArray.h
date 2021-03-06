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


#ifndef _createdataarray_h_
#define _createdataarray_h_

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/AbstractFilter.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/FilterParameters/RangeFilterParameter.h"

/**
 * @brief The CreateDataArray class. See [Filter documentation](@ref createdataarray) for details.
 */
class SIMPLib_EXPORT CreateDataArray : public AbstractFilter
{
    Q_OBJECT
  public:
    SIMPL_SHARED_POINTERS(CreateDataArray)
    SIMPL_STATIC_NEW_MACRO(CreateDataArray)
    SIMPL_TYPE_MACRO_SUPER(CreateDataArray, AbstractFilter)

    virtual ~CreateDataArray();

    enum InitializationChoices
    {
      Manual,
      RandomWithRange
    };

    enum ScalarTypeChoices
    {
      Int8Choice = 0,
      UInt8Choice,
      Int16Choice,
      UInt16Choice,
      Int32Choice,
      UInt32Choice,
      Int64Choice,
      UInt64Choice,
      FloatChoice,
      DoubleChoice,
      BoolChoice
    };

    SIMPL_FILTER_PARAMETER(int, ScalarType)
    Q_PROPERTY(int ScalarType READ getScalarType WRITE setScalarType)

    SIMPL_FILTER_PARAMETER(int, NumberOfComponents)
    Q_PROPERTY(int NumberOfComponents READ getNumberOfComponents WRITE setNumberOfComponents)

    SIMPL_FILTER_PARAMETER(DataArrayPath, NewArray)
    Q_PROPERTY(DataArrayPath NewArray READ getNewArray WRITE setNewArray)

    SIMPL_FILTER_PARAMETER(int, InitializationType)
    Q_PROPERTY(int InitializationType READ getInitializationType WRITE setInitializationType)

    SIMPL_FILTER_PARAMETER(QString, InitializationValue)
    Q_PROPERTY(QString InitializationValue READ getInitializationValue WRITE setInitializationValue)

    SIMPL_FILTER_PARAMETER(FPRangePair, InitializationRange)
    Q_PROPERTY(FPRangePair InitializationRange READ getInitializationRange WRITE setInitializationRange)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getCompiledLibraryName();

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
     */
    virtual const QString getBrandingString();

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    virtual const QString getFilterVersion();

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getGroupName();

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getSubGroupName();

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    virtual const QString getHumanLabel();

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void setupFilterParameters();

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    virtual void execute();

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    virtual void preflight();

  signals:
    /**
     * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
     * be pushed from a user-facing control (such as a widget)
     * @param filter Filter instance pointer
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged Emitted when any Filter parameter is changed internally
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before calling dataCheck()
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after calling dataCheck()
     */
    void preflightExecuted();

  protected:
    CreateDataArray();
    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    void dataCheck();

    /**
     * @brief Initializes all the private instance variables.
     */
    void initialize();


  private:
    DEFINE_IDATAARRAY_VARIABLE(OutputArray)


    /**
    * @brief checkInitialization Checks that the chosen initialization value/range is inside
    * the bounds of the array type
    */
    template <typename T>
    void checkInitialization(QString dataArrayName);

    const QString Int8 = "signed   int 8  bit";
    const QString UInt8 = "unsigned int 8  bit";
    const QString Int16 = "signed   int 16 bit";
    const QString UInt16 = "unsigned int 16 bit";
    const QString Int32 = "signed   int 32 bit";
    const QString UInt32 = "unsigned int 32 bit";
    const QString Int64 = "signed   int 64 bit";
    const QString UInt64 = "unsigned int 64 bit";
    const QString Float = "       Float 32 bit";
    const QString Double = "      Double 64 bit";
    const QString Bool = "bool";

    CreateDataArray(const CreateDataArray&); // Copy Constructor Not Implemented
    void operator=(const CreateDataArray&); // Operator '=' Not Implemented
};




Q_DECLARE_METATYPE(CreateDataArray::ScalarTypeChoices)

#endif /* _CreateDataArray_H_ */
