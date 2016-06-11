
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__StreetlightProxy_h__PROXY_MARSHAL_H
#define __dbusxx__StreetlightProxy_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>

namespace ch {
namespace bbv {

class brightness_proxy
: public ::DBus::InterfaceProxy
{
public:

    brightness_proxy()
    : ::DBus::InterfaceProxy("ch.bbv.brightness")
    {
    }

public:

    /* properties exported by this interface */
        const double scaled() {
            ::DBus::CallMessage call ;
             call.member("Get"); call.interface("org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            const std::string interface_name = "ch.bbv.brightness";
            const std::string property_name  = "scaled";
            wi << interface_name;
            wi << property_name;
            ::DBus::Message ret = this->invoke_method (call);
            ::DBus::MessageIter ri = ret.reader ();
            ::DBus::Variant argout; 
            ri >> argout;
            return argout;
        };
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */

public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
namespace ch {
namespace bbv {

class moisture_proxy
: public ::DBus::InterfaceProxy
{
public:

    moisture_proxy()
    : ::DBus::InterfaceProxy("ch.bbv.moisture")
    {
    }

public:

    /* properties exported by this interface */
        const double scaled() {
            ::DBus::CallMessage call ;
             call.member("Get"); call.interface("org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            const std::string interface_name = "ch.bbv.moisture";
            const std::string property_name  = "scaled";
            wi << interface_name;
            wi << property_name;
            ::DBus::Message ret = this->invoke_method (call);
            ::DBus::MessageIter ri = ret.reader ();
            ::DBus::Variant argout; 
            ri >> argout;
            return argout;
        };
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */

public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
namespace ch {
namespace bbv {

class proximity_proxy
: public ::DBus::InterfaceProxy
{
public:

    proximity_proxy()
    : ::DBus::InterfaceProxy("ch.bbv.proximity")
    {
    }

public:

    /* properties exported by this interface */
        const double scaled() {
            ::DBus::CallMessage call ;
             call.member("Get"); call.interface("org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            const std::string interface_name = "ch.bbv.proximity";
            const std::string property_name  = "scaled";
            wi << interface_name;
            wi << property_name;
            ::DBus::Message ret = this->invoke_method (call);
            ::DBus::MessageIter ri = ret.reader ();
            ::DBus::Variant argout; 
            ri >> argout;
            return argout;
        };
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */

public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
namespace ch {
namespace bbv {

class luminosity_proxy
: public ::DBus::InterfaceProxy
{
public:

    luminosity_proxy()
    : ::DBus::InterfaceProxy("ch.bbv.luminosity")
    {
    }

public:

    /* properties exported by this interface */
        const double scaled() {
            ::DBus::CallMessage call ;
             call.member("Get"); call.interface("org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            const std::string interface_name = "ch.bbv.luminosity";
            const std::string property_name  = "scaled";
            wi << interface_name;
            wi << property_name;
            ::DBus::Message ret = this->invoke_method (call);
            ::DBus::MessageIter ri = ret.reader ();
            ::DBus::Variant argout; 
            ri >> argout;
            return argout;
        };
        void scaled( const double & input) {
            ::DBus::CallMessage call ;
             call.member("Set");  call.interface( "org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            ::DBus::Variant value;
            ::DBus::MessageIter vi = value.writer ();
            vi << input;
            const std::string interface_name = "ch.bbv.luminosity";
            const std::string property_name  = "scaled";
            wi << interface_name;
            wi << property_name;
            wi << value;
            ::DBus::Message ret = this->invoke_method (call);
        };
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */

public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
namespace ch {
namespace bbv {

class warning_proxy
: public ::DBus::InterfaceProxy
{
public:

    warning_proxy()
    : ::DBus::InterfaceProxy("ch.bbv.warning")
    {
    }

public:

    /* properties exported by this interface */
        const std::string phrase() {
            ::DBus::CallMessage call ;
             call.member("Get"); call.interface("org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            const std::string interface_name = "ch.bbv.warning";
            const std::string property_name  = "phrase";
            wi << interface_name;
            wi << property_name;
            ::DBus::Message ret = this->invoke_method (call);
            ::DBus::MessageIter ri = ret.reader ();
            ::DBus::Variant argout; 
            ri >> argout;
            return argout;
        };
        void phrase( const std::string & input) {
            ::DBus::CallMessage call ;
             call.member("Set");  call.interface( "org.freedesktop.DBus.Properties");
            ::DBus::MessageIter wi = call.writer(); 
            ::DBus::Variant value;
            ::DBus::MessageIter vi = value.writer ();
            vi << input;
            const std::string interface_name = "ch.bbv.warning";
            const std::string property_name  = "phrase";
            wi << interface_name;
            wi << property_name;
            wi << value;
            ::DBus::Message ret = this->invoke_method (call);
        };
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */

public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
#endif //__dbusxx__StreetlightProxy_h__PROXY_MARSHAL_H