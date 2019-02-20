

// CEDAR INCLUDES
#include "RewardPeak.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>

// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
RewardPeak::RewardPeak()
:
cedar::proc::Step(true),
mOutput(new cedar::aux::MatData(cv::Mat::zeros(1, 100, CV_32F))),
mSize(new cedar::aux::IntParameter(this, "Size",100)),
mValue(new cedar::aux::DoubleParameter(this, "Amplitude",0.0)),
mSigma(new cedar::aux::DoubleParameter(this,"Sigma",3.0))
{
this->declareOutput("output", mOutput);
this->declareInput("motor",true);
this->declareInput("amplitude",false);

mGaussMatrixSizes.push_back(100);
mGaussMatrixSigmas.push_back(3.0);
mGaussMatrixCenters.push_back(25.0);

this->connect(this->mSize.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mSigma.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mValue.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));


}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void RewardPeak::compute(const cedar::proc::Arguments&)
{

   cedar::aux::ConstDataPtr input_motor = this->getInput("motor");
   const cv::Mat& input_mot = input_motor->getData<cv::Mat>();
   float t1 = input_mot.at<float>(0);
   pos = static_cast<double> (t1);
   pos = pos * size;

   cedar::aux::ConstDataPtr input_amplitude = this->getInput("amplitude");
   const cv::Mat& input_amp = input_amplitude->getData<cv::Mat>();
   float t2 = input_amp.at<float>(0);
   amp = static_cast<double> (t2);
   amp = amp + value;

   mGaussMatrixSizes.clear();
   mGaussMatrixCenters.clear();
   mGaussMatrixSizes.push_back(size);
   mGaussMatrixCenters.push_back(pos);

   //change the Gaussian function with the value of the sensor.
   this->mOutput->setData(cedar::aux::math::gaussMatrix(1,mGaussMatrixSizes,amp,mGaussMatrixSigmas,mGaussMatrixCenters,true));

}

void RewardPeak::reCompute()
{
   mGaussMatrixSizes.clear();
   mGaussMatrixSigmas.clear();
   size = static_cast<int>(this->mSize->getValue());
   mGaussMatrixSizes.push_back(size);
   mGaussMatrixSigmas.push_back(static_cast<double>(this->mSigma->getValue()));
   value = static_cast<double>(this->mValue->getValue());
}

//callback for the subscriber. This one get the value of the sensor.


void RewardPeak::reset()
{

	//ros::shutdown();

}
