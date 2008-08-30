/*
$fileHeader$
*/

/*! \mainpage Imebra manual

\section copyright Copyright

Copyright 2003, 2004, 2005, 2006 by Paolo Brandoli.


\section section_Introduction Introduction

Please read the \ref license_agreement first!

Imebra is an open source Dicom library.
The library has been designed to handle Dicom files, but it includes also some
 classes that manage jpeg and other image files.

At the moment the library provides the following features:
- multi platform
- self contained (the library uses only functions from the standard C library
                  and the standard template library)
- dicom files parser and builder
- jpeg files parser and builder
- image decompression and compression in the following formats:
  - jpeg baseline (8 bits per color channel lossy)
  - jpeg baseline extended (12 bits per color channel lossy)
  - jpeg lossless (up to 16 bits per color channel lossless)
  - raw dicom (up to 16 bits per color channel lossless)
  - rle dicom (up to 16 bits per color channel lossless)
  .
  All the formats are supported both in compression and decompression mode
- color space conversion
- support for nested datasets (sequences)
- support for Unicode and different Dicom charsets
- support for transactions
- load the larger tags only when necessary

Other features have been planned but have not been included in this release.
The missed features are the following:
- support for dicom objects (like patient, procedure, image, and so on)
- network support for communication between Dicom devices


\section is_not What Imebra does NOT do?

The library doesn't check for a Dicom stream validity; this feature will be 
 introduced with the support for dicom objects.


\section start Where to start

After reading the \subpage license_agreement, you should read the \subpage quick_tour
 and the section \subpage imebra_structure.

A guide that will help you to include Imebra in your project can be
 found in \subpage add_to_project.

A detailed reference of the C++ classes that compose Imebra is included in
 this manual.


\section changeLog Changes log

\subsection since_0_0_41 Changes since version 0.0.41 (Alpha)

- Added the function puntoexe::imebra::transforms::VOILUT::getCenterWidth()
- The jpegCodec returns an image with color space "YBR_FULL" when the image is
  compressed in lossy mode and the dataset specifies the color space "RGB"
- Enhanced precision in the RGB to YBR_FULL color conversion
- Enhanced precision in the YBR_FULL to RGB color conversion
- Several optimization in the uncompressed Dicom image decoder
- Added the class puntoexe::imebra::trasforms::transformBuffersInPlace
- puntoexe::imebra::VOILUT and puntoexe::imebra::modalityVOILUT now derive
  from puntoexe::imebra::trasforms::transformBuffersInPlace
- puntoexe::imebra::viewHelper releases the dataset when no images are displayed
- Several optimizations in the Jpeg image decoder
- puntoexe::streamReader::read() throws an exception when the end of file is
  reached
- added puntoexe::streamReader::endReached()
- Several optimizations in puntoexe::streamReader
- Several optimizations in the Huffman decoder


\subsection since_0_0_40 Changes since version 0.0.40 (Alpha)

- Added the example dicom2jpeg


\subsection since_0_0_38 Changes since version 0.0.38 (Alpha)

- Closes #12 (Subsampled images are saved/loaded incorrectly by the jpeg codec)
- Closes #13 (When saving a jpeg image from a dataset and it doesn't need to be converted an exception is thrown)
- Closes #14 (When saving an image the subsampling flags don't match the quality)


\subsection since_0_0_36 Changes since version 0.0.36 (Alpha)

- Removed dependence from charsetsList in data, buffer, dataSet, dataGroup, dataHandler
- Closes #9 (The lossless jpeg codec saves corrupted images)
- Closes #10 (A basic offset table is added even when it shouldn't)
- Now non encapsulated images are saved one after another even when their length is odd: no padding bytes are inserted
- closes #11 (The 32 bits tag's length is truncated (only the lower 16 bits are correct) )
- The images build during the test units had a reduced range. Corrected
- Now the jpeg codec creates the offset table when loading an image


\subsection since_0_0_35 Changes since version 0.0.35 (Alpha)

- Closes #7 (memoryPool isn't thread safe)
- The memory string now is managed by an auto_ptr
- In the memoryPool minimized the number of moved pointers when a memory object is reused
- The dataSet doesn't need to retrieve the images handlers anymore when updating the offsets table
- The dicom codec doesn't need to retrieve the handlers anymore when calculating the tag size
- viewHelper now accepts a null pointer as image
- VOILUT now returns the right voilut description
- puntoexe::memory hides the string of bytes
- Added the class puntoexe::imebra::waveform to handle waveforms embedded in puntoexe::imebra::dataSet
- Added SWIG headers (partial)


\subsection since_0_0_34 Changes since version 0.0.34 (Alpha)

- Closes #4 (The function jpegCodec::writeTag() always writes a tagId=0 on high-endian architectures)
- Closes #5 (The unit test streamBitsTest doesn't flush the write buffer)
- puntoexe::imebra::transforms::VOILUT now disables any VOI/LUT if 
   puntoexe::imebra::transforms::VOILUT::setVOILUT is called with an ID=0


\subsection since_0_0_33 Changes since version 0.0.33 (Alpha)

- Closes #2 (The code assumes that wchar_t is 2 bytes long, while some systems have wchar_t=4 bytes long)
- Closes #3 (Usage of ICONV should check for return value E2BIG)
- Added casting operators () to puntoexe::ptr


\subsection since_0_0_32 Changes since version 0.0.32 (Alpha)

- Corrected the ptr class so baseObject compiles on GCC
- Corrected thread (removed orphan functions)
- Now charsetConversion throws an exception if a charset is not
   supported by the system


\subsection since_0_0_31 Changes since version 0.0.31 (Alpha)

- The PDF documentation is back


\subsection since_0_0_30 Changes since version 0.0.30 (Alpha)

- The smart pointer \ref puntoexe::ptr is able to cast the object's type.
  See \ref new_ptr_behaviour for more information.
- The reference counter in puntoexe::baseObject now is set to 0 at
   construction time and should be increased by the application.
  It doesn't affect your code if you used the smart pointer puntoexe::ptr.
  See \ref new_ptr_behaviour for more information.
- Updated the documentation to reflect recent changes
- The criticalSection now has its own class
- Added the class thread


\subsection since_0_0_29 Changes since version 0.0.29 (Alpha)

- Now the library doesn't fail when the dataset has an empty
   images' offset table
- Now the Dicom codec doesn't switch to implicit datatype when 
   a tag without datatype is found in the group 0x0002.\n
  The tag without datatype is still recognized. This solves a problem 
   with dicom files generated by DicomWorks


\subsection since_0_0_28 Changes since version 0.0.28 (Alpha)

- Added the function puntoexe::imebra::handlers::data::getBufferSize()
- Added the function puntoexe::imebra::buffer::getBufferSizeBytes()
- Now the functions in puntoexe::imebra::dataSet that need the buffer
   size use the new buffer's functions instead of retrieving a data
   handler


\subsection since_0_0_27 Changes since version 0.0.27 (Alpha)

- Breaking change: introduced the puntoexe::streamReader and the 
  puntoexe::streamWriter to control the puntoexe::baseStream objects
- Breaking change: now puntoexe::imebra::dataSet throws the exception
  puntoexe::imebra::dataSetImageDoesntExist when a non existing frame
  is requested with puntoexe::imebra::dataSet::getImage()
- corrected a bug that was crashing the library when an empty tag was
  read
- corrected a bug that was causing a deadlock when 
  puntoexe::WaitForMultipleObjects was used (used by the transactions)
- Added the load on demand for the bigger tags
- Now the library handles correcly the images that are fragmented in several
  data items
- Improvement in the Jpeg codec's performances
- Now image::create() returns a writable datahandler: this avoid the need
  to ask for a writable data handler and improves the speed
- added puntoexe::memoryPool::flush()
- now the stream names can be in unicode format


\subsection since_0_0_26 Changes since version 0.0.26 (Alpha)

- Corrected the sample \ref quick_tour_image
- Corrected a bug in the memoryManager's destructor
- Now the memory manager's parameters can be configured with preprocessor
   definitions


\subsection since_0_0_25 Changes since version 0.0.25 (Alpha)

- Replaced "informations" with "information" and "infos" with "info" \n
  The function exceptionsManager::getExceptionInfos became exceptionsManager::getExceptionInfo \n
  The function exceptionsManager::clearExceptionInfos became exceptionsManager::clearExceptionInfo
- Corrected an issue in the RLE Dicom codec: \n
  after reading a segment the decoder was seeking to the wrong position in the
  dicom file, while writing it was writing wrong offsets
- Improved performances in the Jpeg IDCT function


\subsection since_0_0_24 Changes since version 0.0.24 (Alpha)

- Introduced common lock objects
- Introduced the transactions
- Compiles also on Embedded Visual C++ 4 (requires STLPORT, see 
  sourceforge.net/projects/stlport)
- Introduced the view helper class


\subsection since_0_0_22 Changes since version 0.0.22 (Alpha)

- Introduced support for Unicode and different dicom charsets
- Modified several files to solve problems with Borland C++ Builder 2006
- The dicom codec now uses a dataHandlerRaw to read the tags from the file 
   (previously it was using a normal dataHandler)
- Updated the documentation
- Modified the exceptionManager: now it store a list of objects instead of a
   list of strings


\subsection since_0_0_21 Changes since version 0.0.21 (Alpha)

- Corrected the transformHighBit class
- Modified the exceptionsManager (now it stores the messages per thread and not
   per exception)


\section new_ptr_behaviour New smart pointer's behaviour

Several users had difficulties in understanding the behaviour of the smart
 pointer implemented by the \ref puntoexe::ptr class and the reference count
 mechanism in the \ref puntoexe::baseObject. To solve the reported problems
 the reference counter mechanism has been changed from the version 0.0.31.

Up to the version 0.0.30 the reference counter was initialized to 1 by the
 constructor of \ref puntoexe::baseObject, so a call to puntoexe::baseObject::addRef()
 wasn't necessary after the construction of a baseObject.

This was intended to simplify the usage of the reference counter (one less call to
 addRef()), but ended up adding more complications to the product.
Anyway the final application shouldn't had made any call to addRef() and release()
 if the proper smart pointer was used.

Also, the smart pointer wasn't able to cast the objects' types when copying data
 from other smart pointer: in the beginning this behaviour was intentional
 (I wanted the end programmer to specify his intentions and use the casting
 operators when needed), but most of the users expected the smart pointer to take 
 care of this.

Now the reference counter is initialized to 0 and not to 1 during the baseObject's
 construction: this implies that puntoexe::baseObject::addRef() has to be 
 called immediatly after the object construction: anyway this operation is performed
 automatically by the smart pointer puntoexe::ptr.

This simplified the behaviour of other functions in the ptr class: for instance the
 function puntoexe::ptr::get() doesn't need to increase the reference counter
 anymore.

Also the user is now forced to use the smart pointer because more baseObject's functions 
 have been made protected or private (addRef() and release() now are callable
 by the smart pointers only).

The smart pointer is now able to cast the object containing in other smart pointers
 during the assignment or the construction of a new pointer.

The changes shouldn't affect your old source code if you used the puntoexe::ptr
 class to control the puntoexe::baseObject derived objects.

*/


