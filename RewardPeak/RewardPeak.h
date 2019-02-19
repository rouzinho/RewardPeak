/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015, 2016, 2017 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        RewardPeak.h

    Maintainer:  Stephan Zibner
    Email:       stephan.zibner@ini.ruhr-uni-bochum.de
    Date:        2011 11 08

    Description:

    Credits:

======================================================================================================================*/

#ifndef RewardPeak_H
#define RewardPeak_H

// CEDAR INCLUDES
#include "cedar/dynamics/Dynamics.h"
#include "cedar/auxiliaries/math/Sigmoid.h"
#include "cedar/auxiliaries/DoubleParameter.h"
#include "cedar/auxiliaries/UIntParameter.h"
#include "cedar/auxiliaries/UIntVectorParameter.h"
#include "cedar/auxiliaries/ObjectParameterTemplate.h"

// FORWARD DECLARATIONS
#include "cedar/auxiliaries/MatData.fwd.h"
//#include "RewardPeak.fwd.h"

// SYSTEM INCLUDES


/*!@brief A step that implements RewardPeak dynamics.
 */
class RewardPeak : public cedar::dyn::Dynamics
{
  //--------------------------------------------------------------------------------------------------------------------
  // macros
  //--------------------------------------------------------------------------------------------------------------------
  Q_OBJECT

  //--------------------------------------------------------------------------------------------------------------------
  // nested types
  //--------------------------------------------------------------------------------------------------------------------
  //!@brief a parameter for sigmoid objects
  typedef cedar::aux::ObjectParameterTemplate<cedar::aux::math::TransferFunction> SigmoidParameter;
  //!@cond SKIPPED_DOCUMENTATION
  CEDAR_GENERATE_POINTER_TYPES_INTRUSIVE(SigmoidParameter);
  //!@endcond

  //--------------------------------------------------------------------------------------------------------------------
  // constructors and destructor
  //--------------------------------------------------------------------------------------------------------------------
public:
  //!@brief The standard constructor.
  RewardPeak();

  //!@brief Destructor

  //--------------------------------------------------------------------------------------------------------------------
  // public methods
  //--------------------------------------------------------------------------------------------------------------------
public:
  //!@brief determine if a given Data is a valid input to the field
  cedar::proc::DataSlot::VALIDITY determineInputValidity
                                  (
                                    cedar::proc::ConstDataSlotPtr,
                                    cedar::aux::ConstDataPtr
                                  ) const;

  void resetRewardPeak();

public slots:
  //!@brief handle a change in dimensionality, which leads to creating new matrices
  void dimensionalityChanged();
  //!@brief handle a change in size along dimensions, which leads to creating new matrices
  void dimensionSizeChanged();

  void resetMemory();

  //--------------------------------------------------------------------------------------------------------------------
  // protected methods
  //--------------------------------------------------------------------------------------------------------------------
protected:
  /*!@brief compute the euler step of the RewardPeak dynamics
   *
   * This is the equation:
   * \f[
   *
   * \f]
   */
  void eulerStep(const cedar::unit::Time& time);

  //--------------------------------------------------------------------------------------------------------------------
  // private methods
  //--------------------------------------------------------------------------------------------------------------------
private:
  //!@brief update the size and dimensionality of internal matrices
  void updateMatrices();

  //!@brief check if input fits to field in dimension and size
  bool isMatrixCompatibleInput(const cv::Mat& matrix) const;



  //--------------------------------------------------------------------------------------------------------------------
  // members
  //--------------------------------------------------------------------------------------------------------------------
protected:
  //!@brief this SpaceCode matrix contains the current field activity of the NeuralField
  cedar::aux::MatDataPtr mActivation;

private:
  // none yet

  //--------------------------------------------------------------------------------------------------------------------
  // parameters
  //--------------------------------------------------------------------------------------------------------------------
protected:
  //!@brief the field dimensionality - may range from 1 to 16 in principle, but more like 6 or 7 in reality
  cedar::aux::UIntParameterPtr _mDimensionality;
  //!@brief the field sizes in each dimension
  cedar::aux::UIntVectorParameterPtr _mSizes;
  //!@brief time scale build up
  cedar::aux::DoubleParameterPtr _mTimeScaleBuildUp;
  //!@brief time scale decay
  cedar::aux::DoubleParameterPtr _mTimeScaleDecay;

  //! Sigmoid applied to the input.
  SigmoidParameterPtr _mSigmoid;
private:
  // none yet

}; // class cedar::dyn::RewardPeak

#endif // CEDAR_DYN_RewardPeak_H
