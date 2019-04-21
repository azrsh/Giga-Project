#ifndef WRITABLE_INTERFACE_h
#define WRITABLE_INTERFACE_h

template <class T>
class Writer
{
    T _obj;

  public:
    void write() { _obj.write(); };
};

template <class T>
class IWritable
{
  public:
    void write() { static_cast<T &>(this)->write(); }
};

#endif