#pragma once

#include "Client.hpp"

#include <iomanip>
#include <iostream>
#include <ostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

namespace Database
{
    const std::string           FOLDER      = "database/";
    const std::string           EXTENSION   = ".xml";

    class Account
    {
    public:
        Account() { }
        virtual ~Account() { }

    private:
        Account(const Account &) { }
        const Account & operator = (const Account &) { return *this; }

    private:
        std::string				mLogin;
        std::string				mPassword;
        std::string				mPseudo;
        std::string			    mStatus;
        std::list<std::string>	mFriends;
        
    public:
        void setLogin(const std::string& login)                 { mLogin = login; }
        void setPassword(const std::string& password)           { mPassword = password; }
        void setPseudo(const std::string& pseudo)               { mPseudo = pseudo; }
        void setStatus(const std::string& status)               { mStatus = status; }
        void setFriends(const std::list<std::string>& friends)  { mFriends = friends; }
       
        const std::string& getLogin() const                     { return mLogin; }
        const std::string& getPassword() const                  { return mPassword; }
        const std::string& getPseudo() const                    { return mStatus; }
        const std::string& getStatus() const                    { return mStatus; }
        const std::list<std::string>& getFriends() const        { return mFriends; }

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int)
        {
            ar & BOOST_SERIALIZATION_NVP(mLogin);
            ar & BOOST_SERIALIZATION_NVP(mPassword);
            ar & BOOST_SERIALIZATION_NVP(mPseudo);
            ar & BOOST_SERIALIZATION_NVP(mStatus);
            ar & BOOST_SERIALIZATION_NVP(mFriends);
        }
    };
}
