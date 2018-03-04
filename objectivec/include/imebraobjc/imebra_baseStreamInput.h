/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcBaseStreamInput__INCLUDED_)
#define imebraObjcBaseStreamInput__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class BaseStreamInput;
}
#endif

///
/// \brief This class represents a generic input stream.
///
/// Specialized classes derived from this one can read data from files stored
/// on the computer's disks (ImebraFileStreamInput) or from memory
/// (ImebraMemoryStreamInput).
///
/// The client application cannot read the data directly from a
/// ImebraBaseStreamInput but must use a ImebraStreamReader. Several
/// ImebraStreamReader objects can read data from the same
/// ImebraBaseStreamInput object.
///
/// The ImebraStreamReader class is not thread-safe, but different
/// ImebraStreamReader objects in different threads can access the same
/// ImebraBaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraBaseStreamInput: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::BaseStreamInput* m_pBaseStreamInput;
}

#endif

    -(void)dealloc;

@end

#endif // !defined(imebraObjcBaseStreamInput__INCLUDED_)