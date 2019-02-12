/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

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

    File:        RosPeak.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

#ifndef CEDAR_TUTORIAL_SIMPLE_SUMMATION_H
#define CEDAR_TUTORIAL_SIMPLE_SUMMATION_H

// CEDAR INCLUDES
#include <cedar/processing/Step.h> // if we are going to inherit from cedar::proc::Step, we have to include the header

// FORWARD DECLARATIONS
#include <cedar/auxiliaries/MatData.fwd.h>
#include <cedar/auxiliaries/DoubleParameter.h>
#include <cedar/auxiliaries/StringParameter.h>
#include <cedar/auxiliaries/IntParameter.h>
#include "ros/ros.h"
#include "std_msgs/Float64.h"

// SYSTEM INCLUDES

/*!@brief The tutorial code should look like this..
 *
 * Seriously, I mean it!.
 */
class RosPeak : public cedar::proc::Step
{
  Q_OBJECT
  //--------------------------------------------------------------------------------------------------------------------
  // constructors and destructor
  //--------------------------------------------------------------------------------------------------------------------
public:
  //!@brief The standard constructor.
  RosPeak();

  //!@brief Destructor

  //--------------------------------------------------------------------------------------------------------------------
  // public methods
  //--------------------------------------------------------------------------------------------------------------------
public slots:
  // none yet
  void reCompute();
  void reName();
  //--------------------------------------------------------------------------------------------------------------------
  // protected methods
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet

  //--------------------------------------------------------------------------------------------------------------------
  // private methods
  //--------------------------------------------------------------------------------------------------------------------
private:
  // The arguments are unused here
  void compute(const cedar::proc::Arguments&);
  void chatterCallback(const std_msgs::Float64::ConstPtr& msg);
  void reset();

  //--------------------------------------------------------------------------------------------------------------------
  // members
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet
private:
  //!@brief this is the output of the computation (in this case, the summed inputs)
  cedar::aux::MatDataPtr mOutput;
  std::vector<unsigned int> mGaussMatrixSizes;
  std::vector<double> mGaussMatrixSigmas;
  std::vector<double> mGaussMatrixCenters;
  cedar::aux::IntParameterPtr mSize;
  cedar::aux::DoubleParameterPtr mSigma;
  cedar::aux::StringParameterPtr mTopic;
  cedar::aux::DoubleParameterPtr mCenter;

  std::string topicName;
  ros::NodeHandle n;
  ros::Subscriber sub;
  double sigma;
  double center;
  double pos;
  int size;
  double dat;

  //--------------------------------------------------------------------------------------------------------------------
  // parameters
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet

private:
  // none yet

}; // class RosPeak

#endif // CEDAR_TUTORIAL_SIMPLE_SUMMATION_H
