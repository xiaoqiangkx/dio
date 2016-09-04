#ifndef DIO_BASE_COPYABLE_H
#define DIO_BASE_COPYABLE_H

namespace dio
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
};

};

#endif  // DIO_BASE_COPYABLE_H
