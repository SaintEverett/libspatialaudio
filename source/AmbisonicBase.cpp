/*############################################################################*/
/*#                                                                          #*/
/*#  Ambisonic C++ Library                                                   #*/
/*#  CAmbisonicBase - Ambisonic Base                                         #*/
/*#  Copyright © 2007 Aristotel Digenis                                      #*/
/*#                                                                          #*/
/*#  Filename:      AmbisonicBase.cpp                                        #*/
/*#  Version:       0.1                                                      #*/
/*#  Date:          19/05/2007                                               #*/
/*#  Author(s):     Aristotel Digenis                                        #*/
/*#  Licence:       MIT                                                      #*/
/*#                                                                          #*/
/*############################################################################*/


#include "AmbisonicBase.h"

CAmbisonicBase::CAmbisonicBase()
    : m_nOrder(0)
    , m_b3D(0)
    , m_nChannelCount(0)
    , m_bOpt(0)
{
}

unsigned CAmbisonicBase::GetOrder()
{
    return m_nOrder; // return order
}

bool CAmbisonicBase::GetHeight()
{
    return m_b3D; // return Yes or No regarding height
}

unsigned CAmbisonicBase::GetChannelCount()
{
    return m_nChannelCount; // return # of b format channels
}

bool CAmbisonicBase::Configure(unsigned nOrder, bool b3D, unsigned nMisc) // assign arguments to internal data
{
    m_nOrder = nOrder;
    m_b3D = b3D;
    m_nChannelCount = OrderToComponents(m_nOrder, m_b3D); // 

    return true;
}
