#ifndef GLUG_SCOPED_CF_HPP
#define GLUG_SCOPED_CF_HPP

#include <CoreFoundation/CoreFoundation.h>

namespace glug
{

template <typename cf_ref>
class scoped_cf
{
public:
    // ctor
    scoped_cf(cf_ref cf): cf(cf) {}
    // move ctor
    scoped_cf(scoped_cf &&that): cf(that.cf) { that.cf = nullptr; }
    // move assignment
    void operator =(scoped_cf &&that) { cf = that.cf; that.cf = nullptr; }
    // dtor
    virtual ~scoped_cf() { if (cf) CFRelease(cf); }

    // cast operators
    operator bool() { return cf != nullptr; }
    operator cf_ref() { return cf; }
    cf_ref *operator &() { return &cf; }

protected:
    // copy ctor
    scoped_cf(const scoped_cf &) = delete;
    // copy assignment
    void operator =(const scoped_cf &) = delete;

private:
    cf_ref cf;
};

} // namespace glug

#endif // GLUG_SCOPED_CF_HPP
