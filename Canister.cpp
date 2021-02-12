// Name: Navdeep Virdi
// Seneca email: nvirdi2@myseneca.ca
// Student ID: 166485193
// Date: Feb 11, 2021

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <istream>
#include <iomanip>
#include "cstring.h"  // using strLen, strCpy and strCmp 
#include "Canister.h"
using namespace std;
namespace sdds 
{
    //PI: 3.14159265  (a global constant double value created in Canister.cpp)
    const double PI = 3.14159265;


    void Canister::clear()
    {
        delete[] m_contentName;

        m_contentName = nullptr;
        m_usable = true;
        m_contentVolume = 0.0;
    }
   

    double Canister::capacity() const
    {
        //Capacity = PI x (H - 0.267) x (D/2) x (D/2)
        return PI * (m_hieght - 0.267) * (m_diameter / 2) * (m_diameter / 2);
    }


    double Canister::volume() const
    {
        return m_contentVolume;
    }


    Canister& Canister::setContent(const char* contentName)
    {
        if (contentName == nullptr)
        {
            m_usable = false;
        }

        else if (isEmpty())
        {
            setName(contentName);
        }
        
        else if(strCmp(m_contentName, contentName) != 0)
        {
            m_usable = false;
        } return *this;
    }


    Canister& Canister::pour(double quantity)
    {
        if(m_usable == true && quantity > 0 && 
                (quantity + m_contentVolume) <= capacity())
        {
                m_contentVolume += quantity;
        } 

        else
        {
            m_usable = false;
        } return *this;
    }


    Canister& Canister::pour(Canister& C)
    {
        setContent(C.m_contentName);

        if (C.volume() > (capacity() - volume()))
        {
            C.m_contentVolume -= (capacity() - volume());
            m_contentVolume = capacity();
        }

        else
        {
            C = pour(C.m_contentVolume);
            C.m_contentVolume = 0.0;
        } return *this;
    }


    std::ostream& Canister::display() const
    {
        cout << fixed << setprecision(1);
        cout.width(7);
        cout << right << capacity();

        cout << "cc (" << m_hieght << "x" << m_diameter
             << ") Canister";

            if (m_usable == false)
            {
                cout << " of Unusable content, discard!";
            }

            else if (m_contentName != nullptr)
            {
                cout << " of ";

                cout.width(7);

                cout << m_contentVolume;
                cout << "cc   ";
                cout << m_contentName;

            } return cout;
    }


    void Canister::setToDefault()
    {
        m_contentName = nullptr;
        
        m_diameter = 10.0;
        m_hieght = 13.0;
        m_contentVolume = 0.0; 
        
        m_usable = true;      
    }


    bool Canister::isEmpty() const
    {
       if (m_contentVolume < 0.00001)
       {
           return true;
       }

       else
       {
           return false;
       }
    }


    bool Canister::hasSameContent(const Canister& C) const
    {
        if (m_contentName != nullptr && C.m_contentName != nullptr)
        {
            int x;
            x = strCmp(m_contentName, C.m_contentName);

            return x == 0;
        } 

        else
        {
            return false;
        }
    }


    void Canister:: setName(const char* Cstr)
    {
        if (Cstr != nullptr && m_usable == true)
        {
            delete[] m_contentName;
            
            int i;
            i = strLen(Cstr);
            
            m_contentName = new char[i + 1];
            
            strCpy(m_contentName, Cstr);
        }
    }


//The Canister can be created in three different ways
    Canister::Canister()
    {
        setToDefault();
    }


    Canister::Canister(const char* contentName)
    {
        setToDefault();
        setName(contentName);
    }
    

    Canister::Canister(double hieght, double diameter, const char* contentName)
    {

        if (hieght >= 13 && hieght <= 40 && diameter >= 10 
                && diameter <= 30)
        {
            setToDefault();
            
            m_hieght = hieght;
            m_diameter = diameter;   
            
            setName(contentName);
        }

        else
        {
            setToDefault();
            m_usable = false;
        }
    }


    Canister::~Canister() 
    {
        if (m_contentName && strLen(m_contentName) > 0)
        {
            delete[] m_contentName;
        }
    }
}
