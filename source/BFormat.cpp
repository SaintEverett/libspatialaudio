/*############################################################################*/
/*#                                                                          #*/
/*#  Ambisonic C++ Library                                                   #*/
/*#  CBFormat - Ambisonic BFormat                                            #*/
/*#  Copyright © 2007 Aristotel Digenis                                      #*/
/*#                                                                          #*/
/*#  Filename:      BFormat.cpp                                              #*/
/*#  Version:       0.1                                                      #*/
/*#  Date:          19/05/2007                                               #*/
/*#  Author(s):     Aristotel Digenis                                        #*/
/*#  Licence:       MIT                                                      #*/
/*#                                                                          #*/
/*############################################################################*/


#include "BFormat.h"

CBFormat::CBFormat()
{
    m_nSamples = 0; // initialize w/ zero samples and no data
    m_nDataLength = 0; 
}

unsigned CBFormat::GetSampleCount()
{
    return m_nSamples; // simply return sample count
}

bool CBFormat::Configure(unsigned nOrder, bool b3D, unsigned nSampleCount) // configure BFormat buffer
{
    bool success = CAmbisonicBase::Configure(nOrder, b3D, nSampleCount); // boolean "success" is assigned "1" (true) if the function AmbisonicBase::Configure returns "1" (true) upon attempting to configure
    if(!success) // if it does not configure properly, get out
        return false;
    // if it does, continue configuration on this class
    m_nSamples = nSampleCount; // assign sample count
    m_nDataLength = m_nSamples * m_nChannelCount; // calculate total amount of samples used via how many channel buffers
    m_pfData.resize(m_nDataLength); // pfData is a vector for buffer storage, this resizes the vector to fit all the data needed, determined by m_nDataLength (samps * channels)
    memset(m_pfData.data(), 0, m_nDataLength * sizeof(float)); // fill the vector's data (the buffer) with 0s, for (m_nDataLength * sizeof(float)) number of bytes 
    m_ppfChannels.reset(new float*[m_nChannelCount]); // m_ppfChannels is a pointer (more specifically a std::unique_ptr) that points to a float array of the size m_nChannelCount, this ".reset()" instantiates a float[] that is the size of m_nChannelCount

    for(unsigned niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        m_ppfChannels[niChannel] = &m_pfData[niChannel * m_nSamples];
    }

    return true;
}

void CBFormat::Reset()
{
    memset(m_pfData.data(), 0, m_nDataLength * sizeof(float)); // clear buffer (set to 0s)
}

void CBFormat::Refresh() // not implemented
{

}

void CBFormat::InsertStream(float* pfData, unsigned nChannel, unsigned nSamples)
{
    memcpy(m_ppfChannels[nChannel], pfData, nSamples * sizeof(float)); // using the std::unique_ptr, copy specified vector to the specified float[] row, and copy n amount of samples
}

void CBFormat::ExtractStream(float* pfData, unsigned nChannel, unsigned nSamples)
{
    memcpy(pfData, m_ppfChannels[nChannel], nSamples * sizeof(float)); // opposite of insertstream, copy the specified float[] row to the specified vector
}

void CBFormat::operator = (const CBFormat &bf)
{
    memcpy(m_pfData.data(), bf.m_pfData.data(), m_nDataLength * sizeof(float)); // copy the vector of one BFormat to another
}

bool CBFormat::operator == (const CBFormat &bf)
{
    if(m_b3D == bf.m_b3D && m_nOrder == bf.m_nOrder && m_nDataLength == bf.m_nDataLength) // test two BFormats to be of the same configuration
        return true;
    else
        return false;
}

bool CBFormat::operator != (const CBFormat &bf)
{
    if(m_b3D != bf.m_b3D || m_nOrder != bf.m_nOrder || m_nDataLength != bf.m_nDataLength) // test the two BFormats to NOT be of the same configuration
        return true;
    else
        return false;
}

CBFormat& CBFormat::operator += (const CBFormat &bf) // combine two buffers (add one to the other)
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] += bf.m_ppfChannels[niChannel][niSample];
        }
    }

    return *this;
}

CBFormat& CBFormat::operator -= (const CBFormat &bf) // subtract two buffers
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] -= bf.m_ppfChannels[niChannel][niSample];
        }
    }

    return *this;
}

CBFormat& CBFormat::operator *= (const CBFormat &bf) // multiply two buffers
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] *= bf.m_ppfChannels[niChannel][niSample];
        }
    }

    return *this;
}

CBFormat& CBFormat::operator /= (const CBFormat &bf) // divide two buffers
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] /= bf.m_ppfChannels[niChannel][niSample];
        }
    }

    return *this;
}

CBFormat& CBFormat::operator += (const float &fValue) // add a constant value to buffer
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] += fValue;
        }
    }

    return *this;
}

CBFormat& CBFormat::operator -= (const float &fValue) // subtract a constant value from buffer
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] -= fValue;
        }
    }

    return *this;
}

CBFormat& CBFormat::operator *= (const float &fValue) // multiply a constant value to buffer (gain)
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] *= fValue;
        }
    }

    return *this;
}

CBFormat& CBFormat::operator /= (const float &fValue) // divide buffer by a constant value
{
    unsigned niChannel = 0;
    unsigned niSample = 0;
    for(niChannel = 0; niChannel < m_nChannelCount; niChannel++)
    {
        for(niSample = 0; niSample < m_nSamples; niSample++)
        {
            m_ppfChannels[niChannel][niSample] /= fValue;
        }
    }

    return *this;
}
