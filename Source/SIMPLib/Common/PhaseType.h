/* ============================================================================
* Copyright (c) 2009-2015 BlueQuartz Software, LLC
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

#ifndef _phasetype_h_
#define _phasetype_h_


#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QStringList>
#include <QtCore/QMap>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/Constants.h"


/**
 * @class PhaseType PhaseType.h PathToHeader/PhaseType.h
 * @brief
 * @author Mike Jackson for BlueQuartz.net
 * @date May 13, 2011
 * @version 1.0
 */
class SIMPLib_EXPORT PhaseType
{
  public:

    virtual ~PhaseType();

    static QString PrimaryStr() { return QString("Primary"); }
    static QString PrecipitateStr() { return QString("Precipitate"); }
    static QString TransformationStr() { return QString("Transformation"); }
    static QString MatrixStr() { return QString("Matrix"); }
    static QString BoundaryStr() { return QString("Boundary"); }
    static QString UnknownPhaseTypeStr() { return QString("Unknown Phase Type"); }


    static QString getPhaseTypeString(unsigned int phaseType)
    {
      switch(phaseType)
      {
        case SIMPL::PhaseType::PrimaryPhase:
          return PrimaryStr();
        case SIMPL::PhaseType::PrecipitatePhase:
          return PrecipitateStr();
        case SIMPL::PhaseType::TransformationPhase:
          return TransformationStr();
        case SIMPL::PhaseType::MatrixPhase:
          return MatrixStr();
        case SIMPL::PhaseType::BoundaryPhase:
          return BoundaryStr();
        case SIMPL::PhaseType::UnknownPhaseType:
          return UnknownPhaseTypeStr();
        default:
          break;
      }
      return QString("Undefined Phase Type (Error)");
    }

    static unsigned int getPhaseType(const char* str)
    {
      if (PrimaryStr().compare(str) == 0)
      {
        return SIMPL::PhaseType::PrimaryPhase;
      }
      else if (PrecipitateStr().compare(str) == 0)
      {
        return SIMPL::PhaseType::PrecipitatePhase;
      }
      else if (TransformationStr().compare(str) == 0)
      {
        return SIMPL::PhaseType::TransformationPhase;
      }
      else if (MatrixStr().compare(str) == 0)
      {
        return SIMPL::PhaseType::MatrixPhase;
      }
      else if (BoundaryStr().compare(str) == 0)
      {
        return SIMPL::PhaseType::BoundaryPhase;
      }
      return SIMPL::PhaseType::UnknownPhaseType;
    }


    static void getPhaseTypeStrings(QStringList& strings)
    {
      strings.clear();
      strings.push_back(PrimaryStr());
      strings.push_back(PrecipitateStr());
      strings.push_back(TransformationStr());
      strings.push_back(MatrixStr());
      strings.push_back(BoundaryStr());
      strings.push_back(UnknownPhaseTypeStr());
    }

    static void getPhaseTypeEnums(QVector<unsigned int>& types)
    {
      types.clear();
      types.push_back(SIMPL::PhaseType::PrimaryPhase);
      types.push_back(SIMPL::PhaseType::PrecipitatePhase);
      types.push_back(SIMPL::PhaseType::TransformationPhase);
      types.push_back(SIMPL::PhaseType::MatrixPhase);
      types.push_back(SIMPL::PhaseType::BoundaryPhase);
      types.push_back(SIMPL::PhaseType::UnknownPhaseType);
    }

    static void getPhaseTypeMap(QMap<int, QString>& map)
    {
      map.clear();
      map[SIMPL::PhaseType::PrimaryPhase] = PrimaryStr();
      map[SIMPL::PhaseType::PrecipitatePhase] = PrecipitateStr();
      map[SIMPL::PhaseType::TransformationPhase] = TransformationStr();
      map[SIMPL::PhaseType::MatrixPhase] = MatrixStr();
      map[SIMPL::PhaseType::BoundaryPhase] = BoundaryStr();
      map[SIMPL::PhaseType::UnknownPhaseType] = UnknownPhaseTypeStr();
    }

  protected:
    PhaseType();
  private:
    PhaseType(const PhaseType&); //Not Implemented
    void operator=(const PhaseType&); //Not Implemented

};



#endif //_PhaseType_h_
