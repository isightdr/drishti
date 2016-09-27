/*!
  @file   ACFField.h
  @author David Hirvonen (C++ implementation)
  @brief  Utility class to provide optional fields for (de)serialization.

  \copyright Copyright 2014-2016 Elucideye, Inc. All rights reserved.
  \license{This project is released under the 3 Clause BSD License.}

*/

#ifndef __DRISHTI__ACF_ACFFIELD__
#define __DRISHTI__ACF_ACFFIELD__

#include "drishti/acf/drishti_acf.h"
#include "drishti/core/boost_serialize_common.h"

#include <string>
#include <vector>

DRISHTI_ACF_NAMESPACE_BEGIN

template <typename T> struct Field
{
    Field()
    {
        has = false;
    }
    Field(const T &t)
    {
        value = t;
        has = true;
    }
    Field(const std::string &name_, const T &value_, bool)
    {
        isLeaf = true;
        has = true;
        name = name_;
        value = value_;
    }

    ~Field()
    {

    }

    Field<T>& operator=(const std::pair<std::string, T> &src)
    {
        isLeaf = true;
        has = true;
        name = src.first;
        value = src.second;
        return *this;
    }

    void set(const std::string &name_, bool has_, bool isLeaf_, const T& value_)
    {
        name = name_;
        has = has_;
        isLeaf = isLeaf_;
        value = value_;
    }

    void set(const std::string &name_, bool has_, bool isLeaf_)
    {
        name = name_;
        has = has_;
        isLeaf = isLeaf_;
    }

    void merge(const Field<T> &df, int checkExtra)
    {
        if(!has && df.has)
        {
            set(df.name, df.has, df.isLeaf, df.value);
        }
    }

    void set(const std::string &src)
    {
        name = src;
    }
    void mark(bool flag)
    {
        has = flag;
    }
    void setIsLeaf(bool flag)
    {
        isLeaf = flag;
    }

    operator T() const
    {
        CV_Assert(has);
        return value;
    }
    const T &get() const
    {
        return value;
    }

    T& operator *()
    {
        return value;
    }
    const T& operator *() const
    {
        return value;
    }

    T* operator->()
    {
        return &value;
    }
    const T* operator->() const
    {
        return &value;
    }

    T &get()
    {
        return value;
    }

    //friend template<typename T2> std::ostream& operator<<(std::ostream &os, const Field<T2>& src);
    //friend template<typename T2> std::ostream& operator<<(std::ostream &os, const Field<std::vector<T2>> &src);

    // Boost serialization:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & value;
        ar & name;
        ar & has;
        ar & isLeaf;
    }

    T value;
    std::string name;
    bool has = false;
    bool isLeaf = true;
};

DRISHTI_ACF_NAMESPACE_END

#endif // __DRISHTI__ACF_ACFFIELD__

