#ifndef READABLE_INTERFACE_h
#define READABLE_INTERFACE_h

template <class T>
class Reader
{
    T *_obj;

  public:
    Reader(T *obj) : _obj(obj){};
    int read() { return _obj->read(); };
};

template <class T>
class IReadable
{
  public:
    int read() { static_cast<T &>(this)->read(); }
};

#endif