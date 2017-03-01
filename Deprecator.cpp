#include <iostream>
#include <fstream>
#include "base/json/json_file_value_serializer.h"
#include "base/path_service.h"
#include "base/values.h"
#include "base/json/json_string_value_serializer.h"


#define config_doc "Deprecatorconfig.json"


//first version of controller
class DeprecatorClass {

public:
    static DeprecatorClass* getInstance() 
    {
        std::ofstream myfile;
        myfile.open ("getInstance.txt",std::fstream::app);
        myfile << "asked an istance of the singleton: ";
        myfile << m_instanceDeprecator;
        myfile << "\n";
        if(m_instanceDeprecator == nullptr)
        {
            m_instanceDeprecator = new DeprecatorClass;
            myfile.open ("example5.txt",std::fstream::app);
            myfile << "created a new instance of the class: ";
            myfile << m_instanceDeprecator;
            myfile << "\n";
            myfile.close();
            return m_instanceDeprecator;
        }
        else
        {
            myfile << "instance returned: ";
            myfile << m_instanceDeprecator;
            myfile << "\n";
            return m_instanceDeprecator;
            myfile.close();
        }
    }
    //metodo chiamato per controllo valore su json
    bool Check(std::string received)
    {
        bool bool_value = true;
        std::ofstream myfile;
        myfile.open ("Check.txt",std::fstream::app);
        myfile << "ricevuta la key: ";
        myfile << received;
        myfile << "\n";
        myfile.close();
        dizionario->GetBoolean("Bi", &bool_value);
        return(bool_value);
    }

private:
    // private constructor and destructor

    DeprecatorClass() 
    {
        std::ofstream myfile;
        myfile.open ("main.txt",std::fstream::app);
        myfile << "instrance of singleton class created: ";
        myfile << this;
        myfile << "\n";
        if(m_instanceDeprecator == nullptr)
        {
        m_instanceDeprecator= this;
        myfile << "instrance of singleton class assiged to m_instanceDeprecator\n";
        }
        base::FilePath original_file_path;
        PathService::Get(base::DIR_CURRENT, &original_file_path);
        original_file_path = original_file_path.AppendASCII(config_doc);
    	JSONFileValueDeserializer deserializer2(original_file_path);
    	int errorcode=0;
    	std::string errormessage;
  		dizionario = base::DictionaryValue::From(deserializer2.Deserialize(&errorcode, &errormessage));
		if (dizionario == NULL)//error reading the json file
			{
                myfile << "Failed to parse configuration\n";
                myfile << errormessage;
                myfile << "\n";
                myfile.close();
   			 	return;
			}
        size_t dim;
        myfile << "json file read with success\n";
        dim = deserializer2.get_last_read_size();
        myfile << "Dimenzione ultimo Json letto(byte): ";
        myfile << dim;
        myfile << "\n";
        myfile.close();
    }

    ~DeprecatorClass() {}

    // private copy constructor and assignment operator
    DeprecatorClass(const DeprecatorClass&);
    DeprecatorClass& operator=(const DeprecatorClass&);
    //variable private
    static DeprecatorClass *m_instanceDeprecator;
    std::unique_ptr<base::DictionaryValue> dizionario;
};

DeprecatorClass* DeprecatorClass::m_instanceDeprecator = nullptr;
