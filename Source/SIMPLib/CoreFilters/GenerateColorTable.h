/*
 * Your License or Copyright can go here
 */

#ifndef _generatecolortable_h_
#define _generatecolortable_h_

#include <QtCore/QJsonObject>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/AbstractFilter.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

/**
 * @brief The GenerateColorTable class. See [Filter documentation](@ref generatecolortable) for details.
 */
class SIMPLib_EXPORT GenerateColorTable : public AbstractFilter
{
  Q_OBJECT

  public:
    SIMPL_SHARED_POINTERS(GenerateColorTable)
    SIMPL_STATIC_NEW_MACRO(GenerateColorTable)
    SIMPL_TYPE_MACRO_SUPER(GenerateColorTable, AbstractFilter)

    virtual ~GenerateColorTable();

    SIMPL_INSTANCE_PROPERTY(QString, SelectedPresetName)
    Q_PROPERTY(QString SelectedPresetName READ getSelectedPresetName WRITE setSelectedPresetName)

    SIMPL_INSTANCE_PROPERTY(QJsonArray, SelectedPresetControlPoints)
    Q_PROPERTY(QJsonArray SelectedPresetControlPoints READ getSelectedPresetControlPoints WRITE setSelectedPresetControlPoints)

    SIMPL_INSTANCE_PROPERTY(DataArrayPath, SelectedDataArrayPath)
    Q_PROPERTY(DataArrayPath SelectedDataArrayPath READ getSelectedDataArrayPath WRITE setSelectedDataArrayPath)

    SIMPL_INSTANCE_PROPERTY(QString, RGB_ArrayName)
    Q_PROPERTY(QString RGB_ArrayName READ getRGB_ArrayName WRITE setRGB_ArrayName)

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
    GenerateColorTable();

    /**
    * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
    */
    void dataCheck();

    /**
    * @brief Initializes all the private instance variables.
    */
    void initialize();

  private:

    GenerateColorTable(const GenerateColorTable&); // Copy Constructor Not Implemented
    void operator=(const GenerateColorTable&); // Operator '=' Not Implemented
};

#endif /* _GenerateColorTable_H_ */
