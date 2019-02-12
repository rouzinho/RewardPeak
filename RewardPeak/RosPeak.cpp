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

// CEDAR INCLUDES
#include "RosPeak.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"

// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
RosPeak::RosPeak()
:
cedar::proc::Step(true),
mOutput(new cedar::aux::MatData(cv::Mat::zeros(1, 100, CV_32F))),
mSize(new cedar::aux::IntParameter(this, "Size",25)),
mSigma(new cedar::aux::DoubleParameter(this,"Sigma",3.0)),
mTopic(new cedar::aux::StringParameter(this, "Topic Name", ""))
{
this->declareOutput("output", mOutput);
//this->declareInput("motor",true);

mGaussMatrixSizes.push_back(100);
mGaussMatrixSigmas.push_back(3.0);
mGaussMatrixCenters.push_back(25.0);
//init the variable that will get the sensor value
dat = 0;

this->connect(this->mSize.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mSigma.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mTopic.get(), SIGNAL(valueChanged()), this, SLOT(reName()));


}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void RosPeak::compute(const cedar::proc::Arguments&)
{

  //subscriber for the sensor
  /*
  cedar::aux::ConstDataPtr op1 = this->getInputSlot("motor")->getData();
  cv::Mat doublepos = op1->getData<cv::Mat>();
  float t1 = doublepos.at<float>(0);
  pos = static_cast<double> (t1);
  pos = pos * 100;
  */

  ros::Rate loop_rate(98);
  loop_rate.sleep();
  ros::spinOnce();

  //change the Gaussian function with the value of the ear sensor.
  this->mOutput->setData(cedar::aux::math::gaussMatrix(1,mGaussMatrixSizes,dat,mGaussMatrixSigmas,mGaussMatrixCenters,true));

}

void RosPeak::reCompute()
{
   mGaussMatrixSizes.clear();
   mGaussMatrixSigmas.clear();
   mGaussMatrixSizes.push_back(static_cast<int>(this->mSize->getValue()));
   mGaussMatrixSigmas.push_back(static_cast<double>(this->mSigma->getValue()));

}


void RosPeak::reName()
{
   topicName = this->mTopic->getValue();
   const std::string tname = topicName;
   sub = n.subscribe(tname, 1000, &RosPeak::chatterCallback,this);
}

//callback for the subscriber. This one get the value of the sensor.
void RosPeak::chatterCallback(const std_msgs::Float64::ConstPtr& msg)
{
   ROS_INFO("I heard: [%f]", msg->data);
   dat = msg->data;
}

void RosPeak::reset()
{

	//ros::shutdown();

}
