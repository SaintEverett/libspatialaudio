/*############################################################################*/
/*#                                                                          #*/
/*#  Ambisonic C++ Library                                                   #*/
/*#  CBFormat - Ambisonic BFormat                                            #*/
/*#  Copyright © 2007 Aristotel Digenis                                      #*/
/*#                                                                          #*/
/*#  Filename:      BFormat.h                                                #*/
/*#  Version:       0.1                                                      #*/
/*#  Date:          19/05/2007                                               #*/
/*#  Author(s):     Aristotel Digenis                                        #*/
/*#  Licence:       MIT                                                      #*/
/*#                                                                          #*/
/*############################################################################*/


#ifndef _BFORMAT_H
#define _BFORMAT_H

#include "AmbisonicBase.h"
#include <memory>
#include <vector>

/// Storage for BFormat signals.

/** This object is used to store and transfer BFormat signals. Memory is
    allocated for the number of channels needed for the given Ambisonic
    configuration (order and 2D/3D) and the number of samples. */

class CBFormat : public CAmbisonicBase
{
public:
    CBFormat();
    unsigned GetSampleCount(); // returns sample count of buffers
    bool Configure(unsigned nOrder, bool b3D, unsigned nSampleCount); // recreate the buffers needed for the given config
    void Reset(); // fill buffers with zeros
    void Refresh(); // not implemented
    void InsertStream(float* pfData, unsigned nChannel, unsigned nSamples); // copy a number of samples to a specified channel in the bformat
    void ExtractStream(float* pfData, unsigned nChannel, unsigned nSamples); // copy a number of samples from a specified channel in the bformat
    void operator = (const CBFormat &bf); // copy the content of a buffer to another, this operator assumes they are of the same config (order, channel count, etc. look at AmbisonicBase.h regarding configuration
    bool operator == (const CBFormat &bf); // returns 1 (true) if two buffers are of the same configuration
    bool operator != (const CBFormat &bf); // return 1 (true) if two buffers are NOT of the same configuration
    CBFormat& operator += (const CBFormat &bf);
    CBFormat& operator -= (const CBFormat &bf);
    CBFormat& operator *= (const CBFormat &bf);
    CBFormat& operator /= (const CBFormat &bf);
    CBFormat& operator += (const float &fValue);
    CBFormat& operator -= (const float &fValue);
    CBFormat& operator *= (const float &fValue);
    CBFormat& operator /= (const float &fValue);

protected: // class data & info
    unsigned m_nSamples; // # of samples in buffer
    unsigned m_nDataLength; // m_nSamples * m_nChannelCount (how many sets of samples)
    std::vector<float> m_pfData; // sample data
    std::unique_ptr<float*[]> m_ppfChannels; 

    //friend classes cannot be pure abstract type,
    //so must list each friend class manually
    // listing these as friends allows the below classes to access protected data of the BFormat class
    friend class CAmbisonicEncoder;
    friend class CAmbisonicEncoderDist;
    friend class CAmbisonicDecoder;
    friend class CAmbisonicSpeaker;
    friend class CAmbisonicMicrophone;
    friend class CAmbisonicProcessor;
    friend class CAmbisonicBinauralizer;
    friend class CAmbisonicZoomer;
};

#endif //_BFORMAT_H
