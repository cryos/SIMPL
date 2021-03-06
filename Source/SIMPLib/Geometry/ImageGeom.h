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

#ifndef _imagegeom_h_
#define _imagegeom_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Geometry/IGeometryGrid.h"

/**
 * @brief The ImageGeom class represents a structured rectlinear grid
 */
class SIMPLib_EXPORT ImageGeom : public IGeometryGrid
{
  public:
    SIMPL_SHARED_POINTERS(ImageGeom)
    SIMPL_STATIC_NEW_MACRO(ImageGeom)
    SIMPL_TYPE_MACRO_SUPER(ImageGeom, Observable)

    virtual ~ImageGeom();

    /**
     * @brief CreateGeometry
     * @param name
     * @return
     */
    static Pointer CreateGeometry(const QString& name);

    SIMPL_INSTANCE_VEC3_PROPERTY(float, Resolution)

    inline float getXRes() { return m_Resolution[0]; }
    inline float getYRes() { return m_Resolution[1]; }
    inline float getZRes() { return m_Resolution[2]; }

    SIMPL_INSTANCE_VEC3_PROPERTY(float, Origin)

    /**
     * @brief Returns the bounding box for this geometry
     * @param xMin
     * @param xMax
     * @param yMin
     * @param yMax
     * @param zMin
     * @param zMax
     */
    void getBoundingBox(float &xMin, float &xMax, float &yMin, float &yMax, float &zMin, float &zMax);

    /**
     * @brief getBoundingBox
     * @param boundingBox The bounding box will be stored in the input argument in the following order:
     * xMin, xMax, yMin, yMax, zMin, zMax
     */
    void getBoundingBox(float boundingBox[6]);


// -----------------------------------------------------------------------------
// Inherited from IGeometry
// -----------------------------------------------------------------------------

    /**
     * @brief initializeWithZeros
     */
    virtual void initializeWithZeros();

    /**
     * @brief getNumberOfElements
     * @return
     */
    virtual size_t getNumberOfElements();

    /**
     * @brief findElementSizes
     * @return
     */
    virtual int findElementSizes();

    /**
     * @brief getElementSizes
     * @return
     */
    virtual FloatArrayType::Pointer getElementSizes();

    /**
     * @brief deleteElementSizes
     */
    virtual void deleteElementSizes();

    /**
     * @brief findElementsContainingVert
     * @return
     */
    virtual int findElementsContainingVert();

    /**
     * @brief getElementsContainingVert
     * @return
     */
    virtual ElementDynamicList::Pointer getElementsContainingVert();

    /**
     * @brief deleteElementsContainingVert
     */
    virtual void deleteElementsContainingVert();

    /**
     * @brief findElementNeighbors
     * @return
     */
    virtual int findElementNeighbors();

    /**
     * @brief getElementNeighbors
     * @return
     */
    virtual ElementDynamicList::Pointer getElementNeighbors();

    /**
     * @brief deleteElementNeighbors
     */
    virtual void deleteElementNeighbors();

    /**
     * @brief findElementCentroids
     * @return
     */
    virtual int findElementCentroids();

    /**
     * @brief getElementCentroids
     * @return
     */
    virtual FloatArrayType::Pointer getElementCentroids();

    /**
     * @brief deleteElementCentroids
     */
    virtual void deleteElementCentroids();

    /**
     * @brief getParametricCenter
     * @param pCoords
     */
    virtual void getParametricCenter(double pCoords[3]);

    /**
     * @brief getShapeFunctions
     * @param pCoords
     * @param shape
     */
    virtual void getShapeFunctions(double pCoords[3], double* shape);

    /**
     * @brief findDerivatives
     * @param field
     * @param derivatives
     */
    virtual void findDerivatives(DoubleArrayType::Pointer field, DoubleArrayType::Pointer derivatives, Observable* observable = nullptr);

    /**
     * @brief getInfoString
     * @return Returns a formatted string that contains general infomation about
     * the instance of the object.
     */
    virtual QString getInfoString(SIMPL::InfoStringFormat format);

    /**
     * @brief writeGeometryToHDF5
     * @param parentId
     * @param writeXdmf
     * @return
     */
    virtual int writeGeometryToHDF5(hid_t parentId, bool writeXdmf);

    /**
     * @brief writeXdmf
     * @param out
     * @param dcName
     * @param hdfFileName
     * @return
     */
    virtual int writeXdmf(QTextStream& out, QString dcName, QString hdfFileName);

    /**
     * @brief readGeometryFromHDF5
     * @param parentId
     * @param preflight
     * @return
     */
    virtual int readGeometryFromHDF5(hid_t parentId, bool preflight);

    /**
     * @brief deepCopy
     * @return
     */
    virtual IGeometry::Pointer deepCopy();

    /**
     * @brief addAttributeMatrix
     */
    virtual void addAttributeMatrix(const QString& name, AttributeMatrix::Pointer data);

// -----------------------------------------------------------------------------
// Inherited from IGeometryGrid
// -----------------------------------------------------------------------------

    virtual void setDimensions(size_t dims[3]) { std::copy(dims, dims + 3, m_Dimensions); }
    virtual void setDimensions(size_t xDim, size_t yDim, size_t zDim) { m_Dimensions[0] = xDim;
                                                                        m_Dimensions[1] = yDim;
                                                                        m_Dimensions[2] = zDim; }
    virtual void getDimensions(size_t dims[3]) { std::copy(m_Dimensions, m_Dimensions + 3, dims); }
    virtual void getDimensions(size_t& xDim, size_t& yDim, size_t& zDim) { xDim = m_Dimensions[0];
                                                                           yDim = m_Dimensions[1];
                                                                           zDim = m_Dimensions[2]; }

    virtual size_t getXPoints() { return m_Dimensions[0]; }
    virtual size_t getYPoints() { return m_Dimensions[1]; }
    virtual size_t getZPoints() { return m_Dimensions[2]; }

    virtual void getPlaneCoords(size_t idx[3], float coords[3]);
    virtual void getPlaneCoords(size_t x, size_t y, size_t z, float coords[3]);
    virtual void getPlaneCoords(size_t idx, float coords[3]);
    virtual void getPlaneCoords(size_t idx[3], double coords[3]);
    virtual void getPlaneCoords(size_t x, size_t y, size_t z, double coords[3]);
    virtual void getPlaneCoords(size_t idx, double coords[3]);

    virtual void getCoords(size_t idx[3], float coords[3]);
    virtual void getCoords(size_t x, size_t y, size_t z, float coords[3]);
    virtual void getCoords(size_t idx, float coords[3]);
    virtual void getCoords(size_t idx[3], double coords[3]);
    virtual void getCoords(size_t x, size_t y, size_t z, double coords[3]);
    virtual void getCoords(size_t idx, double coords[3]);

  protected:

    ImageGeom();

    /**
     * @brief gatherMetaData
     * @param parentid
     * @param volDims
     * @param spacing
     * @param origin
     * @param spatialDims
     * @param geomName
     * @param preflight
     * @return
     */
    virtual int gatherMetaData(hid_t parentid, size_t volDims[3], float spacing[3], float origin[3], unsigned int spatialDims, QString geomName, bool preflight);

    /**
     * @brief setElementsContaingVert
     * @param elementsContaingVert
     */
    virtual void setElementsContainingVert(ElementDynamicList::Pointer elementsContainingVert);

    /**
     * @brief setElementNeighbors
     * @param elementNeighbors
     */
    virtual void setElementNeighbors(ElementDynamicList::Pointer elementsNeighbors);

    /**
     * @brief setElementCentroids
     * @param elementCentroids
     */
    virtual void setElementCentroids(FloatArrayType::Pointer elementCentroids);

    /**
     * @brief setElementSizes
     * @param elementSizes
     */
    virtual void setElementSizes(FloatArrayType::Pointer elementSizes);

  private:
    size_t m_Dimensions[3];
    FloatArrayType::Pointer m_VoxelSizes;

    friend class FindImageDerivativesImpl;

    ImageGeom(const ImageGeom&); // Copy Constructor Not Implemented
    void operator=(const ImageGeom&); // Operator '=' Not Implemented
};


#endif /* _ImageGeom_H_ */

