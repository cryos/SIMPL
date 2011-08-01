/* ============================================================================
 * Copyright (c) 2011, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
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
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
///////////////////////////////////////////////////////////////////////////////
// This code was partly written under US Air Force Contract FA8650-07-D-5800
///////////////////////////////////////////////////////////////////////////////
#ifndef ANGREADER_H_
#define ANGREADER_H_

#include <string>
#include <map>


#include "EbsdLib/EbsdSetGetMacros.h"
#include "EbsdLib/EbsdLibConfiguration.h"
#include "AngConstants.h"
#include "AngHeaderEntry.h"
#include "AngPhase.h"



/**
* @class AngReader AngReader.h AngReader/AngReader.h
* @brief This class is a self contained TSL OIM .ang file reader. It should only be dependent on
* standard C++ features
* @author Michael A. Jackson for BlueQuartz Software
* @date Mar 1, 2010
* @version 1.0
*/
class EbsdLib_EXPORT AngReader
{
  public:
    AngReader();
    virtual ~AngReader();

    /** @brief Allow the user to set the origin of the scan */
    EBSD_INSTANCE_PROPERTY(Ebsd::Ang::Orientation, UserOrigin)

    /** @brief Sets the file name of the ang file to be read */
    EBSD_INSTANCE_STRING_PROPERTY( FileName )
    EBSD_INSTANCE_PROPERTY(size_t, NumberOfElements);
    EBSD_INSTANCE_PROPERTY(int, NumFields);

    EBSD_INSTANCE_STRING_PROPERTY(CompleteHeader);

    /** @brief Header Values from the TSL ang file */

    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, TEMpixPerum, Ebsd::Ang::TEMPIXPerUM)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, XStar, Ebsd::Ang::XStar)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, YStar, Ebsd::Ang::YStar)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, ZStar, Ebsd::Ang::ZStar)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, WorkingDistance, Ebsd::Ang::WorkingDistance)

    EBSD_INSTANCE_PROPERTY(std::vector<AngPhase::Pointer>, PhaseVector)

    EbsdHeader_INSTANCE_PROPERTY(AngStringHeaderEntry, std::string, Grid, Ebsd::Ang::Grid)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, XStep, Ebsd::Ang::XStep)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<float>, float, YStep, Ebsd::Ang::YStep)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<int>, int, NumOddCols, Ebsd::Ang::NColsOdd)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<int>, int, NumEvenCols, Ebsd::Ang::NColsEven)
    EbsdHeader_INSTANCE_PROPERTY(AngHeaderEntry<int>, int, NumRows, Ebsd::Ang::NRows)
    EbsdHeader_INSTANCE_PROPERTY(AngStringHeaderEntry, std::string, OIMOperator, Ebsd::Ang::Operator)
    EbsdHeader_INSTANCE_PROPERTY(AngStringHeaderEntry, std::string, SampleID, Ebsd::Ang::SampleId)
    EbsdHeader_INSTANCE_PROPERTY(AngStringHeaderEntry, std::string, ScanID, Ebsd::Ang::ScanId)

    /** @brief Get a pointer to the Phi1 data. Note that this array WILL be deleted
    * when this object is deleted. Most programs should copy the data from the array
    * into their own array storage. */
    EBSD_POINTER_PROPERTY(Phi1, Phi1, float)
    EBSD_POINTER_PROPERTY(Phi, Phi, float)
    EBSD_POINTER_PROPERTY(Phi2, Phi2, float)
    EBSD_POINTER_PROPERTY(XPos, X, float)
    EBSD_POINTER_PROPERTY(YPos, Y, float)
    EBSD_POINTER_PROPERTY(ImageQuality, Iq, float)
    EBSD_POINTER_PROPERTY(ConfidenceIndex, Ci, float)
    EBSD_POINTER_PROPERTY(Phase, PhaseData, int)
    EBSD_POINTER_PROPERTY(SEMSignal, SEMSignal, float)
    EBSD_POINTER_PROPERTY(Fit, Fit, float)

    /**
    * @brief Reads the complete TSL .ang file.
    * @return 1 on success
    */
    virtual int readFile();

    /**
    * @brief Reads ONLY the header portion of the TSL .ang file
    * @return 1 on success
    */
    virtual int readHeaderOnly();


protected:
    // Needed by subclasses
    std::map<std::string, EbsdHeaderEntry::Pointer> m_Headermap;

    /** @brief Allocates the proper amount of memory (after reading the header portion of the file)
    * and then splats '0' across all the bytes of the memory allocation
    */
    void initPointers(size_t numElements);

    /** @brief 'free's the allocated memory and sets the pointer to NULL
    */
    void deletePointers();

    /**
     * @brief Allocats a contiguous chunk of memory to store values from the .ang file
     * @param numberOfElements The number of elements in the Array. This method can
     * also optionally produce SSE aligned memory for use with SSE intrinsics
     * @return Pointer to allocated memory
     */
      template<typename T>
      T* allocateArray(size_t numberOfElements)
      {
  #if defined ( AIM_USE_SSE ) && defined ( __SSE2__ )
        T* m_buffer = static_cast<T*>( _mm_malloc (numberOfElements * sizeof(T), 16) );
  #else
        T*  m_buffer = new T[numberOfElements];
  #endif
        m_NumberOfElements = numberOfElements;
        return m_buffer;
      }

    /**
     * @brief Deallocates memory that has been previously allocated. This will set the
     * value of the pointer passed in as the argument to NULL.
     * @param ptr The pointer to be freed.
     */
      template<typename T>
      void deallocateArrayData(T* &ptr)
      {
        if (ptr != NULL && this->m_ManageMemory == true)
        {
  #if defined ( AIM_USE_SSE ) && defined ( __SSE2__ )
          _mm_free(ptr );
  #else
          delete[] ptr;
  #endif
          ptr = NULL;
          m_NumberOfElements = 0;
        }
      }

private:
    bool m_ManageMemory;  // We are going to forcibly manage the memory. There is currently NO option otherwise.
    bool m_headerComplete;

    AngPhase::Pointer   m_CurrentPhase;


    /** @brief Parses the value from a single line of the header section of the TSL .ang file
    * @param line The line to parse
    */
    void parseHeaderLine(char* buf, size_t length);

    /** @brief Parses the data from a line of data from the TSL .ang file
    * @param line The line of data to parse
    */
    void readData(const std::string &line, int nCols, int currentCol, int nRows, int currentRow, size_t counter);

    AngReader(const AngReader&);    // Copy Constructor Not Implemented
    void operator=(const AngReader&);  // Operator '=' Not Implemented

};

#endif /* ANGREADER_H_ */
