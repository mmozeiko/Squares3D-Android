#ifndef __XML_H__
#define __XML_H__

#include "common.h"
#include "file.h"
#include "vmath.h"

class XMLnode;

typedef vector<XMLnode> XMLnodes;

class XMLreader;
class XMLwriter;

class XMLnode
{
    friend void outputNode(const XMLnode& node, std::ostream& stream, int level);
    friend class XMLreader;
    friend class XMLwriter;
public:
    XMLnode() {};
    XMLnode(const string& name, const string& value = "") : name(name), value(value), line(0) {}

    void load(File::Reader& reader);
    void save(File::Writer& writer);

    XMLnodes childs;
    string name;
    string value;
    unsigned int line;

    inline bool hasAttributes() const;
    inline bool hasAttribute(const string& name) const;

    template <typename T>
    inline T getAttribute(const string& name) const;
    inline string getAttribute(const string& name) const;

    template <typename T>
    inline T getAttribute(const string& name, T defaultValue) const;
    inline string getAttribute(const string& name, const string& defaultValue) const;
    inline Vector getAttributesInVector(const string& attributeSymbols) const;

    inline void setAttribute(const string& name, const string& value);

private:
    StringMap attributes;
};

inline bool XMLnode::hasAttributes() const
{
    return attributes.size() != 0;
}

inline bool XMLnode::hasAttribute(const string& name) const
{
    return foundIn(attributes, name);
}

template <typename T>
T XMLnode::getAttribute(const string& name) const
{
    StringMap::const_iterator iter = attributes.find(name);
    if (iter != attributes.end())
    {
        return cast<T>(iter->second);
    }

    Exception("Missing attribute '" + name + "' in node '" + name + "' at line " + cast<string>(line));
}

string XMLnode::getAttribute(const string& name) const
{
    StringMap::const_iterator iter = attributes.find(name);
    if (iter != attributes.end())
    {
        return iter->second;
    }

    Exception("Missing attribute '" + name + "' in node '" + name + "' at line " + cast<string>(line));
}

template <typename T>
T XMLnode::getAttribute(const string& name, T defaultValue) const
{
    StringMap::const_iterator iter = attributes.find(name);
    if (iter != attributes.end())
    {
        return cast<T>(iter->second);
    }
    return defaultValue;
}

string XMLnode::getAttribute(const string& name, const string& defaultValue) const
{
    StringMap::const_iterator iter = attributes.find(name);
    if (iter != attributes.end())
    {
        return iter->second;
    }
    return defaultValue;
}

void XMLnode::setAttribute(const string& name, const string& value)
{
    attributes[name] = value;
}

Vector XMLnode::getAttributesInVector(const string& attributeSymbols) const
{
    assert(attributeSymbols.size() < 5);
    Vector vector;
    for (size_t i = 0; i < attributeSymbols.size(); i++)
    {
        string key(1, attributeSymbols[i]);
        vector[i] = getAttribute<float>(key);
    }
    return vector;
}

#endif // __XML_H__
