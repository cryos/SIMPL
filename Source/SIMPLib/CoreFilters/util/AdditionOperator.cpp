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

#include "AdditionOperator.h"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>

#include "SIMPLib/Common/TemplateHelpers.hpp"

#include "CalculatorArray.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AdditionOperator::AdditionOperator() :
  CalculatorOperator()
{
  setPrecedenceId(0);
  setOperatorType(Binary);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AdditionOperator::~AdditionOperator()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QSharedPointer<CalculatorItem> AdditionOperator::calculate(AbstractFilter* filter, const QString &newArrayName, QStack<QSharedPointer<CalculatorItem> > &executionStack)
{
  if (executionStack.size() >= 2)
  {
    IDataArray::Pointer item1 = qSharedPointerDynamicCast<CalculatorArray>(executionStack.pop())->getArray();
    IDataArray::Pointer item2 = qSharedPointerDynamicCast<CalculatorArray>(executionStack.pop())->getArray();

    EXECUTE_FUNCTION_TWO_ARRAYS(filter, newArrayName, item1, item2, add)\
  }

  // If the execution gets down here, then we have an error
  QString ss = QObject::tr("The chosen infix equation is not a valid equation.");
  filter->setErrorCondition(-4005);
  filter->notifyErrorMessage(filter->getHumanLabel(), ss, filter->getErrorCondition());
  return QSharedPointer<CalculatorItem>();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template <typename J, typename K>
QSharedPointer<CalculatorItem> AdditionOperator::add(AbstractFilter* filter, const QString &newArrayName, IDataArray::Pointer dataArray1, IDataArray::Pointer dataArray2)
{
  typedef Eigen::Array<J, Eigen::Dynamic, 1> JEigenArrayType;
  typedef Eigen::Map<JEigenArrayType> JEigenArrayMapType;

  typedef Eigen::Array<K, Eigen::Dynamic, 1> KEigenArrayType;
  typedef Eigen::Map<KEigenArrayType> KEigenArrayMapType;

  typename DataArray<J>::Pointer arrayCast1 = std::dynamic_pointer_cast<DataArray<J> >(dataArray1);
  typename DataArray<K>::Pointer arrayCast2 = std::dynamic_pointer_cast<DataArray<K> >(dataArray2);

  DataArray<double>::Pointer newArray;
  if (arrayCast1->getNumberOfTuples() > 1 && arrayCast2->getNumberOfTuples() == 1)
  {
    double number = static_cast<double>(arrayCast2->getValue(0));
    JEigenArrayMapType ac(arrayCast1->getPointer(0), arrayCast1->getNumberOfTuples());

    newArray = DataArray<double>::CreateArray(arrayCast1->getNumberOfTuples(), newArrayName);
    Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > newArrayMap(newArray->getPointer(0), newArray->getNumberOfTuples());

    newArrayMap = ac. template cast<double>() + number;
  }
  else if (arrayCast1->getNumberOfTuples() == 1 && arrayCast2->getNumberOfTuples() > 1)
  {
    double number = static_cast<double>(arrayCast1->getValue(0));
    KEigenArrayMapType ac(arrayCast2->getPointer(0), arrayCast2->getNumberOfTuples());

    newArray = DataArray<double>::CreateArray(arrayCast2->getNumberOfTuples(), newArrayName);
    Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > newArrayMap(newArray->getPointer(0), newArray->getNumberOfTuples());

    newArrayMap = ac. template cast<double>() + number;
  }
  else if (arrayCast1->getNumberOfTuples() > 0 && arrayCast2->getNumberOfTuples() > 0)
  {
    JEigenArrayMapType ac1(arrayCast1->getPointer(0), arrayCast1->getNumberOfTuples());
    KEigenArrayMapType ac2(arrayCast2->getPointer(0), arrayCast2->getNumberOfTuples());

    newArray = DataArray<double>::CreateArray(arrayCast2->getNumberOfTuples(), newArrayName);
    Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > newArrayMap(newArray->getPointer(0), newArray->getNumberOfTuples());

    newArrayMap = ac1. template cast<double>() + ac2. template cast<double>();
  }
  else
  {
    Q_ASSERT(false);
  }

  QSharedPointer<CalculatorItem> newItem = QSharedPointer<CalculatorArray>(new CalculatorArray(newArray));
  return newItem;
}

