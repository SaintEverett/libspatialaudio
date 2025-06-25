/*############################################################################*/
/*#                                                                          #*/
/*#  Ambisonic C++ Library                                                   #*/
/*#  CAmbisonicBase - Ambisonic Base                                         #*/
/*#  Copyright © 2007 Aristotel Digenis                                      #*/
/*#                                                                          #*/
/*#  Filename:      AmbisonicBase.h                                          #*/
/*#  Version:       0.1                                                      #*/
/*#  Date:          19/05/2007                                               #*/
/*#  Author(s):     Aristotel Digenis                                        #*/
/*#  Licence:       MIT                                                      #*/
/*#                                                                          #*/
/*############################################################################*/


#ifndef _AMBISONIC_BASE_H
#define    _AMBISONIC_BASE_H

#include "AmbisonicCommons.h"

/// Ambisonic base class.

/** This is the base class for most if not all of the classes that make up this
    library. */

class CAmbisonicBase
{
public:
    CAmbisonicBase();
    virtual ~CAmbisonicBase() = default;
    unsigned GetOrder(); // returns order of current ambisonic config
    bool GetHeight(); // returns true of false regarding whether or not the config has height
    unsigned GetChannelCount(); // returns the number of b format channels
    virtual bool Configure(unsigned nOrder, bool b3D, unsigned nMisc); // recreates the object with the new configuration aligning to arguments 
    virtual void Reset() = 0; // not implemented
    virtual void Refresh() = 0; // not implemented

protected: // class info 
    unsigned m_nOrder; // order 
    bool m_b3D; // Y or N to height
    unsigned m_nChannelCount; // channel count
    bool m_bOpt; // 
};

#endif //_AMBISONIC_BASE_H
